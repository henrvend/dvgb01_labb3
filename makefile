CC = gcc
CFLAGS = -Wall -Wextra

all: vmsim

vmsim: vmsim.c
	$(CC) $(CFLAGS) -o vmsim vmsim.c

run: vmsim
	./vmsim -a fifo -n 4 -f trace.dat

clean:
	rm -f vmsim

.PHONY: default
default: run
