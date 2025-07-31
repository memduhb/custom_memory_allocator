#include "internal.h"
#include <mutex>
#include <cstring>

/* Custom Realloc function
    - Resizes memory blocks with intelligent optimization
    - Null pointer: behaves like malloc
    - Zero size: behaves like free (deallocates)
    - Smaller size: reuses same block (no data movement)
    - Larger size: allocates new block and copies data
    - Same size: returns original pointer (no-op)
    - Thread-safe with mutex protection
    - Preserves existing data during resize operations
*/

extern std::mutex heap_mutex;

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
