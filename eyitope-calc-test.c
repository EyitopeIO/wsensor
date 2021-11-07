#include <contiki.h>
#include <services/unit-test/unit-test.h>
#include "eyitope-ring-buffer.h"

UNIT_TEST_REGISTER(test_init, "init test");


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



PROCESS(test_all, "Unit testing");
PROCESS_THREAD(test_all, ev, data) 
{
    PROCESS_BEGIN();

    UNIT_TEST_RUN(test_init);

    PROCESS_END();
}
