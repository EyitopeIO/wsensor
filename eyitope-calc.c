#include "eyitope-calc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float* osw_average(list_t *tomato_stack)  
{
    static struct sensorval_l *p = NULL;
    static float total = 0.0f;
    static float average = 0.0f;
    uint8_t n = 1;
    uint8_t l = 0;
    uint8_t ft = 1;     // First time

    p = list_head(*tomato_stack);
    // l = list_length(*tomato_stack);

    while(n != list_length(*tomato_stack)) {
        total = total + p->reading;
        average = total / n++;
        p = list_item_next(p);
    }
    list_pop(*tomato_stack);
    total = 0.0;

    return &average;
}


    // for(i = 0; i < 7; i++) printf("x[%d] = %f\n", i, x[i]);
        // printf("rd: %f, to: %f, av: %f, i: %d\n", p->reading, total, total/i, i);
