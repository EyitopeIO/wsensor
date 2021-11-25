#include "eyitope-calc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
 
float osw_average(list_t *tomato_stack)  
{
    float average = 0.0f;
    struct sensorval_l *p = NULL;
    uint8_t n = 0;
    float total = 0.0f;

    p = list_head(*tomato_stack);

    while((n < WINDOW_SIZE) && (p != NULL)) {
        total = total + p->reading;
        average = total / (n + 1);
        p = list_item_next(p);
        n++;
    }
    list_pop(*tomato_stack);
    total = 0.0;

    return average;
}
