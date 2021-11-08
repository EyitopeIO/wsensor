#ifndef EYITOPE_CALC_H
#define EYITOPE_CALC_H

#include "eyitope-ring-buffer.h"
#include "queue.h"

#define QUEUE(sensorval)

struct sensorval {
    struct queue *next;
    float reading;
};

float* osw_average(ringbuffer *rb);

#endif