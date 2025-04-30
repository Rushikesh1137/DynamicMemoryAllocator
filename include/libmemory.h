#ifndef LIBMEMORY_H
#define LIBMEMORY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void libmemory_init(void *memory_pool, size_t pool_size);
void* lib_malloc(size_t size);
void* lib_calloc(size_t num, size_t size);
void* lib_realloc(void* ptr, size_t new_size);

void lib_free(void *ptr);

#ifdef __cplusplus
}
#endif

#endif // LIBMEMORY_H
