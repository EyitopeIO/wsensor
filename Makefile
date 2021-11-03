CONTIKI = ..

include $(CONTIKI)/Makefile.include

CONTIKI_PROJECT = wsensor

CFLAGS += --Wall --Wextra 

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

all: $(CONTIKI_PROJECT)

test_all: eyitope-test-calc.o
	$(CC) eyitope-test-calc.c -o test_all

eyitope-test-calc.o: eyitope-calc.h eyitope-calc.calc



