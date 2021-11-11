
#include "contiki.h"
#include "eyitope-calc.h"
#include "dev/sensor/sht11/sht11.h"
#include "dev/sensor/sht11/sht11-sensor.h"
#include "sys/etimer.h"
#include "stdlib.h"
#include "stdio.h"

PROCESS(sense_and_send, "Main process");

AUTOSTART_PROCESSES(&sense_and_send);

PROCESS_THREAD(sense_and_send, ev, data) 
{
    LIST(quantum_tunnel_h);     // List of humidity readings
    LIST(quantum_tunnel_t);     // List of temperature readings
    static struct sensorval_l hu_r;    // Humidity readings
    static struct sensorval_l te_r;    // Temperature readings
    static struct etimer time_to_read;
    float avr_h;
    float avr_t;
    int i = 0;

    PROCESS_BEGIN();

    list_init(quantum_tunnel_h);
    list_init(quantum_tunnel_t);

    // hu_r = (struct sensorval_l*)calloc(WINDOW_SIZE, sizeof(struct sensorval_l));
    // te_r = (struct sensorval_l*)calloc(WINDOW_SIZE, sizeof(struct sensorval_l));
    //if (hu_r == NULL || te_r == NULL) PROCESS_EXIT();

    avr_h = avr_t = 0.0f;

    etimer_set(&time_to_read, CLOCK_SECOND * 30);

    SENSORS_ACTIVATE(sht11_sensor);

    while(1) {

        for (i=0; i < WINDOW_SIZE; i++) {
            hu_r.reading = sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
            te_r.reading = sht11_sensor.value(SHT11_SENSOR_TEMP);
            list_add(quantum_tunnel_h, &hu_r);
            list_add(quantum_tunnel_t, &te_r);
        }

        avr_h = (float)osw_average(&quantum_tunnel_h);
        avr_t = (float)osw_average(&quantum_tunnel_t);

        printf("avg humidity: %f\n", avr_h);
        printf("avg temperature: %f\n", avr_t);

        // Send over network here;

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&time_to_read));
        etimer_reset(&time_to_read);
    }



    PROCESS_END();
}
