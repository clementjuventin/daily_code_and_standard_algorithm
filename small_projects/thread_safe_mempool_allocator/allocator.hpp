#pragma once

#include <cstddef> 

#define SLAB_MAX_SIZE 1000 // SLAB max size in bytes

/*
 * A slab is a contiguous set of memory, used to allocate a certain amount of objects of the same fixed size.
*/
struct Slab {
    void* memory;           // Pointer to the start of the slab memory
    std::size_t object_size;     // Size of each object in the slab
    std::size_t total_objects;   // Total number of objects in this slab
    std::size_t free_objects;    // Number of free objects
    void* free_list;        // List of free objects in the slab (free slots)
    Slab* next;             // Pointer to the next slab in the cache
};

/*
 * A cache is a set of slabs.
*/
struct Cache {
    std::size_t object_size;     // Size of the objects managed by this cache
    Slab* empty_slabs;      // List of empty slabs
    Slab* partial_slabs;    // List of partially filled slabs
    Slab* full_slabs;       // List of full slabs
    std::size_t slab_size;       // Size of each slab
};

template <typename T>
class Allocator {
private:
    Slab* get_slab_from_memory(Cache *cache, void* memory);
    void move_slab(Slab*& from, Slab *&to, Slab* slab);
    void initialize_slab(Cache* cache, Slab* slab); 
    void initialize_cache(Cache* cache);
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    // Cache
    Cache* cache;

    Allocator() noexcept;
    T* allocate();
    void deallocate(T* p) noexcept;

    template <typename U>
    bool operator==(const Allocator<U>&) const noexcept;

    template <typename U>
    bool operator!=(const Allocator<U>&) const noexcept;
};

