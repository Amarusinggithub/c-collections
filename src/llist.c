/**
 * @file llist.c
 * @author Amar Campbell
 * @brief This is the dynamic array declaration header file
 * @copyright Copyright (c) 2026 Amar
 */

#include "llist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ll_errors_to_str(LL_ERROR_CODES code) {
    switch (code) {
        case LL_ERROR_RETURN_SUCCESS:
            return "Return Success";
        case LL_ERROR_RETURN_ERROR:
            return "Return Error";
        case LL_ERROR_EMPTY_LIST:
            return "Empty List";
        case LL_ERROR_NOT_FOUND:
            return "Not Found";
        case LL_ERROR_OUT_OF_BOUNDS:
            return "Out of Bound";
        default:
            return "Unknown Code";
    }
}

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
    new_node->data = NULL;
    new_node->next = NULL;

    // copy the value to a buffer before and then set new node
    //  data to the buffer to obey the ownership of value
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
        list->head = new_node;
        list->tail = NULL;
        ++list->length;
    } else if (list->head && list->head->next == NULL && list->length > 0) {
        list->head->next = new_node;
        list->tail       = new_node;
        ++list->length;
    } else {
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

LL_ERROR_CODES ll_prepend(LinkListPtr list, const void* value) {
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

    NodePtr new_head = calloc(1, sizeof(Node));
    if (new_head == NULL) {
        (void)fprintf(stderr, "[ERROR] the newNode is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return LL_ERROR_RETURN_ERROR;
    }

    new_head->data = NULL;
    new_head->next = NULL;

    // copy the value to a buffer before and then set new node
    //  data to the buffer to obey the ownership of value.
    void* new_data = calloc(1, list->element_size);
    if (new_data == NULL) {
        (void)fprintf(stderr, "[ERROR] the new_head is null in file %s at line# %d", __FILE__,
                      __LINE__);
        free(new_head); // free new node in the case that new data is null before return
        return LL_ERROR_RETURN_ERROR;
    }
    memmove(new_data, value, list->element_size);
    new_head->data = new_data;

    if (list->length == 0 && list->head == NULL) {
        list->head = new_head;
        ++list->length;
    } else {
        NodePtr old_head = list->head;
        list->head       = new_head;
        new_head->next   = old_head;
        ++list->length;
    }

    return LL_ERROR_RETURN_SUCCESS;
}

LL_ERROR_CODES ll_free_list(LinkListPtr list) {

    if (list == NULL) {
        (void)fprintf(stderr, "[ERROR] the list is null in %s at %d ", __FILE__, __LINE__);
        return LL_ERROR_RETURN_ERROR;
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
        }
        current = current->next;
    }

    return LL_ERROR_RETURN_SUCCESS;
}

LL_ERROR_CODES ll_remove(LinkListPtr list, const void* value) {
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
    NodePtr current  = list->head;
    NodePtr previous = NULL;

    if (list->length == 1 && memcmp(current->data, value, list->element_size) == 0) {
        list->head = NULL;
        list->tail = NULL;
        --list->length;
        free(current->data);
        free(current);
    }

    while (true) {

        if (list->length == 0 && list->head == NULL) {
            return LL_ERROR_EMPTY_LIST;
        }

        // previous == NULL detects that we are still at the head
        if (list->length > 1 && previous == NULL &&
            memcmp(current->data, value, list->element_size) == 0) {
            list->head = current->next;
            --list->length;
            free(current->data);
            free(current);
            break;
        }

        if (current->next == NULL && memcmp(current->data, value, list->element_size) == 0) {
            --list->length;
            list->tail     = previous;
            previous->next = NULL;
            free(current->data);
            free(current);
            break;
        }

        // if the data was not found
        if (current->next == NULL && memcmp(current->data, value, list->element_size) != 0) {
            return LL_ERROR_NOT_FOUND;
        }

        if (memcmp(current->data, value, list->element_size) != 0) {
            previous = current;
            current  = current->next;
            continue;
        }

        // Unlinks the middle node from the chain
        previous->next = current->next;
        --list->length;
        free(current->data);
        free(current);
        break;
    }

    return LL_ERROR_RETURN_SUCCESS;
}

NodePtr ll_get(LinkListPtr list, size_t index) {
    if (list == NULL) {
        (void)fprintf(stderr, "[ERROR] the list is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return NULL;
    }

    if (index >= list->length) {
        return NULL;
    }

    NodePtr current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

int64_t ll_length(LinkListPtr list) {
    if (list == NULL) {
        (void)fprintf(stderr, "[ERROR] the list is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return -1;
    }

    return (int64_t)list->length;
}

LL_ERROR_CODES ll_contains(LinkListPtr list, const void* value) {
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

    NodePtr current = list->head;
    if (list->length == 0 || current == NULL) {
        return LL_ERROR_EMPTY_LIST;
    }

    while (true) {
        if (memcmp(current->data, value, list->element_size) != 0) {
            if (current->next != NULL) {
                current = current->next;
                continue;
            }
            break;
        }
        return LL_ERROR_RETURN_SUCCESS;
    }
    return LL_ERROR_NOT_FOUND;
}

LL_ERROR_CODES ll_insert_at(LinkListPtr list, size_t idx, const void* value) {
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

    if (idx > list->length) {
        return LL_ERROR_OUT_OF_BOUNDS;
    }

    NodePtr new_node = calloc(1, sizeof(Node));
    if (new_node == NULL) {
        (void)fprintf(stderr, "[ERROR] the new_node is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return LL_ERROR_RETURN_ERROR;
    }

    new_node->data = NULL;
    new_node->next = NULL;

    // copy the value to a buffer before and then set new node
    //  data to the buffer to obey the ownership of value.
    void* new_data = calloc(1, list->element_size);
    if (new_data == NULL) {
        (void)fprintf(stderr, "[ERROR] the new_node is null in file %s at line# %d", __FILE__,
                      __LINE__);
        free(new_node); // free new node in the case that new data is null before return
        return LL_ERROR_RETURN_ERROR;
    }
    memmove(new_data, value, list->element_size);
    new_node->data = new_data;

    NodePtr current  = list->head;
    NodePtr previous = NULL;

    if (list->length == 0 && current == NULL) {
        list->head = new_node;
        ++list->length;
        return LL_ERROR_RETURN_SUCCESS;
    }

    if (idx == 0) {
        list->head     = new_node;
        new_node->next = current;
        ++list->length;
        return LL_ERROR_RETURN_SUCCESS;
    }

    if (idx == list->length) {
        if (list->tail == NULL) {
            list->tail    = new_node;
            current->next = list->tail;
            ++list->length;
            return LL_ERROR_RETURN_SUCCESS;
        }
        list->tail->next = new_node;
        list->tail       = new_node;
        ++list->length;
        return LL_ERROR_RETURN_SUCCESS;
    }

    for (size_t i = 0; i <= idx; i++) {
        if (i != idx) {
            previous = current;
            current  = current->next;
            continue;
        }
        previous->next = new_node;
        new_node->next = current;
        ++list->length;
        break;
    }

    return LL_ERROR_RETURN_SUCCESS;
}

LL_ERROR_CODES ll_reverse(LinkListPtr list) {
    if (list == NULL) {
        (void)fprintf(stderr, "[ERROR] the list is null in file %s at line# %d", __FILE__,
                      __LINE__);
        return LL_ERROR_RETURN_ERROR;
    }

    if (list->head == NULL && list->length == 0) {
        return LL_ERROR_EMPTY_LIST;
    }

    if (list->head != NULL && list->length == 1) {
        return LL_ERROR_RETURN_SUCCESS;
    }

    NodePtr previous = NULL;
    NodePtr current  = list->head;
    NodePtr next     = list->head->next;

    while (true) {
        if (next == NULL) {
            current->next    = previous;
            list->head->next = NULL;
            list->tail       = list->head;
            list->head       = current;
            break;
        }
        previous      = current;
        current       = next;
        next          = next->next;
        current->next = previous;
    }

    return LL_ERROR_RETURN_SUCCESS;
}
