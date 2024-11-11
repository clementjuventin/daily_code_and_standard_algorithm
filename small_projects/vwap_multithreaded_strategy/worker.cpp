#include "worker.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

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
  double volume = std::max(s.volume, 0.0000001);
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

  if (cumulative_volume >= 0.00001)
    vwap = cumulative_price_volume / cumulative_volume;
  else
    vwap = 0;

  if (std::isnan(vwap))
  {

    throw std::runtime_error("VWAP is NaN");
  }

  std::cout << "vwap " << vwap << " cumulative_v " << cumulative_volume << " cumulative_p_v " << cumulative_price_volume << " price_volume " << price_volume << " volume " << volume << "\n";
}