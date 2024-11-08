#include <benchmark/benchmark.h>
#include <iostream>
#include <thread>

#include "engine.hpp"
#include "state_buffer.hpp"

static void sync_buffer_push_and_pop_extremity(benchmark::State &state)
{
    const size_t buffer_size = 126;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];

    StateBuffer<buffer_size> buffer;

    for (auto _ : state)
    {
        for (size_t i = 0; i < states_size; i++)
        {
            buffer.try_push(std::move(states[i]));
            buffer.try_pop(reciever[i]);
        }
    }
}

static void sync_buffer_full_capacity(benchmark::State &state)
{
    const size_t buffer_size = 126;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];

    StateBuffer<buffer_size> buffer;

    for (auto _ : state)
    {
        for (size_t i = 0; i < states_size; i += buffer_size)
        {
            size_t max_states = std::min(i + buffer_size, states_size);
            for (size_t j = i; j < max_states; j++)
                buffer.try_push(std::move(states[j]));
            for (size_t j = i; j < max_states; j++)
                buffer.try_pop(reciever[j]);
        }
    }
}

static void sync_buffer_await_push_and_await_pop_extremity(benchmark::State &state)
{
    const size_t buffer_size = 126;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];

    StateBuffer<buffer_size> buffer;

    for (auto _ : state)
    {
        for (size_t i = 0; i < states_size; i++)
        {
            buffer.await_push(std::move(states[i]));
            buffer.await_pop(reciever[i]);
        }
    }
}

static void sync_buffer_await_full_capacity(benchmark::State &state)
{
    const size_t buffer_size = 126;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];
    StateBuffer<buffer_size> buffer;

    for (auto _ : state)
    {
        for (size_t i = 0; i < states_size; i += buffer_size)
        {
            size_t max_states = std::min(i + buffer_size, states_size);
            for (size_t j = i; j < max_states; j++)
                buffer.await_push(std::move(states[j]));
            for (size_t j = i; j < max_states; j++)
                buffer.await_pop(reciever[j]);
        }
    }
}

static void async_1producer_1consumer_buffer_full_capacity(benchmark::State &state)
{
    const size_t buffer_size = 126;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];
    StateBuffer<buffer_size> buffer;

    for (auto _ : state)
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
        }
    }
}

static void async_2producer_2consumer_buffer_full_capacity(benchmark::State &state)
{
    const size_t buffer_size = 126;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];
    StateBuffer<buffer_size> buffer;

    for (auto _ : state)
    {
        for (size_t i = 0; i < states_size; i += buffer_size)
        {
            size_t max_states = std::min(i + buffer_size, states_size);
            std::thread producer1([&]
                                  {
                for (size_t j = i; j < max_states/2; j++)
                    buffer.await_push(std::move(states[j])); });
            std::thread producer2([&]
                                  {
                for (size_t j = max_states/2; j < max_states; j++)
                    buffer.await_push(std::move(states[j])); });
            std::thread consumer1([&]
                                  {
                for (size_t j = i; j < max_states/2; j++)
                    buffer.await_pop(reciever[j]); });
            std::thread consumer2([&]
                                  {
                for (size_t j = max_states/2; j < max_states; j++)

                    buffer.await_pop(reciever[j]); });

            producer1.join();
            producer2.join();
            consumer1.join();
            consumer2.join();
        }
    }
}

BENCHMARK(sync_buffer_push_and_pop_extremity);
BENCHMARK(sync_buffer_full_capacity);
BENCHMARK(sync_buffer_await_push_and_await_pop_extremity);
BENCHMARK(sync_buffer_await_full_capacity);

BENCHMARK(async_1producer_1consumer_buffer_full_capacity);
BENCHMARK(async_2producer_2consumer_buffer_full_capacity);

int main(int argc, char **argv)
{
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}