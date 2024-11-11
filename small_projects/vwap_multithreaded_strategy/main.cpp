#include <thread>
#include <functional>
#include <iostream>

#include "engine.hpp"
#include "worker.hpp"
#include "state_buffer.hpp"

#include <cstdint>

// #define RDTSC() ({           \
//     uint64_t _cycles;        \
//     asm volatile(            \
//         "rdtsc\n\t"          \
//         "shl $32, %%rdx\n\t" \
//         "or %%rdx, %%rax"    \
//         : "=a"(_cycles)      \
//         :                    \
//         : "rdx");            \
//     _cycles;                 \
// })

int main()
{
    // auto a = RDTSC();
    // auto b = RDTSC();

    const size_t buffer_size = 127;
    const size_t states_size = 1000;
    State states[states_size];
    State reciever[states_size];
    StateBuffer<buffer_size> buffer;

    std::cout << "async_1producer_1consumer_buffer_full_capacity" << std::endl;
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

    // TBuffer<127, std::array<char, 128>> buffer{};
    // // TBuffer<126, char[64]> buffer2{};
    // // TBuffer<126, char[96]> buffer3{};
    // const size_t buffer_size = 127;
    // const size_t states_size = 1000;
    // std::array<char, 128> c50;

    // for (size_t i = 0; i < states_size; i += buffer_size)
    // {
    //     size_t max_states = std::min(i + buffer_size, states_size);
    //     std::thread producer([&]
    //                          {
    //                              for (size_t j = i; j < max_states; j++)
    //                                  {
    //                                     buffer.try_push(std::move(c50));
    //                                     while (buffer.size() != 0);
    //                                  } });
    //     std::thread consumer([&]
    //                          {
    //                              for (size_t j = i; j < max_states; j++)
    //                              {
    //                                     buffer.await_pop(c50);
    //                              } });

    //     producer.join();
    //     consumer.join();
}