#include <nanobench.h>
#include <thread>
#include <functional>
#include <iostream>
#include <vector>
#include <random>

#include "engine.hpp"
#include "worker.hpp"
#include "state_buffer.hpp"

int main()
{
    const size_t buffer_size = 127;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];

    StateBuffer<buffer_size> buffer;

    ankerl::nanobench::Bench().run("sync_pop_pull", [&]
                                   {
        for (size_t i = 0; i < states_size; i += buffer_size)
    {
        size_t max_states = std::min(i + buffer_size, states_size);
        for (size_t j = i; j < max_states; j++)
            buffer.try_push(std::move(states[j]));
        for (size_t j = i; j < max_states; j++)
            buffer.try_pop(reciever[j]);
    } });

    ankerl::nanobench::Bench().run("sync_pop_pull_extremity", [&]
                                   {
                for (size_t i = 0; i < states_size; i++)
        {
            buffer.try_push(std::move(states[i]));
            buffer.try_pop(reciever[i]);
        } });

    ankerl::nanobench::Bench().run("async_pop_pull", [&]
                                   {
                for (size_t i = 0; i < states_size; i += buffer_size)
        {
            size_t max_states = std::min(i + buffer_size, states_size);
            std::thread producer([&]
                                 {
                for (size_t j = i; j < max_states; j++)
                    buffer.await_push(std::move(states[j])); });
            std::thread consumer([&]
                                 {
                for (size_t j = i; j < max_states; j++)
                    buffer.await_pop(reciever[j]); });

            producer.join();
            consumer.join();
        } });
}
