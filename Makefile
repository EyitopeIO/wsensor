CONTIKI = ../contiki-ng
all: $(CONTIKI_PROJECT)
include $(CONTIKI)/Makefile.include

CONTIKI_PROJECT = wsensor

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

PROJECT_SOURCEFILES += eyitope-ring-buffer.c eyitope-calc-test.c
