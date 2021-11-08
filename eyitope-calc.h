#ifndef EYITOPE_CALC_H
#define EYITOPE_CALC_H

#include "eyitope-ring-buffer.h"
#include "queue.h"

struct sensorval {
    struct queue_t *next;
    float reading;
};

struct tracker {
    int index;
    float *data;
};

struct tracker* osw_average(queue_t tomato_stack);

#endif