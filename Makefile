CONTIKI_PROJECT = eyitope

all: $(CONTIKI_PROJECT) 

PROJECT_SOURCEFILES += eyitope-calc.c
CFLAGS += -Wall
#define UIP_CONF_IPV6_RPL  1
#define RPL_CONF_DIS_INTERVAL	300
#define NETSTACK_MAX_ROUTE_ENTRIES 5

CONTIKI = ..
include $(CONTIKI)/Makefile.include
