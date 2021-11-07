#include "eyitope-ring-buffer.h"
#include "unit-test.h"
#include "contiki.h"

UNIT_TEST_REGISTER(test_init, "init test");
UNIT_TEST_REGISTER(test_pop, "test pop");
UNIT_TEST_REGISTER(test_push, "test push");
UNIT_TEST_REGISTER(test_head, "test head");
UNIT_TEST_REGISTER(test_tail, "test tail");
UNIT_TEST_REGISTER(test_peek, "test peek");


UNIT_TEST(test_init) 
{
    ringbuffer rb;
    rb_init(&rb);

    UNIT_TEST_BEGIN();
    
    UNIT_TEST_ASSERT(rb.front == -1);
    UNIT_TEST_ASSERT(rb.rear == -1);
    UNIT_TEST_ASSERT(rb.front == rb.rear);

    UNIT_TEST_END();
}

UNIT_TEST(test_pop) 
{
    ringbuffer rb;
    rb_init(&rb);
    int a = 0;
    for (a = 0; a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }

    UNIT_TEST_BEGIN();
    for (a = rb.ring_buffer_size; a<rb.ring_buffer_size; a--) {
        UNIT_TEST_ASSERT(rb_pop(&rb) == a);
    }

    UNIT_TEST_END();
}

UNIT_TEST(test_push) 
{
    ringbuffer rb;
    UNIT_TEST_BEGIN();

    for (int a = 0; a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_ASSERT(rb_push(&rb, 5) == -1);
    UNIT_TEST_END();
}

UNIT_TEST(test_head) 
{
    ringbuffer rb;
    rb_init(&rb);

    UNIT_TEST_BEGIN();
    for (int a = 0; a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_ASSERT(rb_head(&rb) == 0);
    UNIT_TEST_END();
}

UNIT_TEST(test_tail) 
{
    ringbuffer rb;
    rb_init(&rb);

    UNIT_TEST_BEGIN();
    for (int a = 0; a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_ASSERT(rb_tail(&rb) == rb.ring_buffer_size - 1);
    UNIT_TEST_END();
}

UNIT_TEST(test_peek) 
{
    ringbuffer rb;
    rb_init(&rb);

    UNIT_TEST_BEGIN();
    for (int a = 0; a<rb.ring_buffer_size; a++) {
        rb_push(&rb, a);
    }
    UNIT_TEST_ASSERT(rb_peek(&rb) == rb.ring_buffer_size -1);
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
