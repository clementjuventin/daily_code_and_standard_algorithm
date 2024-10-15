#include "allocator.hpp"
#include <new> // For placement new

template <typename T>
Slab *get_slab(Cache *cache)
{
    Slab *slab = cache->partial_slabs;
    // If the partial_slabs list is empty
    if (slab == nullptr)
    {
        slab = new Slab();
        initialize_slab(cache, slab);
        cache->partial_slabs = slab;
    }
    // Take the next slab until one fit or we reach the end
    else
    {
        Slab *last;
        while (slab != nullptr && slab->free_objects < n)
        {
            last = slab;
            slab = slab->next;
        }

        if (slab == nullptr)
        {
            slab = new Slab();
            initialize_slab(cache, slab);
            last->next = slab;
        }
    }

    return slab;
}
template <typename T>
void initialize_slab(Cache *cache, Slab *slab)
{
    slab->memory = ::operator new(cache->slab_size);
    slab->object_size = cache->object_size;
    slab->total_objects = cache->slab_size / cache->object_size;
    slab->free_objects = slab->total_objects;

    slab->free_list = slab->memory;
    char *current = static_cast<char *>(slab->memory);
    for (size_t i = 0; i < slab->total_objects - 1; ++i)
    {
        *reinterpret_cast<void **>(current) = current + cache->object_size;
        current += cache->object_size;
    }
    *reinterpret_cast<void **>(current) = nullptr;

    slab->next = nullptr;
}
template <typename T>
void initialize_cache(Cache *cache)
{
    cache->object_size = sizeof(T);
    cache->empty_slabs = nullptr;
    cache->partial_slabs = nullptr;
    cache->full_slabs = nullptr;
    cache->slab_size = SLAB_MAX_SIZE / cache->object_size * cache->object_size;
}

// Default constructor
template <typename T>
Allocator<T>::Allocator() noexcept
{
}

// Allocate memory for n objects
template <typename T>
T *Allocator<T>::allocate(std::size_t n)
{
    if (n == 0)
    {
        return nullptr;
    }
    Cache *cache = caches;
    
}

// Deallocate memory for n objects
template <typename T>
void Allocator<T>::deallocate(T *p) noexcept
{
    // You can add custom deallocation logic here
    ::operator delete(p); // Deallocating raw memory
}

// Equality comparison operator
template <typename T>
template <typename U>
bool Allocator<T>::operator==(const Allocator<U> &) const noexcept
{
    // Custom equality logic (usually true for stateless allocators)
    return true;
}

// Inequality comparison operator
template <typename T>
template <typename U>
bool Allocator<T>::operator!=(const Allocator<U> &) const noexcept
{
    return !(*this == Allocator<U>());
}

template class Allocator<int>;
