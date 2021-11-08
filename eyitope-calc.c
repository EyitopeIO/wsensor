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
    float phead = 0.0f;

    int i = 6;
    int b = 0;

    while(i--) x[i] = 0;

    for(i = 6; ((p = queue_dequeue(tomato_stack)) != NULL) && i--; ) {
        b = abs(i - 6);
        total += p->reading ;
        x[abs(b)] = total / b;
        printf("rd: %f, to: %f, av: %f\n", p->reading, total, total/b);
    }
    for(i = 0; i != 6; i++) printf("x[%d] = %f\n", i, x[i]);

    t.index = b;
    t.data = x;
    return &t;
}