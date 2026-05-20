/**
 * @file dynarr.h
 * @author Amar Campbell
 * @brief This is the header that includes for dynamic array implementation
 * @copyright Copyright (c) 2026 Amar
 */

//#pragma once
#ifndef DYNARR_H
#define  DYNARR_H
#include <stddef.h>


// Array struct
typedef struct array {
    size_t length;
    size_t capacity;
    size_t element_size;
    void * items;
}Array;

// Function Prototypes
int  append(Array *arr, const void* value);
int remove_item(Array *arr, const void* value);
int remove_at(Array *arr,const size_t index);
void * get(Array *arr, const size_t index);
int set(Array *arr, const size_t index, const void *value);
int contains(Array *arr, const void *value);
int insert_at(Array *arr,const size_t index, const void *value);
#endif
