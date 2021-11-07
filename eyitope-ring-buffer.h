#ifndef EYITOPE_RING_BUFFER
#define EYITOPE_RING_BUFFER

#define RING_BUFFER_SIZE 32

typedef struct ringbuffer {
    int front;
    int rear;
    int ring_buffer_size;
    float buffer[RING_BUFFER_SIZE];
    int overflow;
} ringbuffer;

void rb_init(ringbuffer *rb);

int rb_push(ringbuffer *rb, int value);

void* rb_pop(ringbuffer *rb);

void* rb_head(ringbuffer *rb);

void* rb_tail(ringbuffer *rb);

void* rb_peek(ringbuffer *rb);

#endif