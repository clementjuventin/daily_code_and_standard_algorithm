# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -I /usr/src/gtest  # Adjust path to gtest/include
LDFLAGS = -L /usr/src/gtest -lgtest -lgtest_main -pthread  # Adjust path to gtest/lib

# Source files
SOURCES = allocator.cpp unit_test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = test_allocator

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp allocator.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run tests
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
