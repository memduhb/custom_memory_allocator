#include "internal.h"
#include <mutex>
#include <iostream>
#include <cstring>
#include <climits>

/* Custom Calloc function
    - Allocates memory for arrays and zero-initializes all bytes
    - Implements integer overflow protection for size calculations
    - Handles edge cases: zero elements or zero size returns nullptr
    - Uses my_malloc_internal for allocation, then memset for initialization
    - Thread-safe with mutex protection
    - Returns pointer to zero-initialized memory
*/

extern std::mutex heap_mutex;

void* my_calloc(std::size_t num, std::size_t size) {
    std::lock_guard<std::mutex> lock(heap_mutex);

    if (num == 0 || size == 0) return nullptr;

    size_t total = num * size;
    if (size != 0 && total / size != num) {
        std::cerr << "[my_calloc] Integer overflow detected!\n";
        return nullptr;
    }

    void* memory = my_malloc_internal(total);
    if (!memory) return nullptr;

    std::memset(memory, 0, total);
    return memory;
}


