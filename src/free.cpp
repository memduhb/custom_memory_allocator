#include "internal.h"
#include <mutex>

extern std::mutex heap_mutex;

void my_free_internal(void* ptr) {
    if (!ptr) return;
    BlockHeader* header = static_cast<BlockHeader*>(ptr) - 1;
    header->is_free = true;
}

void my_free(void* ptr) {
    std::lock_guard<std::mutex> lock(heap_mutex);
    my_free_internal(ptr);
}
