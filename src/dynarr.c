/**
 * @file main.c
 * @author Amar Campbell
 * @brief Implementation of dynamic array functions
 * @copyright Copyright (c) 2026 Amar
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarr.h"


/**
 * @brief appends items to the array
 * 
 * @param arr pointer to the array
 * @param value Pointer to the value to append
 * @return 0 on success or 1 on error 
 */
int  append(Array *arr, const void* value){
    if(arr==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if(arr->length==arr->capacity){
        void* new_arr=realloc(arr->items, 2*arr->capacity*arr->element_size);
        if(arr==NULL){
        fprintf(stderr,"[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }
        arr->items=new_arr;
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
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    void* new_arr= calloc(arr->length,arr->element_size);
    if(new_arr == NULL){
        fprintf(stderr,"[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
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
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }
    void * new_arr= calloc(arr->capacity, arr->element_size);

    if(new_arr==NULL){
        fprintf(stderr,"[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
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
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
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
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
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
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
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
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if(index >arr->length){
        perror("[ERROR] the index is out of bound");
        return 1;
    }

    void * new_arr= malloc(2*arr->capacity* arr->element_size);

    if(new_arr==NULL){
        fprintf(stderr,"[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
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


/**
 * @brief reverse  the order of the array
 * 
 * @param arr  Pointer to the array
 * @return ) for success or 1 for error
 */
int reverse(Array *arr){
    if(arr ==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    void* new_arr= calloc(arr->length, arr->element_size);

    if(new_arr == NULL){
        fprintf(stderr,"[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    size_t j=0;
    for(int i=arr->length-1; i>=0;--i){
        memmove((char*)new_arr+j*arr->element_size,(char*)arr->items+i*arr->element_size,arr->element_size);
        ++j;
    }

free(arr->items);
arr->items=new_arr;
return 0;
}



/**
 * @brief gets the index of the given value in the array
 * 
 * @param arr Pointer to the array
 * @param value Pointer to the given value
 * @return 1 for  error, the index of the value if successfully and -1 if it did not find the value
 */
int index_of(Array *arr, const void *value){
    if(arr ==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    for(size_t i=0; i<arr->length;++i){
        if(memcmp(value,(char*)arr->items+i*arr->element_size, arr->element_size)==0){
            return (int)i;
        }
    }
    
    return -1;
}


/**
 * @brief shrink the array capacity to fit the length
 * 
 * @param arr Pointer to arr
 * @return 0 for success or 1 for error 
 */
int shrink_to_fit(Array *arr){
    if(arr ==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if(arr->capacity ==arr->length){
        return 0;
    }

    void* new_arr= realloc(arr->items,arr->length *arr->element_size);
    if(new_arr==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    arr->items=new_arr;
    arr->capacity=arr->length;
    return 0;
}


/**
 * @brief 
 * 
 * @param arr Pointer to the array.
 * @param cmp Pointer to a function (Function pointer) that compares 2 value and return a int.
 *            less than 0 (negative int) if the first element is smaller,
 *            0 if they are equal or 1 if the first element is larger.
 * @return 0 forsuccess or 1 for error.  
 */
int sort(Array * arr, const Compare cmp){
    if(arr ==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

        if(cmp ==NULL){
        fprintf(stderr,"[Error] the cmp function is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    void * swap= malloc(arr->element_size);
    if(swap ==NULL){
        fprintf(stderr,"[Error] the swap is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }
    for(size_t i =0; i<arr->length;i++){
        for(size_t j=i+1; j<arr->length; j++){
            if(cmp((char*)arr->items+i*arr->element_size,(char*)arr->items+j*arr->element_size)<=0){
                continue;
            }else {
                memmove(swap,(char*)arr->items+i*arr->element_size, arr->element_size);
                memmove((char*)arr->items+i*arr->element_size,(char*)arr->items+j*arr->element_size, arr->element_size);
                memmove((char*)arr->items+j*arr->element_size,swap,arr->element_size);
            }
        }
    }

    free(swap);
    return 0;
}


/**
 * @brief apply the function to each element of the array
 * 
 * @param arr Pointer to the array 
 * @param fn Function pointer that do something with the value in the array. 
 * @return 0 for success or 1 for error 
 */
int map(Array *arr, const Function fn){
    if(arr ==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }

    if(fn ==NULL){
        fprintf(stderr,"[Error] the fn function is null in%s at line# %d", __FILE__, __LINE__);
        return 1;
    }
    for(size_t i=0; i<arr->length; i++){
        fn((char*)arr->items+i*arr->element_size);
    }
    return 0;
}


/**
 * @brief creates a new array with elements that pass the predicate
 * 
 * @param arr Pointer to array
 * @param pred Function pointer that checks if value pass the predicate.
                0 if true and 1 if false
 * @return void* Pointer to the new array
 */
Array* filter(const Array *arr, const Predicate pred){
    if(arr ==NULL){
        fprintf(stderr,"[Error] the array is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    if(pred ==NULL){
        fprintf(stderr,"[Error] the predicate function is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    Array * new_arr= malloc( sizeof(Array));
    if(new_arr ==NULL){
        fprintf(stderr,"[Error] the new array is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    new_arr->items= calloc(arr->length, arr->element_size);
    if(new_arr->items ==NULL){
        fprintf(stderr,"[Error] the new array items is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }

    size_t j=0;
    for(size_t i=0;i<arr->length;i++){
        if(pred((char*)arr->items+i*arr->element_size)!=0) continue;
        memcpy((char*)new_arr->items+j*arr->element_size,(char*)arr->items+i*arr->element_size, arr->element_size);
        j++;
    }

    if(j==0){
        free(new_arr->items);
        new_arr->items=NULL;
        new_arr->length=j;
        new_arr->capacity=new_arr->length;
        new_arr->element_size=arr->element_size;
        return new_arr;
    }
    
    void* buffer_arr= realloc(new_arr->items,j*arr->element_size);
    if(buffer_arr ==NULL){
        fprintf(stderr,"[Error] the buffer array is null in%s at line# %d", __FILE__, __LINE__);
        exit(1);
    }
    new_arr->items=buffer_arr;
    new_arr->length=j;
    new_arr->capacity=new_arr->length;
    new_arr->element_size=arr->element_size;

    return new_arr;
}
