#include "worker.hpp"
#include <iostream>
#include <stdexcept>

template <std::size_t BUFFER_SIZE, std::size_t VWAP_BASE>
Worker<BUFFER_SIZE, VWAP_BASE>::Worker(StateBuffer<BUFFER_SIZE> &b) : buffer(b){};

template <std::size_t BUFFER_SIZE, std::size_t VWAP_BASE>
void Worker<BUFFER_SIZE, VWAP_BASE>::stop()
{
  keep_running.store(false, std::memory_order_release);
}

template <std::size_t BUFFER_SIZE, std::size_t VWAP_BASE>
void Worker<BUFFER_SIZE, VWAP_BASE>::run()
{
  keep_running.store(true, std::memory_order_release);
  while (keep_running.load(std::memory_order_acquire))
  {
    State s;
    buffer.await_pop(s);
    calculate_vwap(s);
  }
}
template <std::size_t BUFFER_SIZE, std::size_t VWAP_BASE>
void Worker<BUFFER_SIZE, VWAP_BASE>::calculate_vwap(const State &s)
{
  double volume = s.volume;
  double price_volume = volume * (s.high + s.low + s.close) / 3;

  cumulative_volume += volume;
  cumulative_price_volume += price_volume;

  volumes.push(volume);
  prices_volume.push(price_volume);

  if (volumes.size() >= VWAP_BASE)
  {
    cumulative_volume -= volumes.front();
    cumulative_price_volume -= prices_volume.front();

    volumes.pop();
    prices_volume.pop();
  }

  if (cumulative_volume != 0)
    vwap = cumulative_price_volume / cumulative_volume;
  else
    vwap = 0;
}