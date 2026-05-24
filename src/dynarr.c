/**
 * @file main.c
 * @author Amar Campbell
 * @brief Implementation of dynamic array functions
 * @copyright Copyright (c) 2026 Amar
 */
#include "dynarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int append(ArrayPtr arr, const void* value) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if (arr->length == arr->capacity) {
        void* new_arr = realloc(arr->items, 2 * arr->capacity * arr->element_size);
        if (new_arr == NULL) {
            fprintf(stderr, "[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
            return 1;
        }
        arr->items    = new_arr;
        arr->capacity = 2 * arr->capacity;
    }
    memmove((char*)arr->items + (arr->length * arr->element_size), value, arr->element_size);

    arr->length++;

    return 0;
}

int remove_item(ArrayPtr arr, const void* value) {

    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    void* new_arr = calloc(arr->length, arr->element_size);
    if (new_arr == NULL) {
        fprintf(stderr, "[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    size_t j = 0;
    for (size_t i = 0; i < arr->length; i++) {
        if (memcmp((char*)arr->items + (i * arr->element_size), (char*)value, arr->element_size) !=
            0) {
            memmove((char*)new_arr + (j * arr->element_size),
                    (char*)arr->items + (i * arr->element_size), arr->element_size);
            j++;
        }
    }

    arr->length = j;
    free(arr->items);
    arr->items = new_arr;
    return 0;
}

int remove_at(ArrayPtr arr, const size_t index) {

    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }
    void* new_arr = calloc(arr->capacity, arr->element_size);

    if (new_arr == NULL) {
        fprintf(stderr, "[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    size_t j = 0;
    for (size_t i = 0; i < arr->length; i++) {
        if (i != index) {
            memmove((char*)new_arr + (j * arr->element_size),
                    (char*)arr->items + (i * arr->element_size), arr->element_size);
            j++;
        }
    }

    arr->length = j;
    free(arr->items);
    arr->items = NULL;
    arr->items = new_arr;
    return 0;
}

void* get(ArrayPtr arr, const size_t index) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    if (index >= arr->length) {
        perror("[ERROR] the index is out of bound");
        exit(1);
    }
    return (char*)arr->items + (index * arr->element_size);
}

int set(ArrayPtr arr, const size_t index, const void* value) {

    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if (index >= arr->length) {
        perror("[ERROR] the index is out of bound");
        return 1;
    }
    memmove((char*)arr->items + (index * arr->element_size), value, arr->element_size);

    return 0;
}

int contains(ArrayPtr arr, const void* value) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if (value == NULL) {
        fprintf(stderr, "[Error] the value is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    for (size_t i = 0; i < arr->length; i++) {
        if (memcmp((char*)arr->items + (i * arr->element_size), value, arr->element_size) == 0) {
            return 0;
        }
    }
    return -1;
}

int insert_at(ArrayPtr arr, const size_t index, const void* value) {

    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if (index > arr->length) {
        perror("[ERROR] the index is out of bound");
        return 1;
    }

    void* new_arr = malloc(2 * arr->capacity * arr->element_size);

    if (new_arr == NULL) {
        fprintf(stderr, "[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    ++arr->length;
    size_t j = 0;
    for (size_t i = 0; i < arr->length; i++) {
        if (index == i) {
            memmove((char*)new_arr + (i * arr->element_size), value, arr->element_size);
            continue;
        }
        memmove((char*)new_arr + (i * arr->element_size),
                (char*)arr->items + (j * arr->element_size), arr->element_size);
        j++;
    }

    free(arr->items);
    arr->items    = new_arr;
    arr->capacity = 2 * arr->capacity;
    return 0;
}

int reverse(ArrayPtr arr) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    void* new_arr = calloc(arr->length, arr->element_size);

    if (new_arr == NULL) {
        fprintf(stderr, "[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    size_t j = 0;
    for (int i = (int)arr->length - 1; i >= 0; --i) {
        memmove((char*)new_arr + (j * arr->element_size),
                (char*)arr->items + (i * arr->element_size), arr->element_size);
        ++j;
    }

    free(arr->items);
    arr->items = new_arr;
    return 0;
}

int index_of(ArrayPtr arr, const void* value) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    for (size_t i = 0; i < arr->length; ++i) {
        if (memcmp(value, (char*)arr->items + (i * arr->element_size), arr->element_size) == 0) {
            return (int)i;
        }
    }

    return -1;
}

int shrink_to_fit(ArrayPtr arr) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if (arr->capacity == arr->length) {
        return 0;
    }

    void* new_arr = realloc(arr->items, arr->length * arr->element_size);
    if (new_arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    arr->items    = new_arr;
    arr->capacity = arr->length;
    return 0;
}

int sort(ArrayPtr arr, const Compare cmp) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if (cmp == NULL) {
        fprintf(stderr, "[Error] the cmp function is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    void* swap = malloc(arr->element_size);
    if (swap == NULL) {
        fprintf(stderr, "[Error] the swap is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }
    for (size_t i = 0; i < arr->length; i++) {
        for (size_t j = i + 1; j < arr->length; j++) {
            if (cmp((char*)arr->items + (i * arr->element_size),
                    (char*)arr->items + (j * arr->element_size)) <= 0) {
                continue;
            }
            memmove(swap, (char*)arr->items + (i * arr->element_size), arr->element_size);
            memmove((char*)arr->items + (i * arr->element_size),
                    (char*)arr->items + (j * arr->element_size), arr->element_size);
            memmove((char*)arr->items + (j * arr->element_size), swap, arr->element_size);
        }
    }

    free(swap);
    return 0;
}

int map(ArrayPtr arr, const Function func) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if (func == NULL) {
        fprintf(stderr, "[Error] the fn function is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }
    for (size_t i = 0; i < arr->length; i++) {
        func((char*)arr->items + (i * arr->element_size));
    }
    return 0;
}

ArrayPtr filter(const ArrayPtr arr, const Predicate pred) {
    if (arr == NULL) {
        fprintf(stderr, "[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    if (pred == NULL) {
        fprintf(stderr, "[Error] the predicate function is null in%s at line# %d", __FILE__,
                __LINE__);
        exit(1);
    }

    ArrayPtr new_arr = malloc(sizeof(Array));
    if (new_arr == NULL) {
        fprintf(stderr, "[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    new_arr->items = calloc(arr->length, arr->element_size);
    if (new_arr->items == NULL) {
        fprintf(stderr, "[Error] the new array items is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    size_t j = 0;
    for (size_t i = 0; i < arr->length; i++) {
        if (pred((char*)arr->items + (i * arr->element_size)) != 0) {
            continue;
        }
        memcpy((char*)new_arr->items + (j * arr->element_size),
               (char*)arr->items + (i * arr->element_size), arr->element_size);
        j++;
    }

    if (j == 0) {
        free(new_arr->items);
        new_arr->items        = NULL;
        new_arr->length       = j;
        new_arr->capacity     = new_arr->length;
        new_arr->element_size = arr->element_size;
        return new_arr;
    }

    void* buffer_arr = realloc(new_arr->items, j * arr->element_size);
    if (buffer_arr == NULL) {
        fprintf(stderr, "[Error] the buffer array is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }
    new_arr->items        = buffer_arr;
    new_arr->length       = j;
    new_arr->capacity     = new_arr->length;
    new_arr->element_size = arr->element_size;

    return new_arr;
}
