
#include "eyitope-ring-buffer.h"

void rb_init(ringbuffer *rb) {
    rb->front = rb->rear = -1;
    rb->overflow = 0;
    rb->ring_buffer_size = RING_BUFFER_SIZE;
}

void rb_push(ringbuffer *rb, int value) {

	if ((rb->front == 0 && rb->rear == rb->ring_buffer_size-1) ||
			(rb->rear == (rb->front-1)%(rb->ring_buffer_size-1))) {
        rb->overflow = 1;
		return;
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
}

int rb_pop(ringbuffer *rb) {
    int rt = 0;
    if (rb->front == -1) {
        return -1;
    }
    rt = rb->buffer[rb->front];
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

int rb_head(ringbuffer *rb) {
    return rb->buffer[rb->front];
}

int rb_tail(ringbuffer *rb) {
    return rb->buffer[rb->rear];
}

int rb_peek(ringbuffer *rb) {
    if (rb->front == rb->rear) {
        return -1;
    }
    else {
        return rb->buffer[rb->rear];
    }
}

