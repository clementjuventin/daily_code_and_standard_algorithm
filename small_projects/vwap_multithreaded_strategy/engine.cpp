#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "engine.hpp"

template <std::size_t BUFFER_SIZE>
Engine<BUFFER_SIZE>::Engine(StateBuffer<BUFFER_SIZE> &b) : buffer(b) {}

template <std::size_t BUFFER_SIZE>
unsigned long long Engine<BUFFER_SIZE>::convert_to_ts(const std::string &dateTime)
{
  std::tm tm = {};
  std::istringstream ss(dateTime);

  ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
  if (ss.fail())
    throw std::runtime_error("Failed to parse date string: " + dateTime);

  time_t timeSinceEpoch = std::mktime(&tm);
  return static_cast<unsigned long long>(timeSinceEpoch);
}

template <std::size_t BUFFER_SIZE>
void Engine<BUFFER_SIZE>::read_csv(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::string line;
  // Skip the header line
  std::getline(file, line);
  size_t line_n = 0;
  size_t missed_lines = 0;

  while (std::getline(file, line))
  {
    std::stringstream lineStream(line);
    std::string cell;
    State s;

    std::getline(lineStream, cell, ','); // Open time
    s.open_time = convert_to_ts(cell);   // Convert string to unsigned long long

    std::getline(lineStream, cell, ','); // Open
    s.open = std::stod(cell);

    std::getline(lineStream, cell, ','); // High
    s.high = std::stod(cell);

    std::getline(lineStream, cell, ','); // Low
    s.low = std::stod(cell);

    std::getline(lineStream, cell, ','); // Close
    s.close = std::stod(cell);

    std::getline(lineStream, cell, ','); // Volume
    s.volume = std::stod(cell);

    std::getline(lineStream, cell, ','); // Close time
    s.close_time = convert_to_ts(cell);

    std::getline(lineStream, cell, ','); // Quote asset volume
    s.quote_asset_volume = std::stod(cell);

    std::getline(lineStream, cell, ','); // Number of trades
    s.number_of_trades = std::stoull(cell);

    std::getline(lineStream, cell, ','); // Taker buy base asset volume
    s.taker_buy_base_asset_volume = std::stod(cell);

    std::getline(lineStream, cell, ','); // Taker buy quote asset volume
    s.taker_buy_quote_asset_volume = std::stod(cell);

    std::getline(lineStream, cell, ','); // Ignore
    s.ignore = std::stod(cell);

    // Push the state object into the buffer
    bool pushed = buffer.try_push(std::move(s));
    missed_lines += !pushed;
    line_n++;

    if (line_n == 100000)
      break;
  }

  std::cout << "Finished to read " << line_n << " lines\n";
  std::cout << "Missed " << missed_lines << " lines\n";

  file.close();
}

template <std::size_t BUFFER_SIZE>
void Engine<BUFFER_SIZE>::run()
{
  read_csv("./archive/ETHUSD_1m_Binance.csv");
}