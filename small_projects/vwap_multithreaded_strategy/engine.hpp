#pragma once

#include "state_buffer.hpp"

template <std::size_t BUFFER_SIZE>
class Engine
{
  StateBuffer<BUFFER_SIZE> &buffer;
  void read_csv(const std::string &filename);
  unsigned long long convert_to_ts(const std::string &dateTime);

public:
  Engine(StateBuffer<BUFFER_SIZE> &buffer);
  void run();
};