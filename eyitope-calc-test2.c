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
    float *avg = NULL;
    float cfm[] = {5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 9.0};
    float tst[] = {5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};

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
    // struct sensorval sv9;  
    // struct sensorval sv10;

    sv1.reading = tst[0];
    sv2.reading = tst[1];
    sv3.reading = tst[2];
    sv4.reading = tst[3];
    sv5.reading = tst[4];
    sv6.reading = tst[5];
    sv7.reading = tst[6];
    sv8.reading = tst[7];
    // sv9.reading = a + 9.0;tores values read from sensor.
    // sv10.reading = a + 10.0;

    queue_enqueue(worm, &sv1);
    queue_enqueue(worm, &sv2);
    queue_enqueue(worm, &sv3);
    queue_enqueue(worm, &sv4);
    queue_enqueue(worm, &sv5);
    queue_enqueue(worm, &sv6);
    queue_enqueue(worm, &sv7);
    queue_enqueue(worm, &sv8);
    // queue_enqueue(worm, &sv9);
    // queue_enqueue(worm, &sv10);
    
    // while ((p = queue_dequeue(worm)) != NULL) printf("dq: %f\n", (float)(p->reading));


    UNIT_TEST_BEGIN();

    avg = osw_average(&worm); // Find average of first 7
    printf("avg: %f\n", *avg);
    UNIT_TEST_ASSERT(avg != NULL); 
    UNIT_TEST_ASSERT(*avg == cfm[6]);    // cfm[6] = 8.0 
      
    avg = osw_average(&worm);     
    UNIT_TEST_ASSERT(avg != NULL);
    printf("avg: %f\n", *avg);
    UNIT_TEST_ASSERT(*avg == cfm[7]);        // cfm[7] = 9.0

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