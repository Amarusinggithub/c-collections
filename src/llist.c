/**
 * @file llist.c
 * @author Amar Campbell
 * @brief This is the dynamic array declaration header file
 * @copyright Copyright (c) 2026 Amar
 */

#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LL_ERROR_CODES ll_append(LinkListPtr list, const void* value) {

    if (list == NULL) {
        (void)fprintf(stderr, "[ERROR] the list is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return LL_ERROR_RETURN_ERROR;
    }

    if (value == NULL) {
        (void)fprintf(stderr, "[ERROR] the value is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return LL_ERROR_RETURN_ERROR;
    }

    NodePtr new_node = (NodePtr)calloc(1, sizeof(Node));
    if (new_node == NULL) {
        (void)fprintf(stderr, "[ERROR] the new_node is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return LL_ERROR_RETURN_ERROR;
    }
    // set the new node members to null
    new_node->data = NULL;
    new_node->next = NULL;

    // copy the data to a buffer before and then set new node data to the buffer
    void* new_data = calloc(1, list->element_size);
    if (new_data == NULL) {
        (void)fprintf(stderr, "[ERROR] the new_data is null in file %s at line# %d", __FILE__,
                      __LINE__);
        free(new_node); // free new node in the case that new data is null before return
        return LL_ERROR_RETURN_ERROR;
    }
    memmove(new_data, value, list->element_size);
    new_node->data = new_data;

    
    if (list->head == NULL && list->length == 0) {
        //set the new node to the head if their is no head
        list->head = new_node;
        list->tail = NULL;
        ++list->length;
    } else if (list->head && list->head->next == NULL && list->length > 0) {
        // set the new node to the tail if their is a head
        list->head->next = new_node;
        list->tail       = new_node;
        ++list->length;
    } else {
        // traverse the list and set the tail to the new_node
        Node* current = list->head;
        while (true) {
            if (current->next == NULL) {
                current->next = new_node;
                list->tail    = new_node;
                ++list->length;
                break;
            }
            current = current->next;
        }
    }

    return LL_ERROR_RETURN_SUCCESS;
}
LL_ERROR_CODES ll_free_list(LinkListPtr list) {

    if (list == NULL) {
        (void)fprintf(stderr, "[ERROR] the list is null in %s at %d ", __FILE__, __LINE__);
    }

    for (size_t i = 0; i <= list->length; i++) {
        NodePtr old_head = list->head;
        if (old_head->next == NULL) {
            free(old_head->data);
            free(old_head);
            old_head = NULL;
            break;
        }
        list->head = old_head->next;
        free(old_head->data);
        free(old_head);
        old_head = NULL;
    }

    free(list);

    return LL_ERROR_RETURN_SUCCESS;
}

LL_ERROR_CODES ll_print_list(LinkListPtr list) {

    if (list == NULL) {
        (void)fprintf(stderr, "[ERROR] the list is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return LL_ERROR_RETURN_ERROR;
    }

    NodePtr current = list->head;
    for (size_t i = 0; i < list->length; i++) {
        if (current->data != NULL) {
            (void)fprintf(stdout, "this is the value of the node at inx# %zu is %d", i,
                          *(int*)(current->data));
            current = current->next;
        }
    }

    return LL_ERROR_RETURN_SUCCESS;
}
