
#include <stdio.h>
#include <unit-test.h>
#include <contiki.h>
#include "eyitope-ring-buffer.h"

UNIT_TEST_REGISTER(test_init, "init test");


UNIT_TEST(test_init) {
    ringbuffer rb;
    rb_init(&rb);

    UNIT_TEST_BEGIN();
    
    UNIT_TEST_ASSERT(rb.front == -1);
    UNIT_TEST_ASSERT(rb.rear == -1);
    UNIT_TEST_ASSERT(rb.front == rb.rear);

    UNIT_TEST_END();
}

void test_pop() {

}

void test_push() {
    ringbuffer rb;
}

void test_head() {

}

void test_tail() {

}

void test_peek() {

}



PROCESS(test_all, "Unit testing");
AUTOSTART_PROCESSES(&test_all);

PROCESS_THREAD(test_pricess, ev, data) {
    PROCESS_BEGIN();

    UNIT_TEST_RUN(test_init);

    PROCESS_END();
}