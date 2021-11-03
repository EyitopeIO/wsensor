CONTIKI = ../contiki-ng

include $(CONTIKI)/Makefile.include

CONTIKI_PROJECT = wsensor

CFLAGS += --Wall --Wextra 

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

all: $(CONTIKI_PROJECT)

test-all: eyitope-calc-test.o
	
eyitope-calc-test.o: eyitope-ring-buffer.o 
	$(CC) eyitope-calc-test.c -o test-all

eyitope-ring-buffer.o: eyitope-ring-buffer.h
	$(CC) eyitope-ring-buffer.c -o eyitope-ring-buffer.o



