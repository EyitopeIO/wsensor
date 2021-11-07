#include "contiki.h"
#include "unit-test.h"
#include <stdlib.h>
#include <stdio.h>
#include "eyitope-ring-buffer.h"
#include "eyitope-calc.h"

UNIT_TEST_REGISTER(test_osw, "Calculation test");


UNIT_TEST(test_osw) 
{
    UNIT_TEST_BEGIN();

    ringbuffer rb;
    float *zr = NULL;
    rb_init(&rb);
    float cfm[] = {5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 9.0};
    
    // Fill ring buffer with test data
    for (float a = 5.0f; a < 8.0f; a++) {
        rb_push(&rb, a);
    }
    printf("Ring buffer -> ");
    for (int i = 0; i < 8; i++) {
        printf("%f ", *(float*)rb_pop(&rb));
    }
    printf("\n");

    zr = osw_average(&rb);

    for (int i = 0; i < 8; i++) {
        printf("%1.2f ", zr[i]);
    }
    printf("\n");


    for (int i = 0; i < 8; i++) {
        UNIT_TEST_ASSERT(zr[i] == cfm[i]);
    }

    UNIT_TEST_END();
}

// UNIT_TEST(test_pop) 
// {
//     UNIT_TEST_BEGIN();
//     UNIT_TEST_END();
// }



PROCESS(test_all, "Calculation unit test");
AUTOSTART_PROCESSES(&test_all);
PROCESS_THREAD(test_all, ev, data) 
{
    PROCESS_BEGIN();

    UNIT_TEST_RUN(test_osw);

    PROCESS_END();
}
