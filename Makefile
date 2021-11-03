CONTIKI = ../contiki-ng

include $(CONTIKI)/Makefile.include

CONTIKI_PROJECT = wsensor

CFLAGS += --Wall --Wextra 

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

all: $(CONTIKI_PROJECT)

test-all: eyitope-calc-test.h
	$(CC) eyitope-calc-test.c -o test-all
	




