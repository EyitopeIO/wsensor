
#include "contiki.h"
#include "eyitope-calc.h"
#include "dev/sensor/sht11/sht11.h"
#include "dev/sensor/sht11/sht11-sensor.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include "random.h"
#include "math.h"
#include "memb.h"

#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "sys/log.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define WITH_SERVER_REPLY 1
#define UDP_CLIENT_PORT 8000
#define UDP_SERVER_PORT 8100



static struct sensorval_l *th_r;    // Humidity & temperature readings 
static struct sensorval_l *th_p;    // Pointer to block of memory
static struct etimer time_to_read;
static float avr_h;     // Average humidity
static float avr_t;     // Average temperature
static int counter;  

static struct simple_udp_connection udp_conn;
static uip_ipaddr_t dest_addr;     // destination IP address
static char json_formatted[20];     // {"+aa.bb","+cc.dd"}

static void
udp_rx_callback(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{

  LOG_INFO("Received response '%.*s' from ", datalen, (char *) data);
  LOG_INFO_6ADDR(sender_addr);
#if LLSEC802154_CONF_ENABLED
  LOG_INFO_(" LLSEC LV:%d", uipbuf_get_attr(UIPBUF_ATTR_LLSEC_LEVEL));
#endif
  LOG_INFO_("\n");

}
/*---------------------------------------------------------------------------*/


PROCESS(sense_and_send, "Main process");

AUTOSTART_PROCESSES(&sense_and_send);

PROCESS_THREAD(sense_and_send, ev, data) 
{

    PROCESS_BEGIN();

    /* Initialize UDP connection */
    simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL,
                      UDP_SERVER_PORT, udp_rx_callback);

    LIST(quantum_l);        // List of acquired data points
    MEMB(th_buff, struct sensorval_l, WINDOW_SIZE);     // Block of memory
    random_init(3);
    list_init(quantum_l);
    memb_init(&th_buff);
    if((th_p = (struct sensorval_l*)memb_alloc(&th_buff)) == NULL) {
        printf("Not enough memory!\n");
        PROCESS_EXIT();
    }
    avr_h = avr_t = 0.0f;
    etimer_set(&time_to_read, CLOCK_SECOND * 10);   // 1 mins / 7 secs

    // SENSORS_ACTIVATE(sht11_sensor);
    printf("Sensor activated!\n");

    while(1) {
        printf("Loop!\n");
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&time_to_read));

        /* Read temperature values */
        counter = WINDOW_SIZE;
        th_r = th_p;
        while (counter--) { 
            // th_r->reading = abs((float)random_rand());
            thr_r->reading = (float)sht11_sensor.value(SHT11_SENSOR_TEMP);
            // printf("temperature readings: %f\n",th_r->reading);
            list_add(quantum_l, th_r++);
        }
        avr_h = (0.01 * osw_average(&quantum_l)) - 36.9;
        printf("avg1 humidity: %f\n",(double)avr_h);
        avr_h = (0.01 * avr_h) - 36.9;

        /* Read Humidity values */
        counter = WINDOW_SIZE;
        th_r = th_p;
        while (counter--) { 
            // th_r->reading = abs((float)random_rand());
            thr_r->reading = (float)sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
            // printf("th_r2: %f\n",th_r->reading);
            list_add(quantum_l, th_r++); 
        }
        avr_t = osw_average(&quantum_l);
        printf("avg1 temperature: %f\n",(double)avr_t);
        avr_t = -4 + (0.0405 * avr_t) - (0.0000028 * avr_t * avr_t);

        printf("avg humidity: %f\n", (double)avr_h);
        printf("avg temperature: %f\n", (double)avr_t);

        /* Send over network */
        if (NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_addr)) {
            sprintf(json_formatted, "{"%.2f","%.2f"}", (double)avr_t, (double)avr_t);
            simple_udp_sendto(&udp_conn, json_formatted, strlen(json_formatted), &dest_addr);
        }

        etimer_reset(&time_to_read);
    }

    memb_free(&th_buff, th_p);

    PROCESS_END();
}
