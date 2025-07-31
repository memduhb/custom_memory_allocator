/**
 * @file my_allocator.h
 * @brief Custom memory allocator public interface
 * 
 * Provides custom implementations of standard memory allocation functions:
 * malloc, free, calloc, and realloc with thread safety and memory reuse.
 */

#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include <cstddef>

/**
 * Allocates memory block of specified size.
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or nullptr if allocation fails
 */
void* my_malloc(std::size_t size);

/**
 * Deallocates previously allocated memory block.
 * @param ptr Pointer to memory block to free
 */
void my_free(void* ptr);

/**
 * Allocates memory for array and initializes to zero.
 * @param num Number of elements
 * @param size Size of each element in bytes
 * @return Pointer to zero-initialized memory, or nullptr if allocation fails
 */
void* my_calloc(std::size_t num, std::size_t size);

/**
 * Resizes memory block with data preservation.
 * @param ptr Pointer to existing memory block
 * @param size New size in bytes
 * @return Pointer to resized memory block, or nullptr if reallocation fails
 */
void* my_realloc(void* ptr, std::size_t size);

#endif // MY_ALLOCATOR_H
