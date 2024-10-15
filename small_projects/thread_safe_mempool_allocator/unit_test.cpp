#include <gtest/gtest.h>
#include "allocator.hpp"  // Include your allocator header file

// Test Fixture for Allocator
class AllocatorTest : public ::testing::Test {
protected:
    Allocator<int> allocator; // Replace MyAllocator with your actual allocator class

    void SetUp() override {
        // Setup code can go here if needed
    }

    void TearDown() override {
        // Cleanup code can go here if needed
    }
};

// Test memory allocation
TEST_F(AllocatorTest, AllocatesMemory) {
    int* ptr = allocator.allocate(10);
    ASSERT_NE(ptr, nullptr); // Check that allocation was successful

    // Optionally initialize the memory
    for (int i = 0; i < 10; ++i) {
        ptr[i] = i;
    }

    // Verify the values
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(ptr[i], i);
    }

    allocator.deallocate(ptr); // Clean up
}

// Test memory deallocation
TEST_F(AllocatorTest, DeallocatesMemory) {
    int* ptr = allocator.allocate(5);
    ASSERT_NE(ptr, nullptr); // Check that allocation was successful

    allocator.deallocate(ptr); // Deallocate memory

    // Note: Accessing ptr after deallocation is undefined behavior, so we won't check it here
}

// Test allocation of zero size
TEST_F(AllocatorTest, AllocatesZeroSize) {
    int* ptr = allocator.allocate(0);
    EXPECT_EQ(ptr, nullptr); // Check that allocating 0 returns nullptr (or your defined behavior)
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

