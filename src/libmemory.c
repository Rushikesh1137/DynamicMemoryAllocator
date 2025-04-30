#include "libmemory.h"

typedef struct Block {
    size_t size;
    int free;
    struct Block *next;
} Block;

static Block *free_list = NULL;
static void *memory_start = NULL;

void libmemory_init(void *memory_pool, size_t pool_size) {
    memory_start = memory_pool;
    free_list = (Block *)memory_pool;
    free_list->size = pool_size - sizeof(Block);
    free_list->free = 1;
    free_list->next = NULL;
}

void* lib_malloc(size_t size) {
    Block *curr = free_list;

    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size >= size + sizeof(Block) + 1) {
                Block *new_block = (Block *)((char *)curr + sizeof(Block) + size);
                new_block->size = curr->size - size - sizeof(Block);
                new_block->free = 1;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }

            curr->free = 0;
            return (char *)curr + sizeof(Block);
        }

        curr = curr->next;
    }

    return NULL;
}

void lib_free(void *ptr) {
    if (!ptr) return;

    Block *block = (Block *)((char *)ptr - sizeof(Block));
    block->free = 1;

    // Optional: Coalesce free blocks
    Block *curr = free_list;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += sizeof(Block) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

#include <string.h> // for memset and memcpy

void* lib_calloc(size_t num, size_t size) {
    size_t total_size = num * size;
    void* ptr = lib_malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}

void* lib_realloc(void* ptr, size_t new_size) {
    if (!ptr) {
        return lib_malloc(new_size);  // same as malloc
    }

    Block* old_block = (Block *)((char *)ptr - sizeof(Block));
    if (old_block->size >= new_size) {
        return ptr;  // current block is big enough
    }

    void* new_ptr = lib_malloc(new_size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, old_block->size);
        lib_free(ptr);
    }

    return new_ptr;
}
