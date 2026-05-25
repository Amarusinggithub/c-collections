/**
 * @file llist.h
 * @author Amar Campbell
 * @brief This is the dynamic array declaration header file
 * @copyright Copyright (c) 2026 Amar
 */

#ifndef INCLUDED_LLIST
#define INCLUDED_LLIST

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    LL_ERROR_RETURN_SUCCESS,
    LL_ERROR_RETURN_ERROR,
} LL_ERROR_CODES;

typedef struct node {
    void* data;
    struct node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t length;
    size_t element_size;
} LinkList;


//Aliases
typedef LinkList* LinkListPtr;
typedef Node* NodePtr;


/***Function Prototypes/Declarations***/
/**
 * @brief Adds another node to the end of the list
 *
 * @param list Pointer to the linklist
 * @param value the value to add appended note
 * @return int - 0 for success or 1 for error
 */
LL_ERROR_CODES ll_append(LinkListPtr list, const void* value);

/**
 * @brief
 *
 * @param list
 * @param idx
 * @param shouldStopAtIdx
 * @return LL_ERROR_CODES
 */

/**
 * @brief Prints the value for each node in the list
 *
 * @param list Pointer to the list
 * @return LL_ERROR_CODES
 */
LL_ERROR_CODES ll_print_list(LinkListPtr list);

/**
 * @brief iteratively free the list
 *
 * @param list Pinter to the list to free
 * @return LL_ERROR_CODES
 */
LL_ERROR_CODES ll_free_list(LinkListPtr list);

#endif