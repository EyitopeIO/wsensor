CONTIKI_PROJECT = wsensor
all: $(CONTIKI_PROJECT)
MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

CONTIKI = ../
include $(CONTIKI)/Makefile.include