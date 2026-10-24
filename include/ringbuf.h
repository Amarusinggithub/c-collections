/**
 * @file ringbuf.h
 * @author Amar Campbell
 * @brief This is the ring buffer declaration header file
 * @copyright Copyright (c) 2026 Amar
 */

#pragma once
#include "logging.h"
#include <stddef.h>
typedef enum {
    RBUFF_ERROR_RETURN_SUCCESS,
    RBUFF_ERROR_RETURN_ERROR,
    RBUFF_ERROR_OUT_OF_BOUNDS,
    RBUFF_ERROR_NOT_FOUND,
    RBUFF_ERROR_EMPTY_LIST,
    RBUFF_ERROR_FULL_LIST
} RBUFF_ERROR_CODES;

struct ringBuf {
    void* buffer;
    size_t head;
    size_t tail;
    size_t cap;
    size_t length;
    size_t elem_size;
};

typedef struct ringBuf RingBuf;
typedef RingBuf* RingBufPtr;

static inline char* rbuff_errs_to_str(const RBUFF_ERROR_CODES code) {

    switch (code) {
        case RBUFF_ERROR_RETURN_SUCCESS:
            return "Success";
        case RBUFF_ERROR_RETURN_ERROR:
            return "Error";
        case RBUFF_ERROR_OUT_OF_BOUNDS:
            return "Out of Bound";
        case RBUFF_ERROR_NOT_FOUND:
            return "Not Found";
        case RBUFF_ERROR_EMPTY_LIST:
            return "Empty";
        case RBUFF_ERROR_FULL_LIST:
            return "Full";
        default:
            return "Error code does not Exist";
    }
}

/**
 * @brief -> creates the ring buffer.
 *
 * @param cap -> the number of elements
 * @param elem_size -> the size of elements
 * @return RingBufPtr -> A pointer to the ring buffer
 */
RingBufPtr rbuf_create(size_t cap, size_t elem_size, RBUFF_ERROR_CODES* err);

/**
 * @brief-> Adds an element to the ring buffer
 *
 * @param rbuf -> The ring buffer
 * @param value -> value to store in the buffer
 * @return RBUFF_ERROR_CODES -> the error codes
 */
RBUFF_ERROR_CODES rbuf_push(RingBufPtr rbuf, void* value);

/**
 * @brief-> removes an element from the ring buffer
 *
 * @param rbuf -> the ring buffer
 * @param out -> stores the element being removed
 * @return RBUFF_ERROR_CODES
 */
RBUFF_ERROR_CODES rbuf_pop(RingBufPtr rbuf, void* out);

/**
 * @brief-> Takes a look at the element at the head of the ring buffer.
 *
 * @param rbuf -> the ring buffer
 * @param out -> stores the element to peek at
 * @return RBUFF_ERROR_CODES
 */
RBUFF_ERROR_CODES rbuf_peek(RingBufPtr rbuf, void* out);

/**
 * @brief Check if the ring buffer is full
 *
 * @param rbuf -> the ring buffer
 * @param err -> the error codes
 * @return RBUFF_ERROR_CODES
 */
static inline bool cbuf_is_full(RingBufPtr rbuf, RBUFF_ERROR_CODES* err) {
    if (rbuf == NULL) {
        LOG_ERROR("The rbuf is null.");
        *err = RBUFF_ERROR_RETURN_ERROR;
        return false;
    }

    if (rbuf->length == rbuf->cap) {
        *err = RBUFF_ERROR_RETURN_SUCCESS;
        return true;
    }

    *err = RBUFF_ERROR_RETURN_SUCCESS;
    return false;
}

/**
 * @brief Check if the ring buffer is empty
 *
 * @param rbuf -> the ring buffer
 * @param err -> the error codes
 * @return RBUFF_ERROR_CODES
 */
static inline bool cbuf_is_empty(RingBufPtr rbuf, RBUFF_ERROR_CODES* err) {
    if (rbuf == NULL) {
        LOG_ERROR("The rbuf is null.");
        *err = RBUFF_ERROR_RETURN_ERROR;
        return false;
    }

    if (rbuf->length == 0) {
        *err = RBUFF_ERROR_RETURN_SUCCESS;
        return true;
    }

    *err = RBUFF_ERROR_RETURN_SUCCESS;
    return false;
}

/**
 * @brief checks the size of the ring buffer
 *
 * @param rbuf -> The ring buffer
 * @return size_t -> The size of the ring buffer
 */
static inline size_t rbuf_size(RingBufPtr rbuf) {
    if (rbuf == NULL) {
        LOG_ERROR("The rbuf is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }

    return rbuf->length;
}

/**
 * @brief clear the ring buffer
 * 
 * @param rbuf -> The ring buffer
 * @return RBUFF_ERROR_CODES-> The error codes 
 */
RBUFF_ERROR_CODES rbuf_clear(RingBufPtr rbuf);