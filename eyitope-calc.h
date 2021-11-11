#ifndef EYITOPE_CALC_H
#define EYITOPE_CALC_H

#include "queue.h"
#include "list.h"

#define WINDOW_SIZE 7

/*
* Represents a single unit of data from the sensor.
* Do not ever modify the first member. Ever.
* Your business is only with the second member.
*/
struct sensorval_q {
    struct queue_t *next;
    float reading;
};

struct sensorval_l {
    struct list_t *next;
    float reading;
};

/*
* Calculate the average of the last 7 elements in the queue.
* @param tomato_stack: A pointer to the queue.
* @return: A pointer to the calculated average. 
*/
float osw_average(queue_t *tomato_stack);

#endif