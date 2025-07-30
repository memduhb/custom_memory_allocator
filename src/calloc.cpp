#include "internal.h"
#include <mutex>
#include <iostream>
#include <cstring>
#include <climits>

extern std::mutex heap_mutex;

void* my_calloc(std::size_t num, std::size_t size) {
    std::lock_guard<std::mutex> lock(heap_mutex);
    if (num == 0 || size == 0) return nullptr;

    size_t total = num * size;
    if (size != 0 && total / size != num) {
        std::cerr << "[my_calloc] Integer overflow detected!\n";
        return nullptr;
    }

    void* memory = request_memory_from_os(total);
    if (!memory) return nullptr;

    BlockHeader* header = static_cast<BlockHeader*>(memory);
    header->size = total;
    header->is_free = false;
    header->next = nullptr;

    void* usable_ptr = static_cast<void*>(header + 1);
    std::memset(usable_ptr, 0, total);
    return usable_ptr;
}
