# 🧠 libmemory – Embedded Memory Allocator in C/C++

`libmemory` is a lightweight memory management library designed for **embedded systems** or **bare-metal environments** without an operating system. It provides custom implementations of `malloc()`, `free()`, `calloc()`, and `realloc()` using a fixed-size memory pool.

---

## 🚀 Features

- Works without an OS or dynamic system heap
- First-fit dynamic memory allocation strategy
- Manual memory pool initialization
- Block splitting and coalescing
- Functions: `malloc`, `free`, `calloc`, `realloc`
- Can be used in C and tested from C++

---

## 🛠️ Project Structure




---

## 🧪 How It Works

1. A large block of memory (e.g., 1024 bytes) is allocated statically.
2. `libmemory_init()` initializes this block as the custom heap.
3. `lib_malloc()` splits free blocks as needed.
4. `lib_free()` marks blocks as free and merges adjacent free blocks.
5. `lib_calloc()` allocates and zeroes memory.
6. `lib_realloc()` resizes memory with optional move-and-copy.

---

## 🧵 Example

```cpp
#define MEMORY_POOL_SIZE 1024
char memory_pool[MEMORY_POOL_SIZE];

libmemory_init(memory_pool, MEMORY_POOL_SIZE);

void* a = lib_malloc(100);
void* b = lib_calloc(4, 25);
void* c = lib_realloc(a, 200);

lib_free(b);
lib_free(c);


🧠 Initial Memory Layout (Before Any Allocation)
sql
Copy
Edit
+---------------------------------------------------------------+
|                      Entire Free Block (1024 bytes)           |
+---------------------------------------------------------------+
✅ After lib_malloc(100)
sql
Copy
Edit
+--------------------------+------------------------------------+
| Allocated (100 bytes)    | Free Block (924 bytes)             |
+--------------------------+------------------------------------+
✅ After lib_malloc(200)
sql
Copy
Edit
+--------------------------+-----------------------+------------+
| Allocated (100 bytes)    | Allocated (200 bytes) | Free (724) |
+--------------------------+-----------------------+------------+
✅ After lib_free(100-byte block)
sql
Copy
Edit
+--------------------------+-----------------------+------------+
| Free (100 bytes)         | Allocated (200 bytes) | Free (724) |
+--------------------------+-----------------------+------------+
✅ After lib_malloc(50) → Reuses first free block (100 bytes → split)
sql
Copy
Edit
+-----------+--------------+-----------------------+------------+
| Alloc(50) | Free(50)     | Allocated (200 bytes) | Free (724) |
+-----------+--------------+-----------------------+------------+
✅ After lib_calloc(2, 100) → Allocates 200 bytes and zeroes memory
sql
Copy
Edit
+-----------+--------------+-----------------------+------------------+--------+
| Alloc(50) | Free(50)     | Allocated (200 bytes) | Allocated (200)  | Free   |
+-----------+--------------+-----------------------+------------------+--------+
✅ After lib_free(50) and lib_free(50) → Merging Free Blocks
sql
Copy
Edit
+--------------------------+-----------------------+------------------+--------+
| Merged Free (100 bytes)  | Allocated (200 bytes) | Allocated (200)  | Free   |
+--------------------------+-----------------------+------------------+--------+
✅ After lib_realloc(ptr_200, 300) → New Alloc + Copy + Free old
sql
Copy
Edit
+--------------------------+-----------------------+------------------+----------------+
| Free (100)               | Free (200)            | Alloc (300)      | Free (remaining)|
+--------------------------+-----------------------+------------------+----------------+