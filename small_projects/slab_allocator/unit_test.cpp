#include <gtest/gtest.h>
#include "allocator.hpp"

// Test case for simple allocation
TEST(AllocatorTest, SimpleAllocate)
{
    Allocator<int> allocator;
    int *ptr = allocator.allocate();

    // Check if the returned pointer is not null
    ASSERT_NE(ptr, nullptr);

    // Test if we can assign a value and retrieve it
    *ptr = 42;
    EXPECT_EQ(*ptr, 42);

    allocator.deallocate(ptr);
}

// Test case for deallocation and reallocation
TEST(AllocatorTest, DeallocateAndReallocate)
{
    Allocator<int> allocator;

    // Allocate and deallocate an object
    int *ptr1 = allocator.allocate();
    *ptr1 = 10;
    allocator.deallocate(ptr1);

    // Allocate again, it should reuse the previous memory
    int *ptr2 = allocator.allocate();

    // Ensure the pointers are the same (slab reuses memory)
    EXPECT_EQ(ptr1, ptr2);

    allocator.deallocate(ptr2);
}

// Test case for allocating multiple objects
TEST(AllocatorTest, MultipleAllocations)
{
    Allocator<int> allocator;

    // Allocate multiple objects
    int *ptr1 = allocator.allocate();
    int *ptr2 = allocator.allocate();

    // Check that both pointers are not null
    ASSERT_NE(ptr1, nullptr);
    ASSERT_NE(ptr2, nullptr);

    // Ensure the two pointers are different
    EXPECT_NE(ptr1, ptr2);

    allocator.deallocate(ptr1);
    allocator.deallocate(ptr2);
}

// Test for the slab allocation logic (ensuring slab moves from partial to full)
TEST(AllocatorTest, SlabAllocation)
{
    Allocator<int> allocator;

    std::vector<int *> allocations;

    // Allocate a large number of objects (fill up a slab)
    for (int i = 0; i < 1000; ++i)
    {
        allocations.push_back(allocator.allocate());
    }

    // Ensure all pointers are valid and unique
    for (int i = 0; i < 1000; ++i)
    {
        ASSERT_NE(allocations[i], nullptr);
        for (int j = i + 1; j < 1000; ++j)
        {
            EXPECT_NE(allocations[i], allocations[j]);
        }
    }

    // Deallocate all objects
    for (int *ptr : allocations)
    {
        allocator.deallocate(ptr);
    }
}
