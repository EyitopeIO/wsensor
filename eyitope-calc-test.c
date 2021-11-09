#include "contiki.h"
#include "unit-test.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>
// #include "eyitope-ring-buffer.h"
#include "eyitope-calc.h"

UNIT_TEST_REGISTER(test_osw, "Calculation test");

UNIT_TEST(test_osw) 
{
    int i = 0;
    float *avg = NULL;
    float cfm[] = {5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 9.0};
    float tst[] = {5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};

    LIST(worm);
    list_init(worm);

    struct sensorval_l sv1;
    struct sensorval_l sv2; 
    struct sensorval_l sv3; 
    struct sensorval_l sv4; 
    struct sensorval_l sv5; 
    struct sensorval_l sv6; 
    struct sensorval_l sv7;
    struct sensorval_l sv8;  
    // struct sensorval_l sv9;  
    // struct sensorval_l sv10;

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

    list_add(worm, &sv1);
    list_add(worm, &sv2);
    list_add(worm, &sv3);
    list_add(worm, &sv4);
    list_add(worm, &sv5);
    list_add(worm, &sv6);
    list_add(worm, &sv7);
    list_add(worm, &sv8);
    // list_add(worm, &sv9);
    // list_add(worm, &sv10);
    
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
