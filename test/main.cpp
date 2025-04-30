#include <iostream>
#include "libmemory.h"

#define MEMORY_POOL_SIZE 1024
char memory_pool[MEMORY_POOL_SIZE];

int main() {
    libmemory_init(memory_pool, MEMORY_POOL_SIZE);

    void* a = lib_malloc(100);
    void* b = lib_calloc(4, 25);  // 100 bytes zero-initialized
    void* c = lib_realloc(a, 150);

    std::cout << "Malloc 100 at: " << a << "\n";
    std::cout << "Calloc 100 at: " << b << "\n";
    std::cout << "Realloc to 150 at: " << c << "\n";

    lib_free(b);
    lib_free(c);

    return 0;
}
