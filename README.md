# C Collections

A from scratch implementation of common data structures in C, built as a learning project to understand manual memory management, pointers, and how fundamental data structures work under the hood. No third-party libraries just the C standard library.

---

## Disclamer

All code within the src and include folders are hand written  by the author not AI. The code written in these folders are completed by the authors research,by utalizing the official docs, books, forums, youtube and blogs. AI was only use help guide the author in identifying bugs and logical errors and extending understanding of the different concepts covered. This is detailed in the [AGENTS.md](AGENTS.md).

Here is a list of other files that were extented by AI, but not fully completed by AI:

- .clang-tidy
- .clang-format
- CMakeLists.txt

Here is a list of  files that were Completely AI Generated:
- README.md (excluding this section)
- AGENTS.MD
---

## Table of Contents

- [C Collections](#c-collections)
  - [Disclamer](#disclamer)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Data Structures](#data-structures)
    - [Dynamic Array](#dynamic-array)
    - [Linked List](#linked-list)
    - [Stack](#stack)
    - [Queue](#queue)
    - [Circular Buffer / Ring Buffer](#circular-buffer--ring-buffer)
    - [Deque](#deque)
    - [Min / Max Heap](#min--max-heap)
    - [Binary Search Tree](#binary-search-tree)
    - [AVL Tree](#avl-tree)
    - [Trie](#trie)
    - [Hash Map](#hash-map)
    - [Hash Set](#hash-set)
    - [Graph — Adjacency List](#graph--adjacency-list)
    - [Graph — Adjacency Matrix](#graph--adjacency-matrix)
    - [B-Tree](#b-tree)
    - [B+ Tree](#b-tree-1)
    - [Bloom Filter](#bloom-filter)
    - [HyperLogLog](#hyperloglog)
  - [Build \& Execute](#build--execute)
    - [GCC (any platform)](#gcc-any-platform)
    - [CMake — Windows (PowerShell)](#cmake--windows-powershell)
    - [CMake — WSL / Linux](#cmake--wsl--linux)
    - [Choosing a build type](#choosing-a-build-type)

---

## Overview

Each data structure lives in its own header/source pair under `include/` and `src/`. The project grows one structure at a time — each one is fully implemented and tested before moving to the next.

**Core C concepts practised across this project:**

- Heap allocation with `malloc`, `calloc`, and `realloc`
- Generic storage using `void*` and `element_size`
- Manual pointer arithmetic with `(char*)` casting
- Value copying with `memcpy` and `memmove`
- Linked node structures and pointer chaining
- Recursive and iterative tree traversal
- Hashing and collision resolution
- Struct design for encapsulating state

---

## Data Structures

### Dynamic Array

**Files:** `include/dynarr.h` · `src/dynarr.c`

A resizable array that stores any data type via `void*`. Doubles in capacity automatically when full.

```c
typedef struct {
    size_t length;       // number of elements currently stored
    size_t capacity;     // max elements before realloc
    size_t element_size; // size of each element in bytes
    void  *items;        // pointer to the data on the heap
} Array;
```

| Function | Description |
| --- | --- |
| `append(arr, value)` | Add an element to the end, doubling capacity if full |
| `remove_item(arr, value)` | Remove all occurrences of a value |
| `remove_at(arr, index)` | Remove the element at a given index |
| `get(arr, index)` | Return a pointer to the element at an index, with bounds checking |
| `set(arr, index, value)` | Overwrite an element at an index |
| `contains(arr, value)` | Return 1 if value exists, 0 if not |
| `insert_at(arr, index, value)` | Insert at a position, shifting everything after it right |
| `reverse(arr)` | Reverse the array in place |
| `index_of(arr, value)` | Return the index of the first match, -1 if not found |
| `sort(arr, cmp)` | Sort using a comparator function pointer |
| `map(arr, fn)` | Apply a function to every element in place |
| `filter(arr, fn)` | Return a new array with only elements where fn returns true |
| `shrink_to_fit(arr)` | Realloc capacity down to match length, reclaiming unused memory |

**Status:** complete

---

### Linked List

**Files:** `include/llist.h` · `src/llist.c`

A singly linked list where each node holds a value and a pointer to the next node. No contiguous memory — each node is individually heap-allocated.

```c
typedef struct Node {
    void        *data;
    struct Node *next;
} Node;

typedef struct {
    Node  *head;
    size_t length;
    size_t element_size;
} LinkedList;
```

| Function | Description 
| --- | --- | --- |
| `ll_append(list, value)` | Add a node to the end
| `ll_prepend(list, value)` | Add a node to the front
| `ll_remove(list, value)` | Remove the first node matching value
| `ll_get(list, index)` | Return a pointer to the data at an index
| `ll_insert_at(list, index, value)` | Insert a node at a given position
| `ll_contains(list, value)` | Return 1 if value exists, 0 if not
| `ll_reverse(list)` | Reverse the list in place
| `ll_length(list)` | Return the number of nodes
| `ll_free(list)` | Free all nodes and reset the list

**Status:** in progress

---

### Stack

**Files:** `include/stack.h` · `src/stack.c`

A LIFO (last-in, first-out) structure. Push onto the top, pop from the top. Can be backed by a dynamic array or linked list.

**Status:** planned

---

### Queue

**Files:** `include/queue.h` · `src/queue.c`

A FIFO (first-in, first-out) structure. Enqueue at the back, dequeue from the front.

**Status:** planned

---

### Circular Buffer / Ring Buffer

**Files:** `include/cbuf.h` · `src/cbuf.c`

A fixed-size FIFO queue backed by a flat array. Instead of shifting elements, two indices (`head` and `tail`) chase each other around the array in a loop — no allocation after init. Commonly used in operating systems, device drivers, and network I/O buffers.

**Status:** planned

---

### Deque

**Files:** `include/deque.h` · `src/deque.c`

A double-ended queue. Elements can be pushed and popped from both the front and the back in O(1). Generalises both stack and queue.

**Status:** planned

---

### Min / Max Heap

**Files:** `include/heap.h` · `src/heap.c`

A complete binary tree stored in a flat array (no node pointers). The smallest (min-heap) or largest (max-heap) element is always at index 0. The foundation of priority queues and heap sort.

**Status:** planned

---

### Binary Search Tree

**Files:** `include/bst.h` · `src/bst.c`

A node-based tree where every left child is smaller than its parent and every right child is larger. Supports recursive insertion, search, deletion, and in-order/pre-order/post-order traversal.

**Status:** planned

---

### AVL Tree

**Files:** `include/avl.h` · `src/avl.c`

A self-balancing BST. After every insert or delete the tree checks its balance factor and performs rotations to keep height at O(log n), guaranteeing fast lookups even in worst-case input sequences.

**Status:** planned

---

### Trie

**Files:** `include/trie.h` · `src/trie.c`

A prefix tree where each node represents one character. Ideal for autocomplete, spell-check, and dictionary lookups. Insertion and search run in O(k) where k is the length of the key.

**Status:** planned

---

### Hash Map

**Files:** `include/hashmap.h` · `src/hashmap.c`

A key-value store backed by a hash table. A hash function maps keys to bucket indices; collisions are handled via chaining (linked list per bucket) or open addressing. Average O(1) get/set.

**Status:** planned

---

### Hash Set

**Files:** `include/hashset.h` · `src/hashset.c`

A hash map without values — just keys. O(1) average insert, delete, and membership test.

**Status:** planned

---

### Graph — Adjacency List

**Files:** `include/graph_list.h` · `src/graph_list.c`

A graph where each vertex stores a list of its neighbours. Memory-efficient for sparse graphs. Supports BFS and DFS traversal.

**Status:** planned

---

### Graph — Adjacency Matrix

**Files:** `include/graph_matrix.h` · `src/graph_matrix.c`

A graph represented as a 2D array where `matrix[i][j] = 1` means an edge exists between vertex i and j. Fast edge lookups at the cost of O(V²) memory. Better suited for dense graphs.

**Status:** planned

---

### B-Tree

**Files:** `include/btree.h` · `src/btree.c`

A self-balancing search tree where each node can hold many keys and have many children. Designed for systems where data lives on disk — a single node read can eliminate many branches at once, keeping the tree very short. Used in databases (SQLite, PostgreSQL) and file systems (NTFS, ext4). Each node holds up to `m-1` keys and up to `m` children, and all leaves sit at the same depth.

**Status:** planned

---

### B+ Tree

**Files:** `include/bplustree.h` · `src/bplustree.c`

A variant of the B-Tree where only leaf nodes store actual data — internal nodes hold keys purely for navigation. All leaf nodes are linked together in a list, making range queries fast. This is what most real-world databases use under the hood.

**Status:** planned

---

### Bloom Filter

**Files:** `include/bloom.h` · `src/bloom.c`

A probabilistic data structure that answers "have I seen this before?" using a bit array and multiple hash functions. Inserting an item sets several bits; checking an item tests those same bits. If any bit is 0 the item is definitely absent; if all are 1 it is probably present. False positives are possible but false negatives are not. Uses a tiny amount of memory compared to a hash set — the trade-off is the small chance of being wrong.

**Status:** planned

---

### HyperLogLog

**Files:** `include/hll.h` · `src/hll.c`

A probabilistic data structure that estimates how many unique items have been seen (cardinality) using a tiny fixed amount of memory — typically a few kilobytes regardless of how many items you process. It works by hashing each item and tracking the maximum number of leading zeros seen across buckets; statistically, more unique items produce longer runs of zeros. The estimate can be off by roughly 1-2% but uses orders of magnitude less memory than storing every unique item. Used in Redis (`PFADD`/`PFCOUNT`), BigQuery, and stream analytics pipelines.

**Status:** planned

---

## Build & Execute

### GCC (any platform)

```sh
gcc -I./include src/dynarr.c src/main.c -o src/main && cd src && ./main
```

### CMake — Windows (PowerShell)

```powershell
cmake -B build -S .
cmake --build build
.\build\Debug\c_collections.exe
```

### CMake — WSL / Linux

```sh
cmake -B build -S . -DCMAKE_C_COMPILER=gcc
cmake --build build
./build/c_collections
```

### Choosing a build type

The default build type is `Debug`. To switch, pass `-DCMAKE_BUILD_TYPE` when configuring:

```sh
# Debug (default) — includes debug symbols and sanitizers
cmake -DCMAKE_BUILD_TYPE=Debug -B build

# Release — optimized, no sanitizers
cmake -DCMAKE_BUILD_TYPE=Release -B build
```

If you have already configured the build directory and want to switch types, delete the `build/` folder first or pass the flag explicitly to override the cached value.
