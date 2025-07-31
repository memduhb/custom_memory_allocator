#ifndef MY_ALLOCATOR_INTERNAL_H
#define MY_ALLOCATOR_INTERNAL_H

#include <cstddef>

struct BlockHeader {
    size_t size;
    bool is_free;
    BlockHeader* next;
};

// Global pointer to the head of the free list
extern BlockHeader* free_list;

void* my_malloc_internal(size_t size);
void my_free_internal(void* ptr);
void* request_memory_from_os(size_t size);
void handle_error(const char* msg);

#endif // MY_ALLOCATOR_INTERNAL_H
