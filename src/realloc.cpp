#include "internal.h"
#include <mutex>
#include <cstring>

/**
 * Custom realloc function for resizing memory blocks.
 * Implements intelligent optimization based on size changes.
 * Thread-safe with mutex protection.
 */

extern std::mutex heap_mutex;

/**
 * Resizes a memory block with intelligent optimization.
 * @param ptr Pointer to existing memory block (nullptr treated as malloc)
 * @param size New size in bytes (0 treated as free)
 * @return Pointer to resized memory block, or nullptr if reallocation fails
 */
void* my_realloc(void* ptr, std::size_t size) {
    std::lock_guard<std::mutex> lock(heap_mutex);
    if (!ptr) return my_malloc_internal(size);
    if (size == 0) {
        my_free_internal(ptr);
        return nullptr;
    }

    BlockHeader* header = static_cast<BlockHeader*>(ptr) - 1;
    if (size == header->size) return ptr;
    if (size < header->size) {
        header->size = size;
        return ptr;
    }

    void* new_ptr = my_malloc_internal(size);
    if (!new_ptr) return nullptr;
    std::memcpy(new_ptr, ptr, header->size);
    my_free_internal(ptr);
    return new_ptr;
}
