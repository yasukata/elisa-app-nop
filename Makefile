PROGS = libelisa-app-nop.so

CC = gcc

CLEANFILES = $(PROGS) *.o *.d

LIBELISA_DIR = ./deps/elisa/lib/libelisa
LIBELISA_EXTRA_DIR = ./deps/elisa/lib/libelisa-extra

NO_MAN =
CFLAGS = -O3 -pipe
CFLAGS += -g -rdynamic
CFLAGS += -Werror
CFLAGS += -Wall -Wunused-function
CFLAGS += -Wextra
CFLAGS += -shared -fPIC

CFLAGS += -I$(LIBELISA_DIR)/include -I$(LIBELISA_EXTRA_DIR)/include

LDFLAGS += -ldl -lelf

C_SRCS = main.c

C_OBJS = $(C_SRCS:.c=.o)

OBJS = $(C_OBJS)

CLEANFILES += $(C_OBJS)

.PHONY: all
all: $(PROGS)

$(PROGS): $(OBJS) $(LIBELISA_DIR)/libelisa.a
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-@rm -rf $(CLEANFILES)
