#include "internal.h"
#include <mutex>
#include <cstdint>
#include <iostream>

/**
 * Custom memory deallocation function with double-free protection.
 * Adds freed blocks to free list (LIFO) for memory reuse.
 * Thread-safe with mutex protection.
 */

extern std::mutex heap_mutex;

/**
 * Internal free function that handles the actual deallocation logic.
 * @param ptr Pointer to memory block to free
 */
void my_free_internal(void* ptr) {
    
    if (!ptr) return;
    BlockHeader* header = static_cast<BlockHeader*>(ptr) - 1;
    
    // Double free protection: check if block is already free
    if (header->is_free) {
        std::cerr << "[ERROR] Double free detected! Block at " << ptr << " is already free.\n";
        return; // Don't free again
    }
    
    header->is_free = true;

    // Push the freed block onto the front of the free list (LIFO)
    header->next = free_list;
    free_list = header;
}

/**
 * Public interface for memory deallocation.
 * Thread-safe wrapper around my_free_internal.
 * @param ptr Pointer to memory block to free
 */
void my_free(void* ptr) {
    std::lock_guard<std::mutex> lock(heap_mutex);
    my_free_internal(ptr);
}
