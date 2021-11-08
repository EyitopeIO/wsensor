#ifndef EYITOPE_CALC_H
#define EYITOPE_CALC_H

#include "eyitope-ring-buffer.h"
#include "queue.h"

struct sensorval {
    struct queue_t *next;
    float reading;
};

float* osw_average(struct sensorval *sv);

#endif