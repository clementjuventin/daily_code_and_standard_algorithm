#pragma once

#include "state_buffer.h"

#include <array>
#include <atomic>
#include <iostream>

template <std::size_t BUFFER_SIZE, typename T>
TBuffer<BUFFER_SIZE, T>::TBuffer() : head(0), tail(0) {}

template <std::size_t BUFFER_SIZE, typename T>
size_t TBuffer<BUFFER_SIZE, T>::try_push(T &&s)
{
  size_t current_head = head.load(std::memory_order_relaxed);
  // Because MAX_CAPACITY is a power of two
  size_t new_head = (current_head + 1) & (MAX_CAPACITY_MASK);

  size_t current_tail = tail.load(std::memory_order_acquire);
  if (new_head == current_tail)
    return current_tail;

  buffer[current_head] = std::move(s);
  head.store(new_head, std::memory_order_release);

  // diff == BUFFER_SIZE means the queue was empty. This prevent the notification to be sent when no threads are waiting
  current_tail = tail.load(std::memory_order_acquire);
  if (size(new_head, current_tail) == 1)
    head.notify_one();

  return MAX_CAPACITY;
}

template <std::size_t BUFFER_SIZE, typename T>
size_t TBuffer<BUFFER_SIZE, T>::try_pop(T &s)
{
  size_t current_tail = tail.load(std::memory_order_relaxed);

  size_t current_head = this->head.load(std::memory_order_acquire);
  if (current_tail == current_head)
    return current_head;

  // Because MAX_CAPACITY is a power of two
  size_t new_tail = (current_tail + 1) & (MAX_CAPACITY_MASK);

  s = std::move(buffer[new_tail]);
  tail.store(new_tail, std::memory_order_release);

  // diff == EMPTY_SLOTS means the queue was full. This prevent the notification to be sent when no threads are waiting
  current_head = this->head.load(std::memory_order_acquire);
  if (size(current_head, new_tail) == BUFFER_SIZE - 1)
    tail.notify_one();
  return MAX_CAPACITY;
}

template <std::size_t BUFFER_SIZE, typename T>
void TBuffer<BUFFER_SIZE, T>::await_push(T &&s)
{
  while (true)
  {
    size_t current_tail = try_push(std::forward<T>(s));
    if (current_tail == MAX_CAPACITY)
      break;
    tail.wait(current_tail);
  }
}

template <std::size_t BUFFER_SIZE, typename T>
void TBuffer<BUFFER_SIZE, T>::await_pop(T &s)
{
  while (true)
  {
    size_t current_head = try_pop(s);
    if (current_head == MAX_CAPACITY)
      break;
    head.wait(current_head);
  }
}