/**
 * @file stack.h
 * @author Amar Campbell
 * @brief This is the dynamic array declaration header file
 * @copyright Copyright (c) 2026 Amar
 */

#ifndef INCLUDED_STACK
#define INCLUDED_STACK
#include <stddef.h>
#include <stdint.h>

enum stack_error_codes {
    STACK_RETURN_SUCCESS,
    STACK_RETURN_ERROR,
    STACK_RETURN_EMPTY

};

struct stack {
    size_t length;
    size_t element_size;
    struct node* top;
};

struct node {
    struct node* next;
    void* value;
};

// Aliases
typedef struct stack Stack;
typedef Stack* StackPtr;
typedef struct node Node;
typedef Node* NodePtr;
typedef enum stack_error_codes STACK_ERROR_CODES;

/**
 * @brief add a node with the vale at the top of stack
 *
 * @param stack Pointer to the stack
 * @param value value to be addted to stack
 * @return STACK_ERROR_CODES error code
 */
STACK_ERROR_CODES stack_push(StackPtr stack, const void* value);

/**
 * @brief remove a node from the stack
 *
 * @param stack Pointer to the stack
 * @return NodePtr the node that got remove
 */
NodePtr stack_pop(StackPtr stack);

/**
 * @brief get the value of the top node
 *
 * @param stack Pointer to stack
 * @return void* the value of the top node
 */
void* stack_peek(StackPtr stack);

/**
 * @brief check if stack is empty
 *
 * @param stack Pointer to stack
 * @return STACK_ERROR_CODES error enum
 */
STACK_ERROR_CODES stack_is_empty(StackPtr stack);

/**
 * @brief Get stack size
 *
 * @param stack  Pointer to stacy
 * @return int64_t or -1 for error
 */
int64_t stack_size(StackPtr stack);

/**
 * @brief free the stack nodes
 *
 * @param stack Pointer to stack
 * @return STACK_ERROR_CODES enum code
 */
STACK_ERROR_CODES stack_free(StackPtr stack);

/**
 * @brief get string for stack error codes
 *
 * @param code Error code Enum
 * @return char* string to return
 */
char* stack_errors_to_str(STACK_ERROR_CODES code);

#endif