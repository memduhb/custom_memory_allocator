#include "internal.h"
#include <mutex>
#include <iostream>

/**
 * Custom memory allocation function with free list reuse.
 * Searches free list first, then requests from OS if needed.
 * Thread-safe with mutex protection.
 */

std::mutex heap_mutex;
BlockHeader* free_list = nullptr; // Global pointer to the head of the free list

/**
 * Internal malloc function that implements the allocation logic.
 * Searches free list for suitable blocks, requests from OS if none found.
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or nullptr if allocation fails
 */
void* my_malloc_internal(size_t size) {
    // First check if there is a free block in the free list
    BlockHeader* prev = nullptr;
    BlockHeader* curr = free_list;

    while (curr) {
        if (curr->is_free && curr->size >= size) {
            // Found a suitable block; remove it from the free list
            if (prev) {
                prev->next = curr->next;
            } else {
                free_list = curr->next;
            }

            curr->is_free = false;
            curr->next = nullptr;

            std::cout << "[my_malloc] Reused free block of size " << curr->size << " bytes\n";
            return static_cast<void*>(curr + 1);
        }

        prev = curr;
        curr = curr->next;
    }
    
    // If no free block is found, request memory from the OS (mmap)
    void* memory = request_memory_from_os(size);
    if (!memory) return nullptr;

    BlockHeader* header = static_cast<BlockHeader*>(memory);
    header->size = size;
    header->is_free = false;
    header->next = nullptr;

    std::cout << "[my_malloc] Requested: " << size << " bytes\n";
    std::cout << "[my_malloc] Header + data starts at: " << memory << "\n";
    std::cout << "[my_malloc] Usable pointer returned: " << static_cast<void*>(header + 1) << "\n";
    
    return static_cast<void*>(header + 1);
}

/**
 * Public interface for memory allocation.
 * Thread-safe wrapper around my_malloc_internal.
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or nullptr if allocation fails
 */
void* my_malloc(std::size_t size) {
    std::lock_guard<std::mutex> lock(heap_mutex);
    return my_malloc_internal(size);
}
