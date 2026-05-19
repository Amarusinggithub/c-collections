#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct{
    size_t length;
    size_t capacity;
    size_t element_size;
    void * items;
} Array;

void append(Array *arr, const void* value);
int remove_item(Array *arr, const void* value);
int remove_at(Array *arr,const int index);


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

void append(Array *arr, const void* value){
    if(arr->length==arr->capacity){
        arr->items=realloc(arr->items, 2*arr->capacity*arr->element_size);
        arr->capacity=2*arr->capacity;
    }
    memcpy((char*)arr->items+arr->length*arr->element_size,value,arr->element_size);
    arr->length++;
}

int  remove_item(Array *arr, const void* value){
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
int remove_at(Array *arr, const int index){
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



