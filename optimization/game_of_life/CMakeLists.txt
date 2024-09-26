cmake_minimum_required(VERSION 3.10)

project(GameOfLifeOptimization VERSION 1.0)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

set(GAME_OF_LIFE_VARIANTS
    game_of_life_v1.cpp
    game_of_life_v2.cpp
    game_of_life_v3.cpp
)

add_executable(benchmark benchmark.cpp utils.cpp ${GAME_OF_LIFE_VARIANTS})
target_compile_options(benchmark PRIVATE -O3)
target_link_libraries(benchmark PRIVATE benchmark::benchmark)

add_executable(unit_tests unit_tests.cpp utils.cpp ${GAME_OF_LIFE_VARIANTS})

target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)