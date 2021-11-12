
#include "contiki.h"
#include "eyitope-calc.h"
// #include "dev/sensor/sht11/sht11.h"
// #include "dev/sensor/sht11/sht11-sensor.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "stdlib.h"
#include "stdio.h"
#include "random.h"
#include "math.h"
#include "heapmem.h"

PROCESS(sense_and_send, "Main process");

AUTOSTART_PROCESSES(&sense_and_send);

PROCESS_THREAD(sense_and_send, ev, data) 
{
    PROCESS_BEGIN();

    static struct sensorval_l *hu_r;    // Humidity readings
    static struct sensorval_l *te_r;    // Temperature readings
    static struct sensorval_l *hu_p;
    static struct sensorval_l *te_p;

    static struct etimer time_to_read;
    float avr_h;
    float avr_t;
    int i = 0;


    LIST(quantum_tunnel_h);     // List of humidity readings
    LIST(quantum_tunnel_t);     // List of temperature readings

    random_init(3);

    list_init(quantum_tunnel_h);
    list_init(quantum_tunnel_t);

    hu_p = (struct sensorval_l*)heapmem_alloc(WINDOW_SIZE * sizeof(struct sensorval_l));
    te_p = (struct sensorval_l*)heapmem_alloc(WINDOW_SIZE * sizeof(struct sensorval_l));
    if (hu_p == NULL || te_p == NULL) {
        printf("Not enough memory!\n");
        PROCESS_EXIT();
    }

    avr_h = avr_t = 0.0f;

    etimer_set(&time_to_read, CLOCK_SECOND * 8 );   // 1 mins / 7 secs

    // SENSORS_ACTIVATE(sht11_sensor);
    
    printf("Sensor activated!\n");


    while(1) {

        printf("Loop!\n");

        hu_r = hu_p;
        te_r = te_p;
        i = WINDOW_SIZE;

        while (i--) { 
            PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&time_to_read));
            // hu_r->reading = (float)sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
            // te_r->reading = (float)sht11_sensor.value(SHT11_SENSOR_TEMP);
            hu_r->reading = (float)random_rand();
            te_r->reading = (float)random_rand();
            list_add(quantum_tunnel_h, hu_r++);
            list_add(quantum_tunnel_t, te_r++);
            etimer_reset(&time_to_read);
        }

        avr_h = (0.01 * osw_average(&quantum_tunnel_h)) - 36.9;
        avr_h = (0.01 * avr_h) - 36.9;

        avr_t = osw_average(&quantum_tunnel_t);
        avr_t = -4 + (0.0405 * avr_t) - ((2.8 * pow(10, -6)) * pow(avr_t, 2));

        printf("avg humidity: %f\n", avr_h);
        printf("avg temperature: %f\n", avr_t);

        // Send over network here;

    }

    heapmem_free(hu_p);
    heapmem_free(te_p);

    PROCESS_END();
}
