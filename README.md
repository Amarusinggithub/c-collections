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


---

## Functions TODO

- [x] `append(Array *arr, const void *value)` — add an element to the end, doubling capacity if full
- [x] `remove_item(Array *arr, const void *value)` — remove all occurrences of a value
- [x] `remove_at(Array *arr, int index)` — remove the element at a given index
- [ ] `get(Array *arr, int index)` — return a pointer to the element at an index, with bounds checking
- [ ] `set(Array *arr, int index, void *value)` — overwrite an element at an index
- [ ] `contains(Array *arr, void *value)` — return 1 if value exists, 0 if not
- [ ] `insert_at(Array *arr, int index, void *value)` — insert at a position, shifting everything after it right
- [ ] `reverse(Array *arr)` — reverse the array in place
- [ ] `index_of(Array *arr, void *value)` — return the index of the first match, -1 if not found
- [ ] `sort(Array *arr, int (*cmp)(const void*, const void*))` — sort using a comparator function pointer
- [ ] `map(Array *arr, void (*fn)(void*))` — apply a function to every element in place
- [ ] `filter(Array *arr, int (*fn)(const void*))` — return a new array with only elements where the function returns true
- [ ] `shrink_to_fit(Array *arr)` — realloc capacity down to match length, reclaiming unused memory



## Build & Ececute

```sh
gcc src/main.c -o src/main && cd src && ./main
```
