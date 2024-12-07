# Minimum CMake version required
cmake_minimum_required(VERSION 3.14)

# Project name
project(VWAP_PIPELINE)
include(FetchContent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BENCHMARK_ENABLE_LIBPFM ON)
set(BENCHMARK_ENABLE_LIBPFM ON CACHE BOOL "Enable libpfm support")


# Define source files for main application and benchmark
set(SOURCES engine.cpp state_buffer.hpp worker.cpp main.cpp)
set(BENCHMARK_SOURCES engine.cpp state_buffer.hpp worker.cpp benchmark.cpp)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)


if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build enabled")
else()
    message("Release build (or unspecified) enabled")
endif()


# Create the main application executable
add_executable(main_app ${SOURCES})
target_compile_options(main_app PRIVATE 
    $<$<CONFIG:Debug>:-g -O0>      # Enable debug symbols and disable optimization in Debug mode
    $<$<CONFIG:Release>:-O3>       # Enable high optimization in Release mode
)

# Create the benchmark executable
add_executable(benchmark_app ${BENCHMARK_SOURCES})
target_compile_options(benchmark_app PRIVATE -O3)

# Link libraries
target_link_libraries(main_app gtest gtest_main pthread)
target_link_libraries(benchmark_app benchmark pthread)

# Custom targets for running the executables
add_custom_target(run_main COMMAND main_app
    COMMENT "Running main application")
add_custom_target(run_benchmark COMMAND benchmark_app
    COMMENT "Running benchmark application")
add_custom_target(run_debug_main COMMAND $<TARGET_FILE:main_app> --debug
    COMMENT "Running main application in debug mode"
    DEPENDS main_app)

# Optionally, add a clean target to delete generated files
add_custom_target(clean_all COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMENT "Cleaning all build files")
