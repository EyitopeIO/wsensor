CONTIKI_PROJECT = wsensor
CONTIKI = ../contiki-ng
include $(CONTIKI)/Makefile.include

MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

TEST_SRC += eyitope-ring-buffer.c eyitope-calc-test.c
TEST_HDR += eyitope-ring-buffer.h

all: $(CONTIKI_PROJECT)

$(CONTIKI_PROJECT)/test-all: $(TEST_SRC) $(TEST_HDR)
	$(CC) $(TEST_SRC) -o $@



