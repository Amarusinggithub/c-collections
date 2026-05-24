/**
 * @file main.c
 * @author Amar Campbell
 * @brief Implementation of dynamic array in c
 * @copyright Copyright (c) 2026 Amar
 */

#include "dynarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

int main(int argc, char *argv[]) {

  Array arr = {0, SIZE, sizeof(int), NULL};
  arr.items = (int *)calloc(arr.capacity, arr.element_size);

  if (arr.items == NULL) {
    perror("Failed to allocate memory on the heap!!");
    return 1;
  }

  for (size_t i = 0; i < arr.capacity; i++) {
    memcpy((char *)arr.items + i * arr.element_size, &i, arr.element_size);
    arr.length = i + 1;
    printf("this is at arr[%zd]: %2d\n", i,
           *(int *)((char *)arr.items + i * arr.element_size));
  }
  int num = 2;
  int num2 = 12;

  printf("this is at arr[2]: %2d\n",
         *(int *)((char *)arr.items + num * arr.element_size));
  printf("This is the capacity of the array: %zd\n", arr.capacity);
  printf("This is the length of the array: %zd\n", arr.length);
  reverse(&arr);
  printf("reverse:\n");
  for (size_t i = 0; i < arr.length; i++) {
    printf("this is at arr[%zd]: %2d\n", i,
           *(int *)((char *)arr.items + i * arr.element_size));
  }

  free(arr.items);
  return 0;
}
