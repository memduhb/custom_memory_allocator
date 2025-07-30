#include "internal.h"
#include <mutex>
#include <iostream>

std::mutex heap_mutex;

void* my_malloc_internal(size_t size) {
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

void* my_malloc(std::size_t size) {
    std::lock_guard<std::mutex> lock(heap_mutex);
    return my_malloc_internal(size);
}
