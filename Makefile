CONTIKI = ../contiki-ng
all: $(CONTIKI_PROJECT)
include $(CONTIKI)/Makefile.include

CONTIKI_PROJECT = wsensor

# MODULES += $(CONTIKI_NG_SERVICES_DIR)/unit-test

# TEST_SRC += eyitope-ring-buffer.c eyitope-calc-test.c
# TEST_HDR += eyitope-ring-buffer.h


# test-all: $(TEST_SRC) $(TEST_HDR)
# 	$(CC) $(TEST_SRC) -o $@



