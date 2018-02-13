CC = g++
CFLAGS = -O2 -Wall -Wextra
CLIBS = ''

SRCS = $(wildcard *.cpp)

PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(CLIBS)
clean: 
	rm -f $(PROGS)
