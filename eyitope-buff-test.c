#include "eyitope-ring-buffer.h"
#include "unit-test.h"
#include "contiki.h"
#include <stdio.h>
#include <stddef.h>


UNIT_TEST_REGISTER(test_init, "test init");
UNIT_TEST_REGISTER(test_push, "test push");
UNIT_TEST_REGISTER(test_peek, "test peek");
UNIT_TEST_REGISTER(test_head, "test head");
UNIT_TEST_REGISTER(test_tail, "test tail");
UNIT_TEST_REGISTER(test_pop, "test pop");


UNIT_TEST(test_init) 
{
    UNIT_TEST_BEGIN();

    ringbuffer rb;
    rb_init(&rb);
    
    UNIT_TEST_ASSERT(rb.front == -1);
    UNIT_TEST_ASSERT(rb.rear == -1);
    UNIT_TEST_ASSERT(rb.front == rb.rear);

    UNIT_TEST_END();
}

UNIT_TEST(test_pop) 
{
    ringbuffer rb;
    rb_init(&rb);
    float a = 0.0f;
    float *rt;
    for (a = 0.0; (int)a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }

    UNIT_TEST_BEGIN();
    for (a = (float)rb.ring_buffer_size; (int)a<rb.ring_buffer_size; a--) {
        rt = (float*)rb_pop(&rb);
        UNIT_TEST_ASSERT(rb_pop(&rb) == NULL);
        UNIT_TEST_ASSERT(rt != NULL);
    }
    UNIT_TEST_END();
}

UNIT_TEST(test_push)
{
    ringbuffer rb;
    rb_init(&rb);
    for (float a = 0.0f; (int)a < rb.ring_buffer_size - 1; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_BEGIN();
    UNIT_TEST_ASSERT(rb_push(&rb, 8.0) == 0);
    UNIT_TEST_ASSERT(rb_push(&rb, 8.0) == -1);
    UNIT_TEST_ASSERT(rb_push(&rb, 2.1) < 0);
    UNIT_TEST_ASSERT(rb_push(&rb, 1.97) == -1);
    UNIT_TEST_ASSERT(rb_push(&rb, 8.0) > -2.0);

    UNIT_TEST_END();
}


UNIT_TEST(test_head) 
{
    UNIT_TEST_BEGIN();

    ringbuffer rb;
    rb_init(&rb);

    for (float a = 6.0; (int)a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_ASSERT(*(float*)rb_head(&rb) == 6.0);
    rb_pop(&rb);
    UNIT_TEST_ASSERT(*(float*)rb_head(&rb) != 6.0);
    UNIT_TEST_ASSERT(*(float*)rb_head(&rb) == 7.0);
    rb_pop(&rb);
    UNIT_TEST_ASSERT(*(float*)rb_head(&rb) == 8.0);
    UNIT_TEST_END();
}

UNIT_TEST(test_tail) 
{
    UNIT_TEST_BEGIN();

    ringbuffer rb;
    rb_init(&rb);

    for (float a = 0.0; (int)a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_ASSERT(*(float*)rb_tail(&rb) == rb.ring_buffer_size - 1);
    
    // Tail shouldn't change between calls to rb_pop();
    rb_pop(&rb);
    UNIT_TEST_ASSERT(*(float*)rb_tail(&rb) == rb.ring_buffer_size - 1);
    
    UNIT_TEST_END();
}

UNIT_TEST(test_peek) 
{
    ringbuffer rb;
    rb_init(&rb);

    UNIT_TEST_BEGIN();
    for (float a = 0.0; (int)a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_ASSERT(*(float*)rb_peek(&rb) == rb.ring_buffer_size - 1);
    UNIT_TEST_END();
}


PROCESS(test_all, "Unit testing");
AUTOSTART_PROCESSES(&test_all);

PROCESS_THREAD(test_all, ev, data) 
{    
    PROCESS_BEGIN();

    UNIT_TEST_RUN(test_init);
    UNIT_TEST_RUN(test_pop);
    UNIT_TEST_RUN(test_push);
    UNIT_TEST_RUN(test_head);
    UNIT_TEST_RUN(test_tail);
    UNIT_TEST_RUN(test_peek);

    PROCESS_END();
}
