CONTIKI = ../contiki-ng

include $(CONTIKI)/Makefile.include

CONTIKI_PROJECT = wsensor

CFLAGS += --Wall --Wextra 

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

all: $(CONTIKI_PROJECT)

test-queue: eyitope-ring-buffer.h
	$(CC) eyitope-ring-buffer.c -o test-queue
	




