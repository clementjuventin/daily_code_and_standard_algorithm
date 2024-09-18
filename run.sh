#!/bin/bash

# Check if a program name is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <program_name>"
    exit 1
fi

PROGRAM_NAME=$1
OUTPUT_NAME="${PROGRAM_NAME}"

# Compile the program
g++ -std=c++20 -isystem /usr/include/gtest -pthread $PROGRAM_NAME.cpp -lgtest -lgtest_main -o $OUTPUT_NAME

# Check if compilation was successful
if [ $? -eq 0 ]; then
    ./$OUTPUT_NAME
    rm ./$OUTPUT_NAME
else
    echo "Compilation failed."
    exit 1
fi
