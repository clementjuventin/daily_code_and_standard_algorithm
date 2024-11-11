#pragma once
#include <cstddef>
#include <atomic>
#include <iostream>

/** Represent the state of a market.
 * Size: 8* 12 bytes = 96 bytes */
struct State
{
  unsigned long long open_time;
  unsigned long long close_time;
  unsigned long long number_of_trades;
  double open;
  double high;
  double low;
  double close;
  double volume;
  double quote_asset_volume;
  double taker_buy_base_asset_volume;
  double taker_buy_quote_asset_volume;
  double ignore;
  // unsigned long long padding[4];
};

/** This class is the queue that threads can access to fetch data */
template <std::size_t BUFFER_SIZE, typename T>
class TBuffer
{
public:
  static const size_t EMPTY_SLOTS = 1;
  /** Max capacity is a power of two */
  static const size_t MAX_CAPACITY = BUFFER_SIZE + EMPTY_SLOTS;
  static const size_t MAX_CAPACITY_MASK = MAX_CAPACITY - 1;

  TBuffer();
  /** Return MAX_CAPACITY if it works, the index of the last known tail if it fails */
  size_t try_push(T &&s);
  /** Return MAX_CAPACITY if it works, the index of the last known head if it fails */
  size_t try_pop(T &s);

  void await_push(T &&s);
  void await_pop(T &s);

  inline size_t size(const size_t &current_head, const size_t &current_tail) const
  {
    return ((current_head - current_tail) & MAX_CAPACITY_MASK);
  };

  inline size_t size() const
  {
    size_t current_head = head.load(std::memory_order_acquire);
    size_t current_tail = tail.load(std::memory_order_acquire);
    return ((current_head - current_tail) & MAX_CAPACITY_MASK) - EMPTY_SLOTS;
  };

private:
  std::atomic<size_t> head;
  std::atomic<size_t> tail;
  T buffer[MAX_CAPACITY];

  static_assert((MAX_CAPACITY & (MAX_CAPACITY - 1)) == 0, "MAX_CAPACITY must be a power of 2");
};

template <std::size_t BUFFER_SIZE>
using StateBuffer = TBuffer<BUFFER_SIZE, State>;
