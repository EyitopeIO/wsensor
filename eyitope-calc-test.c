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
    rb_init(&rb);

    int i = 0;
    float a = 0.0;
    float *zr = NULL;
    float cfm[] = {5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 9.0};
    
    /*
     *Fill ring buffer with test data
    */
    for (a = 5.0f; a < 12.0f; a++) {
        rb_push(&rb, a);
    }
    for (i = 0; i < 8; i++) {
        zr = (float*)rb_pop(&rb);
        printf("%2.2f ", *zr);
    }
    printf("\n");

    /*
     * The actual calculation
    */    
    zr = osw_average(&rb);

    for (i = 0; i < 8; i++) {
        printf("%1.2f ", zr[i]);
    }
    printf("\n");


    for (i = 0; i < 8; i++) {
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
