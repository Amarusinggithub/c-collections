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
#include <stdint.h>

typedef enum {
    LL_ERROR_RETURN_SUCCESS,
    LL_ERROR_RETURN_ERROR,
    LL_ERROR_OUT_OF_BOUNDS,
    LL_ERROR_NOT_FOUND,
    LL_ERROR_EMPTY_LIST
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

// Aliases
typedef LinkList* LinkListPtr;
typedef Node* NodePtr;

// Function Prototypes/Declarations

/**
 * @brief Adds another node to the end of the list
 *
 * @param list Pointer to the linklist
 * @param value the value to add appended note
 * @return int - 0 for success or 1 for error
 */
LL_ERROR_CODES ll_append(LinkListPtr list, const void* value);

/**
 * @brief Adds another node to the start of the list
 *
 * @param list Pointer to the list
 * @param value the value to be added to the list
 * @return LL_ERROR_CODES -> error code enum
 */
LL_ERROR_CODES ll_prepend(LinkListPtr list, const void* value);

/**
 * @brief Prints the value for each node in the list
 *
 * @param list Pointer to the list
 * @return LL_ERROR_CODES-> error code enum
 */
LL_ERROR_CODES ll_print_list(LinkListPtr list);

/**
 * @brief iteratively free the list
 *
 * @param list Pinter to the list to free
 * @return LL_ERROR_CODES-> error code enum
 */
LL_ERROR_CODES ll_free_list(LinkListPtr list);

/**
 * @brief remove a node from the list containing the given value
 *
 * @param list Pointer to the list
 * @param value the value whose node should be to remove from the list
 * @return LL_ERROR_CODES-> error code enum
 */
LL_ERROR_CODES ll_remove(LinkListPtr list, const void* value);

/**
 * @brief return the node at the index
 *
 * @param list Pointer to the list
 * @param index the position of the node to return
 * @return NodePtr -> a pointer to the node or NULL
 */
NodePtr ll_get(LinkListPtr list, size_t index);

/**
 * @brief get the the length of lis
 *
 * @param list Pointer to the list
 * @return int64_t -> length of list
 */
inline int64_t ll_length(LinkListPtr list);

/**
 * @brief checks if list contins the a node with the value
 *
 * @param list Pointer to the list
 * @param value the to check for
 * @return LL_ERROR_CODES-> error code enum
 */
LL_ERROR_CODES ll_contains(LinkListPtr list, const void* value);

/**
 * @brief insert a node with the given value at a given index
 *
 * @param list Pointer to the list
 * @param idx The position to be inserted at.
 * @param value the value to add to the node being inserted
 * @return  LL_ERROR_CODES-> error code enum
 */
LL_ERROR_CODES ll_insert_at(LinkListPtr list, size_t idx, const void* value);

/**
 * @brief reverse the order of the list
 *
 * @param list Pointer to the list to be reversed
 * @return  LL_ERROR_CODES-> error code enum
 */
LL_ERROR_CODES ll_reverse(LinkListPtr list);

/**
 * @brief get the the string for the LL_ERROR_CODES
 *
 * @param code LL_ERROR_CODES-> error code enum
 * @return char*
 */
inline char* ll_errors_to_str(LL_ERROR_CODES code);
#endif