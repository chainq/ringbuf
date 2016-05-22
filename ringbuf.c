#include <stdint.h>
#include <stdio.h>
#include "ringbuf.h"

void ringbuf_reset(ringbuf_data *rbd) {
    rbd->read = 0;
    rbd->write = 0;
}

int ringbuf_push(ringbuf_data *rbd, ringbuf_item item) {
    if (!ringbuf_full(rbd)) {
        rbd->buffer[rbd->write] = item;
        rbd->write = (rbd->write + 1) & RINGBUF_MASK;
        return 1;
    }
    return 0;
}

int ringbuf_pop(ringbuf_data *rbd, ringbuf_item *item) {
    if (!ringbuf_empty(rbd)) {
        *item = rbd->buffer[rbd->read];
        rbd->read = (rbd->read + 1) & RINGBUF_MASK;
        return 1;
    }
    return 0;
}

int ringbuf_peek(const ringbuf_data *rbd, ringbuf_item *item) {
    if (!ringbuf_empty(rbd)) {
        *item = rbd->buffer[rbd->read];
        return 1;
    }
    return 0;
}

size_t ringbuf_current_size(const ringbuf_data *rbd) {
    return (rbd->write - rbd->read) & RINGBUF_MASK;
}

size_t ringbuf_maximum_size(const ringbuf_data *rbd) {
    /* Here we cheat. For performance reasons (easier computation of
       the index-wraparound with masking) on lightweight systems, we
       only allow 1 less entry than the maximum underlying buffer size */

    /* Also, for now all ringbuffers have the same size, because it's
       decided compile time, so the instance data is not used, but
       lets have the argument in the API for future expansion. */
    return RINGBUF_BUF_SIZE-1;
}

int ringbuf_empty(const ringbuf_data *rbd) {
    return ((rbd->write - rbd->read) & RINGBUF_MASK) == 0;
}

int ringbuf_full(const ringbuf_data *rbd) {
    return ((rbd->write - rbd->read) & RINGBUF_MASK) == RINGBUF_MASK;
}
