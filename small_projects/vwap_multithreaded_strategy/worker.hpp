#pragma once

#include <queue>
#include "state_buffer.hpp"

/** This class represents a worker consuming data */
template <std::size_t BUFFER_SIZE, std::size_t VWAP_BASE>
class Worker
{
  std::atomic<bool> keep_running;
  StateBuffer<BUFFER_SIZE> &buffer;

  std::queue<double> prices_volume;
  std::queue<double> volumes;
  double cumulative_price_volume;
  double cumulative_volume;
  double vwap;

  void calculate_vwap(const State &s);

public:
  Worker(StateBuffer<BUFFER_SIZE> &b);
  void stop();
  void run();
};