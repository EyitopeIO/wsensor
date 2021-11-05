CONTIKI_PROJECT = wsensor
ALL_INCLUDES += $(CONTIKI)/arch/platform/native $(CONTIKI)/os

all: $(CONTIKI_PROJECT)

test: eyitope-calc-test.c eyitope-ring-buffer.c eyitope-ring-buffer.h
	$(CC) -I$(ALL_INCLUDES) eyitope-calc-test.c eyitope-ring-buffer.c -o test

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test
PROJECT_SOURCEFILES += eyitope-calc-test.c eyitope-ring-buffer.c eyitope.c eyitope-calc.c

CONTIKI = ~/contiki-ng
include $(CONTIKI)/Makefile.include
include $(CONTIKI)/arch/platform/native/Makefile.native