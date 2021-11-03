#include <assert.h>
#include <stdio.h>
#include "eyitope.h"

void test_init() {
    ringbuffer rb;
    rb_init(&rb);
    assert(rb.front == -1);
    assert(rb.rear == -1);
    assert(rb.front == rb.rear);
}

void test_pop() {

}

void test_push() {
    ringbuffer rb
}

void test_head() {

}

void test_tail() {

}

void test_peek() {

}


int main() {
    test_init();
    return 0;
}