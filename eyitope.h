#ifndef EYITOPE_H
#define EYITOPE_H

#include <stdlib.h>

#define RING_BUFFER_SIZE 54

typedef struct ringbuffer {
    int front;
    int rear;
    int ring_buffer_size;
    int buffer[RING_BUFFER_SIZE];
    int overflow;
} ringbuffer;

void rb_init(ringbuffer *rb);

void rb_push(ringbuffer *rb, int value);

int rb_pop(ringbuffer *rb);

int rb_head(ringbuffer *rb);

int rb_tail(ringbuffer *rb);

int rb_peek(ringbuffer *rb);

#endif