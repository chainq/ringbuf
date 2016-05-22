#include <stdio.h>
#include <stdint.h>
#include "ringbuf.h"

static ringbuf_data rb;

char *bool2str(int expr) {
    return (expr ? "success" : "failed");
}

int main() {
    int i,ok,tmp;
    ringbuf_item item,item2;

    ringbuf_reset(&rb);

    printf("ringbuf_empty: %s\n",bool2str(ringbuf_empty(&rb)));

    printf("ringbuf_push: %s\n",bool2str(ringbuf_push(&rb,53280)));
    printf("ringbuf_current_size 1: %s\n",bool2str(ringbuf_current_size(&rb) == 1));
    printf("ringbuf_maximum_size: %s\n",bool2str(ringbuf_maximum_size(&rb) == RINGBUF_BUF_SIZE-1));

    ringbuf_reset(&rb);
    ok = 1;
    for (i = 0; i < ringbuf_maximum_size(&rb); i++) {
        ok &= ringbuf_push(&rb,i);
    }
    // ringbuffer should be full at this point, and there must
    // not be any push failures
    printf("push %d items: %s\n",i,bool2str(ok));
    printf("ringbuf_full: %s\n",bool2str(ringbuf_full(&rb)));

    // push to a full buffer must fail
    printf("ringbuf_push: %s\n",bool2str(!ringbuf_push(&rb,64738)));

    ok = 1;
    for (i = 0; i < (ringbuf_maximum_size(&rb) / 2); i++) {
        ok &= ringbuf_pop(&rb,&item);
        ok &= (item==i);
    }
    // ringbuffer should be half empty at this point, and there must
    // not be any push failures
    printf("pop %d items: %s\n",i,bool2str(ok));
    printf("ringbuf_current_size %d: %s\n",
           (int)ringbuf_maximum_size(&rb)-i,
           bool2str(i == (ringbuf_maximum_size(&rb)-ringbuf_current_size(&rb))));

    // peek into the ringbuffer twice, we should get the same values,
    // as the pointer won't increase.
    ok = 1; item = 0; item2 = 0;
    ok &= ringbuf_peek(&rb,&item);
    ok &= ringbuf_peek(&rb,&item2);
    printf("ringbuf_peek: %s\n",bool2str(ok && (item == item2) && (i == item)));

    // pop the rest of the values and test for emptyness
    tmp = ringbuf_current_size(&rb);
    ok = 1;
    for (i = 0; i < tmp; i++) {
        ok &= ringbuf_pop(&rb,&item);
    }
    printf("pop %d items: %s\n",i,bool2str(ok));
    printf("ringbuf_empty: %s\n",bool2str(ringbuf_empty(&rb)));

    // peek and pull from an empty buffer must fail
    printf("ringbuf_pop: %s\n",bool2str(!ringbuf_pop(&rb,&item)));
    printf("ringbuf_peek: %s\n",bool2str(!ringbuf_peek(&rb,&item)));

    return 0;
}
