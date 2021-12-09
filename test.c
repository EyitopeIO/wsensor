#include "sys/etimer.h"
#include "sys/clock.h"
#include "dev/leds.h"


#define NO_TIMER_FLASHES 3  // number of flashes to make
#define INITIAL_TIMER_DELAY 25  // in minutes
#define ON_TIME 100       // in milliseconds
#define OFF_TIME 100    // in milliseconds


static struct etimer main_wait_time;

PROCESS(sense_and_send, "Main process");
AUTOSTART_PROCESSES(&sense_and_send);


PROCESS_THREAD(sense_and_send, ev, data) 
{
    PROCESS_BEGIN();

    etimer_set(&main_wait_time, CLOCK_SECOND * 25 * 60);   // 60s / WINDOW_SIZE ~= 9 secs
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&main_wait_time));

    while(1) {
        for (int count = NO_TIMER_FLASHES; count > 0; count --) {
            etimer_set(&main_wait_time, CLOCK_SECOND * (ON_TIME/1000));
            leds_on(LEDS_RED);
            PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&main_wait_time));
            etimer_set(&main_wait_time, CLOCK_SECOND * (OFF_TIME/1000));
            leds_on(LEDS_RED);
            PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&main_wait_time));
        }
    }


    PROCESS_END();
}
