/**
 * @file internal.h
 * @brief Internal structures and functions for custom memory allocator
 * 
 * Contains internal data structures, global variables, and function
 * declarations used by the custom memory allocator implementation.
 */

#ifndef MY_ALLOCATOR_INTERNAL_H
#define MY_ALLOCATOR_INTERNAL_H

#include <cstddef>

/**
 * Memory block header structure.
 * Contains metadata for each allocated/free memory block.
 */
struct BlockHeader {
    size_t size;        ///< Size of the memory block in bytes
    bool is_free;       ///< Whether the block is free or allocated
    BlockHeader* next;  ///< Pointer to next block in free list
};

/**
 * Global pointer to the head of the free list.
 * Used to track available memory blocks for reuse.
 */
extern BlockHeader* free_list;

/**
 * Internal malloc implementation.
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or nullptr if allocation fails
 */
void* my_malloc_internal(size_t size);

/**
 * Internal free implementation.
 * @param ptr Pointer to memory block to free
 */
void my_free_internal(void* ptr);

/**
 * Requests memory from operating system.
 * @param size Number of bytes to request
 * @return Pointer to allocated memory, or MAP_FAILED on error
 */
void* request_memory_from_os(size_t size);

/**
 * Handles system errors.
 * @param msg Error message to display
 */
void handle_error(const char* msg);

#endif // MY_ALLOCATOR_INTERNAL_H
