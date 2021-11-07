#include "eyitope-calc.h"
#include <stdlib.h>

float * osw_average(ringbuffer *z)
{
    static float x[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float *popped = NULL; 
    float total = 0.0;
    int i = 0;

    while ( ((popped = (float*)rb_pop(z)) != NULL) && (i < 6) ) {
        total += *popped;
        x[i] = total / (i + 1);
        i++;
    }

    return &x[0];
}