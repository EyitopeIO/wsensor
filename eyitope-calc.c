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

    if (list_length(*tomato_stack) < WINDOW_SIZE) {     // At startup, items < WINDOW_SIZE
        uint8_t l = list_length(*tomato_stack);
        p = list_head(*tomato_stack);
        while (l--) {
            total += p->reading;
            average = total / n++;
            p = list_item_next(p);
        }
    }
    else {          // During normal operation, tomato_stack would always be length WINDOW_SIZE
        p = list_head(*tomato_stack);
        float head = p->reading;
        p = list_tail(*tomato_stack);
        float tail = p->reading;
        average = ((total - head) + tail) / WINDOW_SIZE;
        list_pop(*tomato_stack);
    }

    return &average;
}


    // for(i = 0; i < 7; i++) printf("x[%d] = %f\n", i, x[i]);
        // printf("rd: %f, to: %f, av: %f, i: %d\n", p->reading, total, total/i, i);
