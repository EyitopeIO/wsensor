#include "contiki.h"
#include "unit-test.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>
// #include "eyitope-ring-buffer.h"
#include "eyitope-calc.h"

UNIT_TEST_REGISTER(test_osw, "Calculation test");


// UNIT_TEST(test_osw) 
// {

//     ringbuffer rb;
//     rb_init(&rb);

//     int i = 0;
//     float a = 0.0f;
//     float *zr;
//     float cfm[] = {5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 9.0};
    
//     /*
//      *Fill ring buffer with test data
//     */
//     for (a = 5.0f; (rb_push(&rb, a) != -1) && (a < 12.0f); a++);

//     for (i = 0; i != 7; i++) {
//         zr = (float*)rb_pop(&rb);
//         if (zr != NULL) printf("popped: %f\n", (float)(*zr));
//         else printf("NULL at zr[%d]\n",i);
//     }
//     printf("\n");

//     /*
//      * The actual calculation
//     */    
//     zr = osw_average(&rb);

//     for (i = 0; i < 8; i++) {
//         printf("%1.2f ", zr[i]);
//     }
//     printf("\n");

//     UNIT_TEST_BEGIN();
//     for (i = 0; i < 8; i++) {
//         UNIT_TEST_ASSERT(zr[i] == cfm[i]);
//     }
//     UNIT_TEST_END();


UNIT_TEST(test_osw) 
{

    int i = 0;
    float a = 4.0f;
    struct sensorval *p = NULL;
    struct tracker *t; 
    float cfm[] = {5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 9.0};

    QUEUE(worm);
    queue_init(worm);

    struct sensorval sv1;
    struct sensorval sv2; 
    struct sensorval sv3; 
    struct sensorval sv4; 
    struct sensorval sv5; 
    struct sensorval sv6; 
    struct sensorval sv7;
    struct sensorval sv8;  

    sv1.reading = a + 1.0;
    sv2.reading = a + 2.0;
    sv3.reading = a + 3.0;
    sv4.reading = a + 4.0;
    sv5.reading = a + 5.0;
    sv6.reading = a + 6.0;
    sv7.reading = a + 7.0;
    sv8.reading = a + 8.0;
    sv9.reading = a + 8.0;

    queue_enqueue(worm, &sv1);
    queue_enqueue(worm, &sv2);
    queue_enqueue(worm, &sv3);
    queue_enqueue(worm, &sv4);
    queue_enqueue(worm, &sv5);
    queue_enqueue(worm, &sv6);
    queue_enqueue(worm, &sv7);
    queue_enqueue(worm, &sv8);
    
    while ((p = queue_dequeue(worm)) != NULL) printf("dq: %f\n", (float)(p->reading));

    t = osw_average(worm);

    UNIT_TEST_BEGIN();
    UNIT_TEST_ASSERT(t != NULL); 
    for (i = t->index; i != 0; i--) {
        UNIT_TEST_ASSERT(cfm[i] == t->data[i]); 
    }    
    UNIT_TEST_END();
}



PROCESS(test_all, "Calculation unit test");
AUTOSTART_PROCESSES(&test_all);
PROCESS_THREAD(test_all, ev, data) 
{
    PROCESS_BEGIN();

    UNIT_TEST_RUN(test_osw);

    PROCESS_END();
}
