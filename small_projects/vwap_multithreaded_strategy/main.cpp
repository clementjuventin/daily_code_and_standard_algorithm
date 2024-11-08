#include <thread>
#include <functional>
#include <iostream>

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
    worker_thread.join();

    // const size_t buffer_size = 5;
    // const size_t states_size = 1000;
    // State states[states_size];
    // State reciever[states_size];

    // for (size_t i = 0; i < states_size; i++)
    //     states[i] = {i, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    // StateBuffer<buffer_size> buffer;

    // for (size_t i = 0; i < states_size; i += buffer_size)
    // {
    //     size_t max_states = std::min(i + buffer_size, states_size);
    //     for (size_t j = i; j < max_states; j++)
    //         buffer.await_push(std::move(states[j]));
    //     for (size_t j = i; j < max_states; j++)
    //         buffer.await_pop(reciever[j]);
    // }
}