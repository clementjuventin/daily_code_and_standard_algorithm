#include <benchmark/benchmark.h>
#include <iostream>
#include <thread>

#include "engine.hpp"
#include "state_buffer.hpp"

static void sync_buffer_push_and_pop_extremity(benchmark::State &state)
{
    State s;
    State r;
    StateBuffer<127> buffer;

    for (auto _ : state)
    {
        buffer.try_push(std::move(s));
        buffer.try_pop(r);
    }
}

static void sync_buffer_push_and_pop_inside(benchmark::State &state)
{
    State s;
    State r;
    StateBuffer<127> buffer;
    buffer.try_push(State());

    for (auto _ : state)
    {
        buffer.try_push(std::move(s));
        buffer.try_pop(r);
    }
}

static void sync_buffer_push_full_capacity_pull_full_capacity(benchmark::State &state)
{
    const size_t buffer_size = 127;
    State s;
    State r;
    StateBuffer<buffer_size> buffer;

    for (auto _ : state)
    {
        for (size_t j = 0; j < buffer_size; j++)
            buffer.try_push(std::move(s));
        for (size_t j = 0; j < buffer_size; j++)
            buffer.try_pop(r);
    }
}

static void async_empty_buffer_await_pop(benchmark::State &state)
{
    const size_t buffer_size = 127;
    State s;
    State r;
    StateBuffer<buffer_size> buffer;
    std::thread consumer;

    for (auto _ : state)
    {
        state.PauseTiming();
        consumer = std::thread([&]
                               { buffer.await_pop(r); });
        state.ResumeTiming();
        buffer.try_push(std::move(s));
        while (buffer.size() != 0)
            ;
        state.PauseTiming();
        consumer.join();
        state.ResumeTiming();
    }
}

static void async_full_buffer_await_push(benchmark::State &state)
{
    const size_t buffer_size = 127;
    State s;
    State r;
    StateBuffer<buffer_size> buffer;
    std::thread producer;

    for (size_t j = 0; j < buffer_size; j++)
        buffer.try_push(State());

    for (auto _ : state)
    {
        state.PauseTiming();
        producer = std::thread([&]
                               { buffer.await_push(std::move(s)); });
        state.ResumeTiming();
        buffer.try_pop(r);
        while (buffer.size() != buffer_size)
            ;
        state.PauseTiming();
        producer.join();
        state.ResumeTiming();
    }
}

BENCHMARK(sync_buffer_push_and_pop_extremity);
BENCHMARK(sync_buffer_push_and_pop_inside);
BENCHMARK(sync_buffer_push_full_capacity_pull_full_capacity);
BENCHMARK(async_full_buffer_await_push);
BENCHMARK(async_empty_buffer_await_pop);

int main(int argc, char **argv)
{
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}