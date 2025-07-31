#include "internal.h"
#include <mutex>
#include <cstdint>
#include <iostream>

/* Custom Free function
    - Implements memory deallocation with double-free protection
    - Adds freed blocks to free list (LIFO - Last In, First Out)
    - Detects and prevents double-free attempts
    - Uses block headers to track allocation status
    - Thread-safe with mutex protection
    - Null pointer handling (no-op)
*/

extern std::mutex heap_mutex;

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

void my_free(void* ptr) {
    std::lock_guard<std::mutex> lock(heap_mutex);
    my_free_internal(ptr);
}
