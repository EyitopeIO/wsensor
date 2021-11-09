#include "contiki.h"
#include "unit-test.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include "eyitope-calc.h"


/*
* Assume window size is 7
*/
UNIT_TEST_REGISTER(test_below_window_size, "Test when input below window size");
UNIT_TEST_REGISTER(test_equals_window_size, "Test when exactly window elements");
UNIT_TEST_REGISTER(test_above_window_size, "Test input above window elements");

int i = 0;
float *avg = NULL;
float cfm[] = {5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 9.0};
float tst[] = {5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};


UNIT_TEST(test_below_window_size)
{
    LIST(worm);
    list_init(worm);

    struct sensorval_l sv1;
    struct sensorval_l sv2; 
    struct sensorval_l sv3; 

    sv1.reading = tst[0];
    sv2.reading = tst[1];
    sv3.reading = tst[2];

    list_add(worm, &sv1);
    list_add(worm, &sv2);
    list_add(worm, &sv3);

    UNIT_TEST_BEGIN();

    avg = osw_average(&worm); // Find average of first 3
    printf("avg: %f\n", *avg);
    UNIT_TEST_ASSERT(avg != NULL); 
    UNIT_TEST_ASSERT(*avg == cfm[2]);
    
    UNIT_TEST_END();
}


UNIT_TEST(test_equals_window_size) 
{
    LIST(worm);
    list_init(worm);

    struct sensorval_l sv1;
    struct sensorval_l sv2; 
    struct sensorval_l sv3;    
    struct sensorval_l sv4; 
    struct sensorval_l sv5; 
    struct sensorval_l sv6; 
    struct sensorval_l sv7;  
    
    sv1.reading = tst[0];
    sv2.reading = tst[1];
    sv3.reading = tst[2];
    sv4.reading = tst[3];
    sv5.reading = tst[4];
    sv6.reading = tst[5];
    sv7.reading = tst[6];

    list_add(worm, &sv1);
    list_add(worm, &sv2);
    list_add(worm, &sv3);
    list_add(worm, &sv4);
    list_add(worm, &sv5);
    list_add(worm, &sv6);
    list_add(worm, &sv7);

    UNIT_TEST_BEGIN();

    avg = osw_average(&worm); // Find average of first 3
    printf("avg: %f\n", *avg);
    UNIT_TEST_ASSERT(avg != NULL); 
    UNIT_TEST_ASSERT(*avg == cfm[6]);
    
    UNIT_TEST_END();
}

UNIT_TEST(unit_test_test_above_window_size)
{
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
    
    sv1.reading = tst[0];
    sv2.reading = tst[1];
    sv3.reading = tst[2];
    sv4.reading = tst[3];
    sv5.reading = tst[4];
    sv6.reading = tst[5];
    sv7.reading = tst[6];
    sv8.reading = tst[7];

    list_add(worm, &sv1);
    list_add(worm, &sv2);
    list_add(worm, &sv3);
    list_add(worm, &sv4);
    list_add(worm, &sv5);
    list_add(worm, &sv6);
    list_add(worm, &sv7);
    list_add(worm, &sv8);

    UNIT_TEST_BEGIN();

    avg = osw_average(&worm); // Find average of first 7
    printf("avg: %f\n", *avg);
    UNIT_TEST_ASSERT(avg != NULL); 
    UNIT_TEST_ASSERT(*avg == cfm[6]);

    avg = osw_average(&worm); // Find average of first 8
    printf("avg: %f\n", *avg);
    UNIT_TEST_ASSERT(avg != NULL); 
    UNIT_TEST_ASSERT(*avg == cfm[7]);
    
    UNIT_TEST_END();
}


PROCESS(test_all, "Overlapping window test");
AUTOSTART_PROCESSES(&test_all);
PROCESS_THREAD(test_all, ev, data) 
{
    PROCESS_BEGIN();

    UNIT_TEST_RUN(test_below_window_size);
    UNIT_TEST_RUN(test_equals_window_size);
    UNIT_TEST_RUN(test_above_window_size);

    PROCESS_END();
}
