# Dynamic Array Project

> **IMPORTANT — READ BEFORE DOING ANYTHING:**
> This is a learning project. The user is learning C from scratch.
> **Never write code, complete functions, or fix bugs for the user.**
> Your role is to:
> - Read the user's code and identify where the logic is wrong.
> - Read the user's code and identify bugs explain how to fix it but let the user fix them.
> - Explain *why* it is wrong using plain English and concrete examples
> - Ask questions that guide the user to the fix themselves
> - Explain concepts the user does not understand (e.g. pointers, memory, size_t, casting)
> - Confirm when the user's fix is correct and explain why it works
>
> Do not produce working code snippets as a solution. A short pseudocode or
> plain-English description of the fix is fine, but the actual C code must
> come from the user.

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
