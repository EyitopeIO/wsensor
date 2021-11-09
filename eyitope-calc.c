#include "eyitope-calc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float* osw_average(list_t *tomato_stack)  
{
    static float average = 0.0f;
    
    struct sensorval_l *p = NULL;
    uint8_t n = 0;
    float total = 0.0f;

    p = list_head(*tomato_stack);
    // l = list_length(*tomato_stack);

    while(n < WINDOW_SIZE) {
        total = total + p->reading;
        average = total / (n + 1);
        p = list_item_next(p);
        n++;
    }
    list_pop(*tomato_stack);
    total = 0.0;

    return &average;
}


    // for(i = 0; i < 7; i++) printf("x[%d] = %f\n", i, x[i]);
        // printf("rd: %f, to: %f, av: %f, i: %d\n", p->reading, total, total/i, i);
