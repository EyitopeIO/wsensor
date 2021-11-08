#include "eyitope-calc.h"
#include <stdlib.h>
#include <math.h>

struct tracker* osw_average(queue_t tomato_stack)
{
    static float x[6];
    static struct tracker t;

    struct sensorval *p; 
    float total = 0.0f;
    int i = 7;

    while(i--) x[i] = 0;

    for(i = 7; ((p = queue_dequeue(tomato_stack)) != NULL) && i--; ) {
        total += p->reading;
        x[abs(i-7)] = total / abs(i-7);
    }

    t.index = i;
    t.data = x;
    return &t;
}