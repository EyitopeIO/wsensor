CONTIKI_PROJECT = eyitope-calc-test

all: $(CONTIKI_PROJECT) eyitope-calc-test.c

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test
PROJECT_SOURCEFILES += ../eyitope-calc.c
CFLAGS += -Wall

CONTIKI = ..
include $(CONTIKI)/Makefile.include
