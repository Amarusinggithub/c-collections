# Dynamic Array in C

A generic dynamic array implementation in C, built as a learning project to understand manual memory management, pointer arithmetic, and generic data structures.

## What it is

A resizable array that can store any data type using `void*`. When the array runs out of capacity it automatically doubles in size via `realloc`. The implementation avoids relying on any third-party libraries — just the C standard library.

## Core concepts covered

- Heap allocation with `malloc`, `calloc`, and `realloc`
- Generic storage using `void*` and `element_size`
- Manual pointer arithmetic with `(char*)` casting
- Value copying with `memcpy` and `memmove`
- Struct design for encapsulating array state

## Data structure

```c
typedef struct {
    size_t length;       // number of elements currently stored
    size_t capacity;     // max elements before realloc
    size_t element_size; // size of each element in bytes
    void  *items;        // pointer to the data on the heap
} Array;
```

## Functions

| Function | Description |
| --- | --- |
| `append` | Add an element to the end, doubling capacity if full |
| `remove_item` | Remove all occurrences of a value |
| `remove_at` | Remove the element at a given index |

## Planned

See [agents.md](agents.md) for the full list of functions still to be implemented.

## Build & Ececute

```sh
gcc src/main.c -o src/main && cd src && ./main
```
