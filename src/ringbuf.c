#include "ringbuf.h"
#include "logging.h"
#include <stdlib.h>
#include <string.h>

RingBufPtr rbuf_create(size_t cap, const size_t elem_size, RBUFF_ERROR_CODES* err) {
    if (cap == 0) {
        cap = 50;
    }

    auto rbuf = (RingBufPtr)calloc(1, sizeof(RingBuf));
    if (rbuf == NULL) {
        LOG_ERROR("the rbuf is null");
        *err = RBUFF_ERROR_RETURN_ERROR;
        return NULL;
    }

    rbuf->buffer = calloc(cap, elem_size);
    if (rbuf->buffer == NULL) {
        LOG_ERROR("the rbuf->buffer is null");
        free(rbuf);
        *err = RBUFF_ERROR_RETURN_ERROR;
        return NULL;
    }
    rbuf->cap       = cap;
    rbuf->elem_size = elem_size;
    rbuf->length    = 0;
    rbuf->head      = 0;
    rbuf->tail      = 0;

    *err = RBUFF_ERROR_RETURN_SUCCESS;
    return rbuf;
}

RBUFF_ERROR_CODES rbuf_push(RingBufPtr rbuf, void* value) {
    if (rbuf == NULL) {
        LOG_ERROR("The rbuf is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }

    if (value == NULL) {
        LOG_ERROR("The value is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }

    if (rbuf->length == rbuf->cap) {
        return RBUFF_ERROR_FULL_LIST;
    }

    memmove_s((char*)rbuf->buffer + (rbuf->elem_size * rbuf->tail), rbuf->elem_size, value, rbuf->elem_size);

    rbuf->tail = (rbuf->tail + 1) % rbuf->cap;
    rbuf->length++;

    return RBUFF_ERROR_RETURN_SUCCESS;
}

RBUFF_ERROR_CODES rbuf_pop(RingBufPtr rbuf, void* out) {
    if (rbuf == NULL) {
        LOG_ERROR("The rbuf is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }

    if (out == NULL) {
        LOG_ERROR("The out is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }

    if (rbuf->length == 0) {
        return RBUFF_ERROR_EMPTY_LIST;
    }

    memmove_s(out, rbuf->elem_size, (char*)rbuf->buffer + (rbuf->elem_size * rbuf->head), rbuf->elem_size);

    rbuf->head = (rbuf->head + 1) % rbuf->cap;
    rbuf->length--;

    return RBUFF_ERROR_RETURN_SUCCESS;
}

RBUFF_ERROR_CODES rbuf_peek(RingBufPtr rbuf, void* out){
    if (rbuf == NULL) {
        LOG_ERROR("The rbuf is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }

    if (out == NULL) {
        LOG_ERROR("The out is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }

    if (rbuf->length == 0) {
        return RBUFF_ERROR_EMPTY_LIST;
    }

    memmove_s(out, rbuf->elem_size, (char*)rbuf->buffer + (rbuf->elem_size * rbuf->head), rbuf->elem_size);

    return RBUFF_ERROR_RETURN_SUCCESS;
}

RBUFF_ERROR_CODES rbuf_clear(RingBufPtr rbuf){
    if (rbuf == NULL) {
        LOG_ERROR("The rbuf is null.");
        return RBUFF_ERROR_RETURN_ERROR;
    }


    
    return RBUFF_ERROR_RETURN_SUCCESS;
}
