CONTIKI_PROJECT = wsensor
all: $(CONTIKI_PROJECT)
MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

CONTIKI = ../contiki-ng
include $(CONTIKI)/Makefile.include