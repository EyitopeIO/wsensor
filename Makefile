CONTIKI_PROJECT = wsensor

ALL_INCLUDES += -I$(CONTIKI)/os -I$(CONTIKI)/arch/platform/native

all: $(CONTIKI_PROJECT)
	$(CC) eyitope-calc-test.c eyitope-ring-buffer.c -o test

test: eyitope-calc-test.c eyitope-ring-buffer.c eyitope-ring-buffer.h
	$(CC) $(ALL_INCLUDES) eyitope-calc-test.c eyitope-ring-buffer.c -o test

# MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test
# PROJECT_SOURCEFILES += eyitope-calc-test.c eyitope-ring-buffer.c eyitope.c eyitope-calc.c

CONTIKI = ~/contiki-ng
include $(CONTIKI)/Makefile.include