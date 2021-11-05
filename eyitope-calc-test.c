#include "contiki.h"
#include "unit-test.h"
#include "eyitope-ring-buffer.h"

UNIT_TEST_REGISTER(test_init, "init test");
// UNIT_TEST_REGISTER(test_pop, "test pop");
// UNIT_TEST_REGISTER(test_push, "test push");
// UNIT_TEST_REGISTER(test_head, "test head");
// UNIT_TEST_REGISTER(test_tail, "test tail");
// UNIT_TEST_REGISTER(test_peek, "test peek");


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

// UNIT_TEST(test_pop) 
// {
//     UNIT_TEST_BEGIN();
//     UNIT_TEST_END();
// }

// UNIT_TEST(test_push) 
// {
//     ringbuffer rb;
//     UNIT_TEST_BEGIN();
//     UNIT_TEST_END();
// }

// UNIT_TEST(test_head) 
// {
//     UNIT_TEST_BEGIN();
//     UNIT_TEST_END();
// }

// UNIT_TEST(test_tail) 
// {
//     UNIT_TEST_BEGIN();
//     UNIT_TEST_END();
// }

// UNIT_TEST(test_peek) 
// {
//     UNIT_TEST_BEGIN();
//     UNIT_TEST_END();
// }


PROCESS(test_all, "Unit testing");
AUTOSTART_PROCESSES(&test_all);

PROCESS_THREAD(test_all, ev, data) 
{
    PROCESS_BEGIN();

    UNIT_TEST_RUN(test_init);

    PROCESS_END();
}
