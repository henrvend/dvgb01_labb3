CC = gcc
CFLAGS = -Wall -Wextra

all: vmsim

vmsim: vmsim.c
	$(CC) $(CFLAGS) -o vmsim vmsim.c

run: vmsim
	./vmsim -a optimal -n 16 -f trace_1.dat

run1: vmsim
	./vmsim -a lru -n 16 -f trace_1.dat

run2: vmsim
	./vmsim -a fifo -n 16 -f trace_1.dat


clean:
	rm -f vmsim

.PHONY: default
default: run
