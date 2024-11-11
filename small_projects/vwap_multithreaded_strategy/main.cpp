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
    const size_t buffer_size = 1023;
    const size_t vwap_base = 5;
    StateBuffer<buffer_size> buffer;
    Engine<buffer_size> engine(buffer);
    Worker<buffer_size, vwap_base> worker(buffer);

    std::thread t1(&Worker<buffer_size, vwap_base>::run, &worker);
    std::thread t2(&Engine<buffer_size>::run, &engine);

    t1.join();
    t2.join();

    return 0;
}