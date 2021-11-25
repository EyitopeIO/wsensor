
#include "contiki.h"
#include "eyitope-calc.h"
// #include "dev/sensor/sht11/sht11.h"
// #include "dev/sensor/sht11/sht11-sensor.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "dev/leds.h"
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


// static struct sensorval_l *th_r;    // Humidity & temperature readings 
// static struct sensorval_l *th_p;    // Pointer to block of memory
static struct etimer time_to_read;

/* Address of most recent readinfs in dynamic memory area*/
static struct sensorval_l *hu_r;
static struct sensorval_l *te_r;

/* Pointer to dynamic memory area */
static struct sensorval_l *hu_p;
static struct sensorval_l *te_p;

static float avr_h;     // Average humidity
static float avr_t;     // Average temperature
static int counter = WINDOW_SIZE;  

static struct simple_udp_connection udp_conn;
static uip_ipaddr_t dest_addr;     // destination IP address
static char json_formatted[24];     // {"+aa.bb","+cc.dd"}

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

  printf("Received message: %d\n", (int)(*data));

}
/*---------------------------------------------------------------------------*/


PROCESS(sense_and_send, "Main process");

AUTOSTART_PROCESSES(&sense_and_send);

PROCESS_THREAD(sense_and_send, ev, data) 
{

    PROCESS_BEGIN();
    // leds_on(LEDS_ALL);

    /* Initialize UDP connection */
    simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL,
                      UDP_SERVER_PORT, udp_rx_callback);

    // LIST(quantum_l);        // List of acquired data points
    
    /* represents the window */
    LIST(quantum_hu);
    LIST(quantum_te);

    //MEMB(th_buff, struct sensorval_l, WINDOW_SIZE);     // Block of memory
    
    MEMB(t_buff, struct sensorval_l, WINDOW_SIZE);
    MEMB(h_buff, struct sensorval_l, WINDOW_SIZE);

    random_init(3);
    // list_init(quantum_l);
    // memb_init(&th_buff);
    
    /* Initialise dynamic memory areas */
    list_init(quantum_hu);
    list_init(quantum_te);
    memb_init(&t_buff);
    memb_init(&h_buff);

    if((te_p = (struct sensorval_l*)memb_alloc(&t_buff)) == NULL) {
        printf("te memory low!\n");
        PROCESS_EXIT();
    }

    if((hu_p = (struct sensorval_l*)memb_alloc(&h_buff)) == NULL) {
        printf("hu memory low!\n");
        PROCESS_EXIT();
    }

    // if((th_p = (struct sensorval_l*)memb_alloc(&th_buff)) == NULL) {
    //     // printf("Not enough memory!\n");
    //     PROCESS_EXIT();
    // }

    avr_h = avr_t = 0.0f;
    etimer_set(&time_to_read, CLOCK_SECOND * 9);   // 60s / WINDOW_SIZE ~= 9 secs

    // SENSORS_ACTIVATE(sht11_sensor);
    printf("Sensor activated!\n");

    // leds_off(LEDS_ALL);

    while(1) {
        
        printf("Loop!\n");
        
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&time_to_read));

        /* Read temperature values */
        te_r->reading = 33.33f;
        // te_r->reading = (float)sht11_sensor.value(SHT11_SENSOR_TEMP);
        // printf("temperature readings: %f\n",(double)te_r->reading);
        list_add(quantum_te, te_r++);

        /* Read Humidity values */
        hu_r->reading = 44.44f;
        // th_r->reading = (float)sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
        // printf("humidity readings: %f\n",(double)hu_r->reading);
        list_add(quantum_hu, hu_r++); 

        if (counter == 0) { 
          // leds_on(LEDS_ALL);

          avr_t = osw_average(&quantum_te);
          avr_t = -4 + (0.0405 * avr_t) - (0.0000028 * avr_t * avr_t);
          printf("avg1 temperature: %f\n",(double)avr_t);
  
          avr_h = (0.01 * osw_average(&quantum_hu)) - 36.9;
          avr_h = (0.01 * avr_h) - 36.9;
          printf("avg1 humidity: %f\n",(double)avr_h);

          /* Send over network */
          if (NETSTACK_ROUTING.node_is_reachable() && NETSTACK_ROUTING.get_root_ipaddr(&dest_addr)) {
              sprintf(json_formatted, "{\"%.2f\",\"%.2f\"}", (double)avr_t, (double)avr_t);
              simple_udp_sendto(&udp_conn, json_formatted, strlen(json_formatted), &dest_addr);
          }

          counter = WINDOW_SIZE;
          te_r = te_p;
          hu_r = hu_p;

          // leds_off(LEDS_ALL);
        }
        count--;
        etimer_reset(&time_to_read);
    }

    memb_free(&t_buff, te_p);
    memb_free(&h_buff, hu_p);

    PROCESS_END();
}
