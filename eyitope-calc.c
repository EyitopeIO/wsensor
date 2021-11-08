#include "eyitope-calc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct tracker* osw_average(queue_t tomato_stack)
{
    static float x[6];
    static struct tracker t;

    struct sensorval *p; 
    float total = 0.0f;
    int i = 6;
    int b = 0;

    while(i--) x[i] = 0;

    for(i = 7; ((p = queue_dequeue(tomato_stack)) != NULL) && i--; ) {
        b = abs(i - 7);
        total += p->reading;
        printf("reading: %f, total: %f\n", p->reading, total);
        x[abs(b)] = total / abs(b);
    }

    t.index = b;
    t.data = x;
    return &t;
}