#include "eyitope-calc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float* osw_average(queue_t *tomato_stack, float *new)
{
    static int n = 1;
    static struct sensorval *p = NULL;
    static float total = 0.0f;
    static float average = 0.0f;
    static float first_e = 0.0f;        // First item on the queue
    static uint8_t under_7 = 1;     // Used to know if we now have more than 7 elements

    while(n < 8) {
        if (under_7 == 1) {
            if ((p = queue_peek(*tomato_stack)) != NULL) {
                total += p->reading ;
                average = total / n;
            }
        }
        else {
            if ((p = queue_dequeue(*tomato_stack)) != NULL) {
                average = ((total - p->reading) + *new) / WINDOW_SIZE;
            }
        }
        if (n++ > WINDOW_SIZE) {
            under_7 = 1;
            n = 1;
        }
    }

    return &average;
}


    // for(i = 0; i < 7; i++) printf("x[%d] = %f\n", i, x[i]);
        // printf("rd: %f, to: %f, av: %f, i: %d\n", p->reading, total, total/i, i);
