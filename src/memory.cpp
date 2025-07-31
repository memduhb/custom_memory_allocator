#include "internal.h"
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

/* Request memory from the OS
    - Allocates memory using mmap for the custom allocator.
    - Aligns the size to the nearest page boundary.
    - Returns a pointer to the allocated memory.
    - The request_memory_from_os function is the internal interface for memory allocation.
*/

void handle_error(const char* msg) {
    perror(msg); 
    exit(255);
}

void* request_memory_from_os(std::size_t size) {
    size_t page_size = getpagesize();
    size_t aligned_size = ((size + sizeof(BlockHeader) + page_size - 1) / page_size) * page_size;

    void* ptr = mmap(NULL, aligned_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0u);
    std::cout << "[request_memory_from_os] Total memory requested from OS: "
              << aligned_size << " bytes (page aligned)\n";

    if (ptr == MAP_FAILED)
        handle_error("mmap");

    return ptr;
}
