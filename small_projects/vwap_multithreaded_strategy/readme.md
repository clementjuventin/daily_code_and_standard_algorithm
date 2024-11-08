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

## Benchmark

We want to measure the performance of the pipeline by measuring the time it takes to process the whole dataset. For this, we will start by synchronously processing the data.

