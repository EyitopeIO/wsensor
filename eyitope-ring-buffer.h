#ifndef EYITOPE_RING_BUFFER
#define EYITOPE_RING_BUFFER

#define RING_BUFFER_SIZE 64

typedef struct ringbuffer {
    int front;
    int rear;
    int ring_buffer_size;
    float buffer[RING_BUFFER_SIZE];
    int overflow;
} ringbuffer;

/*
* Initialises the ring buffer.
* @param rb: Pointer to ring buffer
*/
void rb_init(ringbuffer *rb);

/*
* Initialises the ring buffer.
* @param rb: Pointer to ring buffer
* @param value: Floating point number to add to buffer
* @return: -1 if full; 0 if success
*/
int rb_push(ringbuffer *rb, float value);

/*
* Initialises the ring buffer.
* @param rb: Pointer to ring buffer
* @return: Pointer to value popped
*/
void* rb_pop(ringbuffer *rb);

/*
* Initialises the ring buffer.
* @param rb: Pointer to ring buffer
* @param rb: Pointer to ring buffer* @return: Pointer to value popped
*/
void* rb_head(ringbuffer *rb);

/*
* Initialises the ring buffer.
* @param rb: Pointer to ring buffer
* @param rb: Pointer to ring buffer* @return: Pointer to value popped
*/
void* rb_tail(ringbuffer *rb);

/*
* Initialises the ring buffer.
* @param rb: Pointer to ring buffer
* @param rb: Pointer to ring buffer* @return: Pointer to value popped
*/
void* rb_peek(ringbuffer *rb);

#endif