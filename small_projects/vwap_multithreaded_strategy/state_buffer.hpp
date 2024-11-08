#pragma once

#include <cstddef>
#include <atomic>

// TODO: Check size
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
  State buffer[BUFFER_SIZE + 2];
  std::atomic<size_t> head;
  std::atomic<size_t> tail;
  std::atomic<bool> stop_waiting;
  std::atomic<size_t> awaiting_threads;

public:
  StateBuffer();
  void clear_waiting_threads();
  bool try_push(State &&s);
  bool try_pop(State &s);

  void await_push(State &&s);
  void await_pop(State &s);
};

template class StateBuffer<5ul>;
template class StateBuffer<100ul>;
