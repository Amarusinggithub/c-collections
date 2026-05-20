/**
 * @file main.c
 * @author Amar Campbell
 * @brief Implementation of dynamic array in c
 * @copyright Copyright (c) 2026 Amar
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarr.h"
#define SIZE 10


int main(int argc, char* argv[]){

    Array arr={0,SIZE,4,NULL};
    arr.items= (int*) calloc(arr.capacity,arr.element_size);

    if(arr.items == NULL){
        perror("Failed to allocate memory on the heap!!");
        return 1;
    }


    for(size_t i=0; i<arr.capacity;i++){
        memcpy((char*)arr.items+i*arr.element_size,&i,arr.element_size);
        arr.length=i+1;
        printf("this is at arr[%zd]: %2d\n",arr.length,*(int*)((char*)arr.items+i*arr.element_size));
    }

    int num=5;
    append(&arr,&num);

    printf("this is at arr[11]: %2d\n",*(int*)((char*)arr.items+11*arr.element_size));
    printf("This is the capacity of the array: %zd\n", arr.capacity);
    printf("This is the length of the array: %zd\n", arr.length);

    free(arr.items);
    return 0;
}


/**
 * @brief appends items to the array
 * 
 * @param arr pointer to the array
 * @param value Pointer to the value to append
 * @return 0 on success or 1 on error 
 */
int  append(Array *arr, const void* value){
    if(arr==NULL){
        fprintf(stderr,"[ERROR] the  array is null on line#: %d", __LINE__);
        return 1;
    }

    if(arr->length==arr->capacity){
        arr->items=realloc(arr->items, 2*arr->capacity*arr->element_size);
        arr->capacity=2*arr->capacity;
    }
    memcpy((char*)arr->items+arr->length*arr->element_size,value,arr->element_size);
    arr->length++;
    return 0;
}


/**
 * @brief find and remove all element of the array that is equal to value 
 * 
 * @param arr Pointer to the array
 * @param value pointer to the value to be removed from the array
 * @return 0 on success or 1 on error 
 */
int  remove_item(Array *arr, const void* value){

    if(arr==NULL){
        fprintf(stderr,"[ERROR] the  array is null on line#: %d", __LINE__);
        return 1;
    }

    void* new_arr= calloc(arr->length,arr->element_size);
    if(new_arr == NULL){
        perror("[Error] The new array is null!!");
        return 1;
    }

    size_t j=0;
    for(size_t i=0; i<arr->length;i++){
        if(memcmp((char*)arr->items+i*arr->element_size,(char*)value,arr->element_size)!=0){
            memmove((char*)new_arr+j*arr->element_size,(char*)arr->items+i*arr->element_size,arr->element_size);
            j++;
        }
    }

    arr->length=j;
    free(arr->items);
    arr->items=new_arr;
    return 0;
}


/**
 * @brief removes a value from the array at a given index
 * 
 * @param arr Pointer to the array
 * @param index the index of the item to be removed from the array
 * @return 0 on success or 1 on error 
 */
int remove_at(Array *arr, const size_t index){

    if(arr==NULL){
        fprintf(stderr,"[ERROR] the  array is null on line#: %d", __LINE__);
        return 1;
    }
    void * new_arr= calloc(arr->capacity, arr->element_size);

    if(new_arr==NULL){
        perror("[Error] The new array is null!!");
        return 1;
    }

    size_t j=0;
    for(size_t i=0; i<arr->length;i++){
        if(i!=index){
            memmove((char*)new_arr+j*arr->element_size,(char*)arr->items+i*arr->element_size, arr->element_size);
            j++;
        }
    }

    arr->length=j;
    free(arr->items);
    arr->items=new_arr;
    return 0;
}


/**
 * @brief get the value at a given index from the array
 * 
 * @param arr Pointer to the array
 * @param index the position of the item to be return
 * @return void* to the item at the index
 */
void * get(Array *arr, const size_t index){
        if(arr==NULL){
        fprintf(stderr,"[ERROR] the  array is null on line#: %d", __LINE__);
        exit(1);
    }

    if(index >=arr->length){
        perror("[ERROR] the index is out of bound");
        exit(1);
    }
    return (char*)arr->items+index*arr->element_size;
}


/**
 * @brief set the value at a given index of the array to a given value
 * 
 * @param arr Pointer to arr
 * @param index the position to set the value to in the array
 * @param value the value to be set at the index
 * @return 0 fro success or 1 for error 
 */
int set(Array *arr,const  size_t index, const void *value){

    if(arr==NULL){
        fprintf(stderr,"[ERROR] the  array is null on line#: %d", __LINE__);
        return 1;
    }

    if(index >=arr->length){
        perror("[ERROR] the index is out of bound");
        return 1; 
    }
    memmove((char*)arr->items+index*arr->element_size,
        value,arr->element_size);
    
    return 0;
}


/**
 * @brief checks if the array contains a given value
 * 
 * @param arr Pointer to the array
 * @param value the value to be checked  for
 * @return 0 for success or 1 for error  
 */
int contains(Array *arr, const void *value){
    if(arr==NULL){
        fprintf(stderr,"[ERROR] the  array is null on line#: %d", __LINE__);
        return 1;
    }
    for(size_t i=0; i< arr->length;i++){
        if(memcmp((char*)arr->items+i*arr->element_size,
            value,arr->element_size)==0) return 1;
    }
    return 0;
}

/**
 * @brief Insert a value at a given index, shifting elements right
 *
 * @param arr   Pointer to the array
 * @param index Position to insert at
 * @param value Pointer to the value to insert
 * @return 0 on success or 1 on error
 */
int insert_at(Array *arr,const size_t index, const void *value){

    if(arr==NULL){
        fprintf(stderr,"[ERROR] the  array is null on line#: %d", __LINE__);
        return 1;
    }

    if(index >arr->length){
        perror("[ERROR] the index is out of bound");
        return 1;
    }

    void * new_arr= malloc(2*arr->capacity* arr->element_size);

    if(new_arr==NULL){
        fprintf(stderr,"[ERROR] the new array is null on line#: %d", __LINE__);
        return 1;
    }

    ++arr->length;
    size_t j=0;
    for(size_t i=0; i<arr->length;i++){
        if(index==i){
            memmove((char*)new_arr+i*arr->element_size,value, arr->element_size);
            continue;
        }
    memmove((char*)new_arr+i*arr->element_size,(char*)arr->items+j*arr->element_size, arr->element_size);
    j++;
    }

    free(arr->items);
    arr->items=new_arr;
    arr->capacity=2*arr->capacity;
    return 0;
}

