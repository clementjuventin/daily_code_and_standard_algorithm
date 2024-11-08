#include "state_buffer.hpp"

#include <array>
#include <atomic>
#include <iostream>

template <std::size_t BUFFER_SIZE>
StateBuffer<BUFFER_SIZE>::StateBuffer() : head(0), tail(BUFFER_SIZE + 1) {}

template <std::size_t BUFFER_SIZE>
bool StateBuffer<BUFFER_SIZE>::try_push(State &&s)
{
  size_t current_head = head.load(std::memory_order_relaxed);
  size_t next_head = (current_head + 1) % (MAX_CAPACITY);

  size_t current_tail = tail.load(std::memory_order_acquire);
  size_t diff = (MAX_CAPACITY + current_tail - next_head) % (MAX_CAPACITY);
  if (next_head == current_tail)
    return false;

  buffer[current_head] = std::move(s);

  head.store(next_head, std::memory_order_release);

  // diff == BUFFER_SIZE means the queue was empty. This prevent the notification to be sent when no threads are waiting
  if (diff == BUFFER_SIZE)
    head.notify_one();
  return true;
}

template <std::size_t BUFFER_SIZE>
bool StateBuffer<BUFFER_SIZE>::try_pop(State &s)
{
  size_t current_tail = tail.load(std::memory_order_relaxed);
  size_t next_tail = (current_tail + 1) % (MAX_CAPACITY);

  size_t current_head = head.load(std::memory_order_acquire);
  size_t diff = (MAX_CAPACITY + current_head - next_tail) % (MAX_CAPACITY);
  if (next_tail == current_head)
    return false;

  s = std::move(buffer[next_tail]);
  tail.store(next_tail, std::memory_order_release);

  // diff == EMPTY_SLOTS means the queue was full. This prevent the notification to be sent when no threads are waiting
  if (diff == EMPTY_SLOTS)
    tail.notify_one();
  return true;
}

template <std::size_t BUFFER_SIZE>
void StateBuffer<BUFFER_SIZE>::await_push(State &&s)
{
  while (!try_push(std::forward<State>(s)))
    tail.wait(tail.load(std::memory_order_relaxed));
}

template <std::size_t BUFFER_SIZE>
void StateBuffer<BUFFER_SIZE>::await_pop(State &s)
{
  while (!try_pop(s))
    head.wait(head.load(std::memory_order_relaxed));
}
