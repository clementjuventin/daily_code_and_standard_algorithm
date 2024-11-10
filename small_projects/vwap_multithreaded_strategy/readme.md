# VWAP Multithreaded Calculation Pipeline

## Introduction

The purpose of this small project is to design a pipeline continuously receiving data and performing calculations on it.

The goal is to introduce as small overhead as possible to the data processing.

## Architecture

To simulate the data processing, I will considere some financial data and calculate the VWAP (Volume-Weighted Average Price) indicator.

The used dataset can be found here https://www.kaggle.com/datasets/imranbukhari/comprehensive-ethusd-1m-data?resource=download.

I will work with three components:
- `Engine`: this component will be responsible for pushing data.
- `Worker`: this component will be responsible for consuming data and performing calculations.
- `Pipeline`: this component will be responsible for managing the data flow.

The `Engine` component will read the CSV file line by line and push the data to a queue. There is no real efficiency constraint on this component since it's only used to simulate the data flow, we just need to have the possibility to push more data in the queue than the consumer can consume in a limited period of time.

The `Worker` v will consume the data from the queue and calculate the VWAP indicator. This is supposed to be the bottleneck of the pipeline.

The `Pipeline` component will manage the data flow between the `Engine` and the `Worker`. Technically, it will be implemented as a lock-free circular buffer with a static capacity. This is the critical component that needs to be as efficient as possible.

## Analysis

### Control or Efficiency

I realized that one property of the queue were slowing down other properties of the buffer. 
The ability for a thread to be stopped when awaiting for a new element to be pushed in the queue is very expensive since it requires to notify and count all the awaiting threads. It doubles the time it takes to push/pull an element in the queue.
For this project, efficiency was the main focus. I just removed this feature (stop awaiting threads) because in a real production environment the pipeline is never stopped and if we still wanted to stop it we could just block the inputs until the queue is empty and then turn off the thread.

### Optimizations

I realized that the notification methods were very expensive. I started to think about a way to reduce the notifications and figured out that we could just notify the threads when the queue is full or empty. This gave a ~25% performance boost.

I removed some modulo operations that were not necessary.
- Changed the MAX_CAPACITY to a power of 2 to avoid the modulo operation in the push and pull methods.
- Removed the modulo operation to calculate the difference between the head and the tail.

### Deadlocks

At some point I had a huge issue with deadlocks. I struggled to understand the source because the memory management for atomic variables was not clear for me.
After some time spent on clarifying subject, I understood that my main issues creating deadlocks were reads after reads while I took a decision based on the first read and awaited another condition on the next read.

## Benchmark

I benchmarked the buffer. I tested sequencial push/pull and await push/pull. I tested when we were always pushing and pulling on the first element (to trigger the full/empty notifications) and when we were fulling and emptying the buffer.
I also tested with multiples threads, but honestly, I don't know if it provides any useful information. 

I used the results to improve step by step the buffer.
```
-----------------------------------------------------------------------------------------
Benchmark                                               Time             CPU   Iterations
-----------------------------------------------------------------------------------------
sync_buffer_push_and_pop_extremity                   6420 ns         6420 ns       109710
sync_buffer_full_capacity                            4954 ns         4953 ns       136344
sync_buffer_await_push_and_await_pop_extremity       7183 ns         7183 ns        97173
sync_buffer_await_full_capacity                      6853 ns         6851 ns       101816
async_1producer_1consumer_buffer_full_capacity     273991 ns       216623 ns         3273
async_2producer_2consumer_buffer_full_capacity     621641 ns       468633 ns         1461
```

As you can see, using the await pull/push methods introduce an overhead of 15% to 40%.