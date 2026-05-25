/**
 * @file main.c
 * @author Amar Campbell
 * @brief Implementation of dynamic array in c
 * @copyright Copyright (c) 2026 Amar
 */

#include "llist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    LinkListPtr list   = calloc(1, sizeof(LinkList));
    list->element_size = (sizeof(int));
    list->length       = 0;
    list->head         = NULL;
    list->tail         = NULL;

    for (size_t i = 0; i < 10; i++) {
        ll_append(list, &i);
    }

    ll_print_list(list);
    ll_free_list(list);

    return 0;
}
