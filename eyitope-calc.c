#include "eyitope-calc.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct tracker* osw_average(queue_t *tomato_stack)
{
    static float x[7];
    static struct tracker t;
    struct sensorval *p; 
    static float total = 0.0f;

    int i = 0;

    while(i--) x[i] = 0;

    for(i = 1; ((p = queue_dequeue(*tomato_stack)) != NULL) && i < 8; i++ ) {
        // b = abs(i - 6);
        total += p->reading ;
        x[i - 1] = total / i;
        printf("rd: %f, to: %f, av: %f, i: %d\n", p->reading, total, total/i, i);
    }
    total -= x[0];

    // for(i = 0; i < 7; i++) printf("x[%d] = %f\n", i, x[i]);

    t.index = i - 1;
    t.data = x;
    return &t;
}