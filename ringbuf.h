#ifndef _RINGBUF_H_
#define _RINGBUF_H_

#include <stdint.h>

#define RINGBUF_BUF_SIZE_DEFAULT (256)

// allow RINGBUF_BUF_SIZE to be defined externally
#ifndef RINGBUF_BUF_SIZE
#define RINGBUF_BUF_SIZE RINGBUF_BUF_SIZE_DEFAULT
#endif

// safety check for the buffer size, if it's power of 2
#if (((RINGBUF_BUF_SIZE) & (RINGBUF_BUF_SIZE-1)) != 0)
#error User Defined ring buffer size must be a power of 2.
#endif

#define RINGBUF_MASK (RINGBUF_BUF_SIZE - 1)


typedef uint32_t ringbuf_item;

typedef struct {
    size_t read;
    size_t write;
    ringbuf_item buffer[RINGBUF_BUF_SIZE];
} ringbuf_data;


extern void ringbuf_reset(ringbuf_data *rbd);
extern int ringbuf_push(ringbuf_data *rbd, ringbuf_item item);
extern int ringbuf_pop(ringbuf_data *rbd, ringbuf_item *item);
extern int ringbuf_peek(const ringbuf_data *rbd, ringbuf_item *item);
extern size_t ringbuf_current_size(const ringbuf_data *rbd);
extern size_t ringbuf_maximum_size(const ringbuf_data *rbd);
extern int ringbuf_empty(const ringbuf_data *rbd);
extern int ringbuf_full(const ringbuf_data *rbd);

#endif /* _RINGBUF_H_ */
