#include <thread>
#include <functional>

#include "engine.hpp"
#include "worker.hpp"
#include "state_buffer.hpp"

int main()
{
    StateBuffer<100> buffer{};
    Engine<100> engine{buffer};
    Worker<100, 10> worker{buffer};

    std::thread engine_thread(std::bind(&Engine<100>::run, &engine));
    std::thread worker_thread(std::bind(&Worker<100, 10>::run, &worker));

    engine_thread.join();
    worker.stop();
    buffer.clear_waiting_threads();
    worker_thread.join();
}