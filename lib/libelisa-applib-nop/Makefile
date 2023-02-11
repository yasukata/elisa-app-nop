PROGS = lib.so

CLEANFILES = $(PROGS) *.o

NO_MAN =
CFLAGS = -O3 -pipe -g -rdynamic
CFLAGS += -Werror -Wextra -Wall -Wunused-function
CFLAGS += -ffreestanding -fno-stack-protector
CFLAGS += -nostdlib -nodefaultlibs -nostdinc -fno-builtin
CFLAGS += -fno-strict-aliasing
CFLAGS += -static
CFLAGS += -shared -fPIC

LDFLAGS += -fPIC

C_SRCS = main.c

C_OBJS = $(C_SRCS:.c=.o)

OBJS = $(C_OBJS)

.PHONY: all
all: $(PROGS)

$(PROGS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	-@rm -rf $(CLEANFILES)
