#include "state_buffer.hpp"

#include <array>
#include <atomic>
#include <iostream>

template <std::size_t BUFFER_SIZE>
StateBuffer<BUFFER_SIZE>::StateBuffer() : head(0), tail(BUFFER_SIZE), stop_waiting{false} {}

template <std::size_t BUFFER_SIZE>
bool StateBuffer<BUFFER_SIZE>::try_push(const State &s)
{
  // TODO: Doc
  size_t current_head = head.load(std::memory_order_relaxed);
  size_t next_head = (current_head + 1) % (BUFFER_SIZE + 1);

  size_t current_tail = tail.load(std::memory_order_acquire);
  if (next_head == current_tail)
    return false;

  // TODO: Move??
  buffer[current_head] = s;

  head.store(next_head, std::memory_order_release);
  head.notify_one();
  return true;
}

template <std::size_t BUFFER_SIZE>
bool StateBuffer<BUFFER_SIZE>::try_pop(State &s)
{
  size_t current_tail = tail.load(std::memory_order_relaxed);
  size_t next_tail = (current_tail + 1) % (BUFFER_SIZE + 1);

  size_t current_head = head.load(std::memory_order_acquire);

  if (next_tail == current_head)
    return false;

  // TODO: Move??
  s = buffer[next_tail];

  tail.store(next_tail, std::memory_order_release);
  tail.notify_one();
  return true;
}

template <std::size_t BUFFER_SIZE>
void StateBuffer<BUFFER_SIZE>::await_push(const State &s)
{
  awaiting_threads.fetch_add(1, std::memory_order_relaxed);
  while (!stop_waiting.load(std::memory_order_acquire) && !try_push(s))
    tail.wait(tail.load(std::memory_order_relaxed));
  awaiting_threads.fetch_sub(1, std::memory_order_relaxed);
  awaiting_threads.notify_one();
}

template <std::size_t BUFFER_SIZE>
void StateBuffer<BUFFER_SIZE>::await_pop(State &s)
{
  awaiting_threads.fetch_add(1, std::memory_order_relaxed);
  while (!stop_waiting.load(std::memory_order_acquire) && !try_pop(s))
    head.wait(head.load(std::memory_order_relaxed));
  awaiting_threads.fetch_sub(1, std::memory_order_relaxed);
  awaiting_threads.notify_one();
}

template <std::size_t BUFFER_SIZE>
void StateBuffer<BUFFER_SIZE>::clear_waiting_threads()
{
  stop_waiting.store(true, std::memory_order_release);

  // Simulate an update for the head an tail pointers
  size_t current_head = head.load(std::memory_order_acquire);
  size_t current_tail = tail.load(std::memory_order_acquire);
  head.store(current_head + 1, std::memory_order_release);
  tail.store(current_tail + 1, std::memory_order_release);

  // Notify all threads to perform a check again (they will interrupt their execution)
  head.notify_all();
  tail.notify_all();

  // Wait for all threads to be stopped
  while (awaiting_threads.load(std::memory_order_acquire) != 0)
    awaiting_threads.wait(awaiting_threads);

  // Restore the original values
  head.store(current_head, std::memory_order_release);
  tail.store(current_tail, std::memory_order_release);

  stop_waiting.store(false, std::memory_order_release);
}
