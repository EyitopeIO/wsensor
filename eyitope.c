
#include "contiki.h"
#include "eyitope-calc.h"
#include "dev/sensor/sht11/sht11.h"
#include "dev/sensor/sht11/sht11-sensor.h"

PROCESS(sense_and_send, "Main process");

PROCESS_THREAD(test_all, ev, data) 
{
    struct sensorval_l hu_r;    // humidity readings
    struct sensorval_l te_r;    // temperature readings

    PROCESS_BEGIN();

    LIST(quantum_tunnel);
    list_init(quantum_tunnel);





    PROCESS_END();
}
