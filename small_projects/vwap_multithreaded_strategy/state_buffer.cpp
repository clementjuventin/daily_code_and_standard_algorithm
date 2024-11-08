#include "state_buffer.hpp"

#include <array>
#include <atomic>
#include <iostream>

template <std::size_t BUFFER_SIZE>
StateBuffer<BUFFER_SIZE>::StateBuffer() : head(0), tail(BUFFER_SIZE + 1) {}

template <std::size_t BUFFER_SIZE>
size_t StateBuffer<BUFFER_SIZE>::try_push(State &&s)
{
  size_t current_head = head.load(std::memory_order_relaxed);
  // Because MAX_CAPACITY is a power of two
  size_t next_head = (current_head + 1) & (MAX_CAPACITY_MASK);

  size_t current_tail = tail.load(std::memory_order_acquire);
  if (next_head == current_tail)
    return current_tail;

  buffer[current_head] = std::move(s);

  head.store(next_head, std::memory_order_release);

  // diff == BUFFER_SIZE means the queue was empty. This prevent the notification to be sent when no threads are waiting
  current_tail = tail.load(std::memory_order_acquire);
  if ((current_tail > next_head
           ? current_tail - next_head
           : current_tail + MAX_CAPACITY - next_head) == BUFFER_SIZE)
  {
    head.notify_one();
  }

  return MAX_CAPACITY;
}

template <std::size_t BUFFER_SIZE>
size_t StateBuffer<BUFFER_SIZE>::try_pop(State &s)
{
  size_t current_tail = tail.load(std::memory_order_relaxed);
  // Because MAX_CAPACITY is a power of two
  size_t next_tail = (current_tail + 1) & (MAX_CAPACITY_MASK);

  size_t current_head = head.load(std::memory_order_acquire);
  if (next_tail == current_head)
    return current_head;

  s = std::move(buffer[next_tail]);
  tail.store(next_tail, std::memory_order_release);

  // diff == EMPTY_SLOTS means the queue was full. This prevent the notification to be sent when no threads are waiting
  current_head = head.load(std::memory_order_acquire);
  if ((current_head > next_tail
           ? current_head - next_tail
           : current_head + MAX_CAPACITY - next_tail) == EMPTY_SLOTS)
    tail.notify_one();
  return MAX_CAPACITY;
}

template <std::size_t BUFFER_SIZE>
void StateBuffer<BUFFER_SIZE>::await_push(State &&s)
{
  while (true)
  {
    size_t current_tail = try_push(std::forward<State>(s));
    if (current_tail == MAX_CAPACITY)
      break;
    tail.wait(current_tail);
  }
}

template <std::size_t BUFFER_SIZE>
void StateBuffer<BUFFER_SIZE>::await_pop(State &s)
{
  while (true)
  {
    size_t current_head = try_pop(s);
    if (current_head == MAX_CAPACITY)
      break;
    head.wait(current_head);
  }
}
