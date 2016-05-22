CFLAGS = -I.
DEPS = ringbuf.h
OBJ = ringbuf.o rb_test.o

%.o: %.c $(DEPS)
	$(CC) -O3 -Wall -c -o $@ $< $(CFLAGS)

rb_test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o *.s rb_test
