#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include <cstddef>

void* my_malloc(std::size_t size);
void my_free(void* ptr);
void* my_calloc(std::size_t num, std::size_t size);
void* my_realloc(void* ptr, std::size_t size);

#endif // MY_ALLOCATOR_H
