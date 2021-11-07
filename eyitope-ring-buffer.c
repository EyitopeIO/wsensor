
#include "eyitope-ring-buffer.h"
#include <stdlib.h>


void rb_init(ringbuffer *rb) {
    rb->front = rb->rear = -1;
    rb->overflow = 0;
    rb->ring_buffer_size = RING_BUFFER_SIZE;
}

int rb_push(ringbuffer *rb, float value) {

	if ((rb->front == 0 && rb->rear == rb->ring_buffer_size-1) ||
			(rb->rear == (rb->front-1)%(rb->ring_buffer_size-1))) {
        rb->overflow = 1;
		return -1;
	}
	else if (rb->front == -1) /* Insert First Element */ {
		rb->front = rb->rear = 0;
		rb->buffer[rb->rear] = value;
	}
	else if (rb->rear == rb->ring_buffer_size-1 && rb->front != 0) {
		rb->rear = 0;
		rb->buffer[rb->rear] = value;
	}
	else {
		(rb->rear)++;
		rb->buffer[rb->rear] = value;
	}
    return 0;
}

void * rb_pop(ringbuffer *rb) {
    static void *rt;
    rt = NULL;
    if (rb->front == -1) {
        return rt;
    }
    rt = &(rb->buffer[rb->front]);
    rb->buffer[rb->front] = -1;
    if (rb->front == rb->rear) {
        rb->front = -1;
        rb->rear = -1;
    }
    else if (rb->front == rb->ring_buffer_size - 1) {
        rb->front = 0;
    }
    else {
        (rb->front)++;
    }
    return rt;
}

void * rb_head(ringbuffer *rb) {
    static void *ret = NULL;
    ret = &rb->buffer[rb->front];
    return ret;
}

void * rb_tail(ringbuffer *rb) {
    static void *ret = NULL;
    ret = &rb->buffer[rb->rear];
    return ret;
}

void * rb_peek(ringbuffer *rb) {
    static void *ret = NULL;
    if (rb->front == rb->rear) {
        return NULL;
    }
    else {
        ret = &(rb->buffer[rb->rear]);
        return ret;
    }
}

