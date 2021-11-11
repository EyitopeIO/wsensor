
#include "contiki.h"
#include "eyitope-calc.h"
#include "dev/sensor/sht11/sht11.h"
#include "dev/sensor/sht11/sht11-sensor.h"
#include "sys/timer.h"

PROCESS(sense_and_send, "Main process");

AUTOSTART_PROCESSES(&sense_and_send);

PROCESS_THREAD(sense_and_send, ev, data) 
{
    LIST(quantum_tunnel_h);     // List of humidity readings
    LIST(quantum_tunnel_t);     // List of temperature readings
    static struct sensorval_l hu_r;    // Humidity readings
    static struct sensorval_l te_r;    // Temperature readings
    static struct etimer time_to_read;

    PROCESS_BEGIN();

    list_init(quantum_tunnel_h);
    list_init(quantum_tunnel_t);

    PROCESS_END();
}
