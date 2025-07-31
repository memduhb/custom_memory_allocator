# Custom Memory Allocator

A custom implementation of memory allocation functions (`malloc`, `free`, `calloc`, `realloc`) in C++. This project demonstrates memory management concepts by implementing a linked-list based allocator that requests memory from the operating system using `mmap`.

## Overview

This allocator implements memory allocation functions using a linked list of free blocks. It first searches for available free blocks before requesting new memory from the OS using `mmap`. The allocator uses block headers to track allocation status and maintains a free list for memory reuse. Each block contains metadata (size, free status, next pointer) and the allocator implements double-free protection.

## Features

- **malloc**: Searches free list for suitable blocks, requests from OS if none found
- **free**: Adds blocks to free list (LIFO) with double-free protection
- **calloc**: Allocates and zero-initializes memory with overflow protection
- **realloc**: Resizes allocations, reuses same block if smaller, copies data if larger
- **Memory reuse**: Maintains free list for efficient memory reuse
- **Double-free protection**: Detects and prevents double-free attempts
- **Page-aligned memory requests**: Uses `mmap` for OS memory allocation
- **Thread safety**: Uses mutex for concurrent access protection
- **Error handling**: Graceful handling of allocation failures and integer overflow

## Learning Outcomes

This project demonstrates key concepts in systems programming and memory management:

- **Memory Allocation**: Best-fit allocation with free list management
- **Data Structures**: Linked list for tracking free memory blocks
- **System Calls**: Direct OS memory interaction via `mmap`
- **Memory Safety**: Double-free detection and prevention
- **Concurrency**: Thread-safe allocation with mutex synchronization
- **Error Handling**: Edge case management and validation
- **Memory Layout**: Block headers and memory organization
- **Performance**: Efficient memory reuse and reallocation strategies

## Layout

```
custom_memory_allocator/
├── include/
│   └── my_allocator.h      # Public API header
├── src/
│   ├── internal.h          # Internal structures and functions
│   ├── memory.cpp          # OS memory request functions
│   ├── malloc.cpp          # malloc implementation
│   ├── free.cpp            # free implementation
│   ├── calloc.cpp          # calloc implementation
│   └── realloc.cpp         # realloc implementation
├── test/
│   └── main.cpp            # Test suite
└── Makefile                # Build configuration
```

## Build and Usage

### Build
```bash
make
```

### Run Tests
```bash
./test_allocator
```

### Clean
```bash
make clean
```

The test suite validates all allocation functions including edge cases like zero-size allocations, overflow detection, and memory reuse patterns. 