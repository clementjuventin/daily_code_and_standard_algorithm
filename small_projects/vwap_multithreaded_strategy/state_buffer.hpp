#pragma once

#include <cstddef>
#include <atomic>

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
  double ignore; // ??
};

/** This class is the queue that threads can access to fetch data */
template <std::size_t BUFFER_SIZE>
class StateBuffer
{
  static const size_t EMPTY_SLOTS = 2;
  /** Max capacity is a power of two */
  static const size_t MAX_CAPACITY = BUFFER_SIZE + EMPTY_SLOTS;
  static const size_t MAX_CAPACITY_MASK = MAX_CAPACITY - 1;
  State buffer[MAX_CAPACITY];
  std::atomic<size_t> head;
  std::atomic<size_t> tail;

  static_assert((MAX_CAPACITY & (MAX_CAPACITY - 1)) == 0, "MAX_CAPACITY must be a power of 2");

public:
  StateBuffer();
  bool try_push(State &&s);
  bool try_pop(State &s);

  void await_push(State &&s);
  void await_pop(State &s);
};

template class StateBuffer<6ul>;
template class StateBuffer<126ul>;
template class StateBuffer<254ul>;
