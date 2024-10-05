cmake_minimum_required(VERSION 3.10)

project(DailyCodeOpti VERSION 1.0)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

set(DAILY_CODE_PB
    day1.cpp
    day2.cpp
    day4.cpp
)

add_executable(benchmark benchmark.cpp ${DAILY_CODE_PB})
target_compile_options(benchmark PRIVATE -O3)
target_link_libraries(benchmark PRIVATE benchmark::benchmark)