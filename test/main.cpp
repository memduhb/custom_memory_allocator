#include <iostream>
#include <vector>
#include <cstring>     // for memset, memcpy
#include <climits>     // for SIZE_MAX

// Forward declarations from your allocator
void* my_malloc(size_t size);
void  my_free(void* ptr);
void* my_calloc(size_t num, size_t size);
void* my_realloc(void* ptr, size_t size);

//
// === TESTS ===
//

// TEST MALLOC
void test_my_malloc() {
    std::cout << "[TEST] my_malloc\n";
    void* ptr = my_malloc(128);
    if (ptr) {
        std::cout << "✅ my_malloc(128) succeeded.\n";
        std::memset(ptr, 0xAB, 128);
        my_free(ptr);
        std::cout << "✅ my_free on malloc'ed memory succeeded.\n";
    } else {
        std::cout << "❌ my_malloc(128) failed.\n";
    }
    std::cout << "\n";
}

// TEST CALLOC
void test_my_calloc() {
    std::cout << "[TEST] my_calloc\n";

    void* ptr1 = my_calloc(10, sizeof(int));
    if (ptr1) {
        std::cout << "✅ my_calloc(10, sizeof(int)) succeeded.\n";
        int* arr = static_cast<int*>(ptr1);
        bool all_zero = true;
        for (int i = 0; i < 10; ++i) {
            if (arr[i] != 0) {
                all_zero = false;
                break;
            }
        }
        std::cout << (all_zero ? "✅ Zero-initialization passed.\n" : "❌ Zero-initialization failed.\n");
        my_free(ptr1);
    }

    void* ptr2 = my_calloc(0, 100);
    std::cout << (!ptr2 ? "✅ my_calloc(0, 100) correctly returned nullptr.\n"
                        : "❌ my_calloc(0, 100) should return nullptr.\n");

    size_t huge = SIZE_MAX / 2 + 1;
    void* ptr3 = my_calloc(2, huge);
    std::cout << (!ptr3 ? "✅ Overflow test correctly returned nullptr.\n"
                        : "❌ Overflow test failed to detect overflow.\n");
    std::cout << "\n";
}

// TEST REALLOC
void test_my_realloc() {
    std::cout << "[TEST] my_realloc\n";

    void* ptr = my_malloc(64);
    if (!ptr) {
        std::cout << "❌ Initial malloc for realloc failed.\n";
        return;
    }

    std::memset(ptr, 0xCD, 64);
    void* bigger = my_realloc(ptr, 128);
    std::cout << (bigger ? "✅ Realloc to 128 bytes succeeded.\n"
                         : "❌ Realloc to 128 bytes failed.\n");

    void* smaller = my_realloc(bigger, 32);
    std::cout << (smaller ? "✅ Realloc to 32 bytes succeeded.\n"
                          : "❌ Realloc to 32 bytes failed.\n");

    my_free(smaller);
    std::cout << "✅ Freed after realloc.\n\n";
}

// TEST REALLOC with size 0
void test_realloc_zero_size() {
    std::cout << "[TEST] realloc with size 0\n";
    void* ptr = my_malloc(32);
    void* result = my_realloc(ptr, 0);
    std::cout << (!result ? "✅ realloc(ptr, 0) correctly returned nullptr (freed).\n"
                          : "❌ realloc(ptr, 0) should return nullptr.\n");
    std::cout << "\n";
}

// MASS ALLOCATION TEST
void test_mass_allocation() {
    std::cout << "[TEST] mass allocation\n";
    std::vector<void*> ptrs;
    for (int i = 0; i < 10000; ++i) {
        void* p = my_malloc(32);
        if (!p) {
            std::cout << "❌ Allocation failed at " << i << "\n";
            break;
        }
        ptrs.push_back(p);
    }
    for (void* p : ptrs) my_free(p);
    std::cout << "✅ Mass allocation/deallocation complete.\n\n";
}

// OPTIONAL: Double free test (should crash or be no-op if not protected)
void test_double_free() {
    std::cout << "[TEST] double free (⚠️ undefined behavior unless handled)\n";
    void* ptr = my_malloc(64);
    my_free(ptr);
    my_free(ptr); // Will crash if double free not protected
    std::cout << "✅ Double free test executed (⚠️ no check in place).\n\n";
}

// MASTER TEST RUNNER
void test_allocation_suite() {
    std::cout << "\n🔬 Running Full Test Suite\n";
    test_my_malloc();
    test_my_calloc();
    test_my_realloc();
    test_realloc_zero_size();
    test_mass_allocation();
    // test_double_free(); // Uncomment only if you handle double free!
    std::cout << "✅ All tests completed.\n";
}

int main() {
    test_allocation_suite();
    return 0;
}
