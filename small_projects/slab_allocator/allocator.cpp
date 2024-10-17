#include "allocator.hpp"
#include <algorithm>
#include <cstddef>
#include <new>

/*
 * Returns the slab containing the passed pointer
 */
template <typename T>
Slab *Allocator<T>::get_slab_from_memory(Cache *cache, void *memory) {
  Slab *current = cache->partial_slabs;
  while (current != nullptr) {
    if (current->memory <= memory &&
        memory <
            static_cast<char *>(current->memory) + current->total_objects) {
      return current;
    }
    current = current->next;
  }
  current = cache->full_slabs;
  while (current != nullptr) {
    if (current->memory <= memory &&
        memory <
            static_cast<char *>(current->memory) + current->total_objects) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

/*
 * Move a slab from a certain list to another one. The slabs needs to be in the
 * "from" list
 */
template <typename T>
void Allocator<T>::move_slab(Slab *&from, Slab *&to, Slab *slab) {
  Slab *prev{nullptr}, *current{from};
  while (current != nullptr) {
    if (current == slab) {
      break;
    }
    prev = current;
    current = current->next;
  }
  if (prev != nullptr) {
    prev->next = current->next;
  } else {
    from = current->next;
  }
  current->next = to;
  to = current;
}

template <typename T>
void Allocator<T>::initialize_slab(Cache *cache, Slab *slab) {
  slab->memory = ::operator new(cache->slab_size);
  slab->object_size = cache->object_size;
  slab->total_objects = cache->slab_size / cache->object_size;
  slab->free_objects = slab->total_objects;

  slab->free_list = slab->memory;
  char *current = static_cast<char *>(slab->memory);
  for (size_t i = 0; i < slab->total_objects - 1; ++i) {
    *reinterpret_cast<void **>(current) = current + cache->object_size;
    current += cache->object_size;
  }
  *reinterpret_cast<void **>(current) = nullptr;

  slab->next = nullptr;
}

template <typename T> void Allocator<T>::initialize_cache(Cache *cache) {
  cache->object_size = std::max(sizeof(T), sizeof(void *));
  cache->partial_slabs = nullptr;
  cache->full_slabs = nullptr;
  cache->slab_size = SLAB_MAX_SIZE / cache->object_size * cache->object_size;
}

template <typename T> Allocator<T>::Allocator() noexcept {
  cache = new Cache();
  initialize_cache(cache);
}

template <typename T> T *Allocator<T>::allocate() {
  Slab *slab = cache->partial_slabs;

  // If the partial_slabs list is empty
  if (slab == nullptr) {
    slab = new Slab();
    initialize_slab(cache, slab);
    cache->partial_slabs = slab;
  }

  slab->free_objects--;

  if (slab->free_objects == 0)
    move_slab(cache->partial_slabs, cache->full_slabs, slab);

  T *allocated = static_cast<T *>(slab->free_list);
  slab->free_list = *reinterpret_cast<void **>(slab->free_list);
  return allocated;
}

template <typename T> void Allocator<T>::deallocate(T *p) noexcept {
  Slab *s = get_slab_from_memory(cache, static_cast<void *>(p));
  if (s != nullptr) {
    *reinterpret_cast<void **>(p) = s->free_list;
    s->free_list = static_cast<void *>(p);
    s->free_objects++;
    if (s->free_objects == 1)
      move_slab(cache->full_slabs, cache->partial_slabs, s);
  }
}

template <typename T>
template <typename U>
bool Allocator<T>::operator==(const Allocator<U> &) const noexcept {
  return true;
}

template <typename T>
template <typename U>
bool Allocator<T>::operator!=(const Allocator<U> &) const noexcept {
  return !(*this == Allocator<U>());
}

template class Allocator<int>;
