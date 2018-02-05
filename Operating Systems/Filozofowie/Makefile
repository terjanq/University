CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -pthread
CLIBS = -lrt

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(CLIBS)
clean: 
	rm -f $(PROGS)
