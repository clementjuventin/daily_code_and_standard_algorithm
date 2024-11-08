#include <thread>
#include <functional>
#include <iostream>

#include "engine.hpp"
#include "worker.hpp"
#include "state_buffer.hpp"

int main()
{
    static const size_t BUFFER_SIZE = 126;
    StateBuffer<BUFFER_SIZE> buffer{};
    Engine<BUFFER_SIZE> engine{buffer};
    Worker<BUFFER_SIZE, 10> worker{buffer};

    std::thread engine_thread(std::bind(&Engine<BUFFER_SIZE>::run, &engine));
    std::thread worker_thread(std::bind(&Worker<BUFFER_SIZE, 10>::run, &worker));

    engine_thread.join();
    worker.stop();
    worker_thread.join();
}