/**
 * @file stack.c
 * @author Amar Campbell
 * @brief This is the dynamic array declaration header file
 * @copyright Copyright (c) 2026 Amar
 */

#include "stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STACK_ERROR_CODES stack_push(StackPtr stack, const void* value) {
    if (stack == NULL) {
        (void)fprintf(stderr, "The stack is null in %s line %d.", __FILE__, __LINE__);
        return STACK_RETURN_ERROR;
    }
    if (value == NULL) {
        (void)fprintf(stderr, "The value is null in %s line %d.", __FILE__, __LINE__);
        return STACK_RETURN_ERROR;
    }
    NodePtr new_top = calloc(1, sizeof(Node));
    if (new_top == NULL) {
        (void)fprintf(stderr, "The new_top is null in %s line %d.", __FILE__, __LINE__);
        return STACK_RETURN_ERROR;
    }
    new_top->next  = NULL;
    new_top->value = NULL;

    void* new_data = calloc(1, stack->element_size);
    if (new_data == NULL) {
        (void)fprintf(stderr, "The new_data is null in %s line %d.", __FILE__, __LINE__);
        free(new_top);
        return STACK_RETURN_ERROR;
    }
    memmove(new_data, value, stack->element_size);
    new_top->value = new_data;

    new_top->next = stack->top;
    stack->top    = new_top;
    ++stack->length;

    return STACK_RETURN_SUCCESS;
}

NodePtr stack_pop(StackPtr stack) {
    if (stack == NULL) {
        (void)fprintf(stderr, "The stack is null in %s line %d.", __FILE__, __LINE__);
        return NULL;
    }

    if (stack->top == NULL) {
        return NULL;
    }

    NodePtr buffer_node = stack->top;
    stack->top          = stack->top->next;
    --stack->length;

    return buffer_node;
}

void* stack_peek(StackPtr stack) {
    if (stack == NULL) {
        (void)fprintf(stderr, "The stack is null in %s line %d.", __FILE__, __LINE__);
        return NULL;
    }

    if (stack->top != NULL) {
        return stack->top->value;
    }
    return NULL;
}

STACK_ERROR_CODES stack_is_empty(StackPtr stack) {
    if (stack == NULL) {
        (void)fprintf(stderr, "The stack is null in %s line %d.", __FILE__, __LINE__);
        return STACK_RETURN_ERROR;
    }

    if (stack->length == 0) {
        return STACK_RETURN_EMPTY;
    }
    return STACK_RETURN_SUCCESS;
}

int64_t stack_size(StackPtr stack) {
    if (stack == NULL) {
        (void)fprintf(stderr, "The stack is null in %s line %d.", __FILE__, __LINE__);
        return -1;
    }

    return (int64_t)stack->length;
}

STACK_ERROR_CODES stack_free(StackPtr stack) {
    if (stack == NULL) {
        (void)fprintf(stderr, "The stack is null in %s line %d.", __FILE__, __LINE__);
        return STACK_RETURN_ERROR;
    }

    NodePtr previous = NULL;
    NodePtr current  = stack->top;
    for (size_t i = 0; i < stack->length; i++) {
        if (current == NULL) {
            break;
        }
        free(current->value);
        previous = current;
        current  = current->next;
        free(previous);
    }
    stack->top    = NULL;
    stack->length = 0;
    free(stack);
    return STACK_RETURN_SUCCESS;
}
STACK_ERROR_CODES stack_clear(StackPtr stack) {
    if (stack == NULL) {
        (void)fprintf(stderr, "The stack is null in %s line %d.", __FILE__, __LINE__);
        return STACK_RETURN_ERROR;
    }

    NodePtr previous = NULL;
    NodePtr current  = stack->top;
    for (size_t i = 0; i < stack->length; i++) {
        if (current == NULL) {
            break;
        }
        free(current->value);
        previous = current;
        current  = current->next;
        free(previous);
    }
    stack->top    = NULL;
    stack->length = 0;
    return STACK_RETURN_SUCCESS;
}

inline char* stack_errors_to_str(STACK_ERROR_CODES code) {
    switch (code) {
        case STACK_RETURN_ERROR:
            return "ERROR";
        case STACK_RETURN_SUCCESS:
            return "SUCCESS";
        case STACK_RETURN_EMPTY:
            return "EMPTY";
        default:
            return "Unkown code";
    }
}
