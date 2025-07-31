#include "internal.h"
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

/**
 * OS-level memory management functions.
 * Handles memory requests from the operating system using mmap.
 */

/**
 * Handles system errors by printing error message and exiting.
 * @param msg Error message to display
 */
void handle_error(const char* msg) {
    perror(msg); 
    exit(255);
}

/**
 * Requests memory from the operating system using mmap.
 * Aligns size to page boundaries for efficiency.
 * @param size Number of bytes to request (will be page-aligned)
 * @return Pointer to allocated memory, or MAP_FAILED on error
 */
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
