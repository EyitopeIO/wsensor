CONTIKI = ../contiki-ng

include $(CONTIKI)/Makefile.include

CONTIKI_PROJECT = wsensor

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

PROJECT_SOURCEFILES += eyitope-ring-buffer.c eyitope-calc-test.c
PROJECT_HEADERS += eyitope-ring-buffer.h eyitope.h

all: $(CONTIKI_PROJECT)

test-all: $(PROJECT_SOURCEFILES) $(PROJECT_HEADERS)
	$(CC) $(PROJECT_SOURCEFILES) -o test-all 


