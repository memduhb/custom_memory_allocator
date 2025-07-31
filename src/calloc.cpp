#include "internal.h"
#include <mutex>
#include <iostream>
#include <cstring>
#include <climits>

/**
 * Custom calloc function for array allocation with zero-initialization.
 * Implements overflow protection and handles edge cases.
 * Thread-safe with mutex protection.
 */

extern std::mutex heap_mutex;

/**
 * Allocates memory for an array and initializes all bytes to zero.
 * @param num Number of elements to allocate
 * @param size Size of each element in bytes
 * @return Pointer to zero-initialized memory, or nullptr if allocation fails
 */
void* my_calloc(std::size_t num, std::size_t size) {
    std::lock_guard<std::mutex> lock(heap_mutex);

    if (num == 0 || size == 0) return nullptr;

    size_t total = num * size;
    if (size != 0 && total / size != num) {
        std::cerr << "[my_calloc] Integer overflow detected!\n";
        return nullptr;
    }

    void* memory = my_malloc_internal(total);
    if (!memory) return nullptr;

    std::memset(memory, 0, total);
    return memory;
}


