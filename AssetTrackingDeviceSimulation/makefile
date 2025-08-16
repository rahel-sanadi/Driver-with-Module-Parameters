CC = gcc
CFLAGS = -Wall -Wextra -O2

all: asset_tracking

asset_tracking: main.o payload.o
	$(CC) $(CFLAGS) main.o payload.o -o asset_tracking

main.o: main.c payload.h
payload.o: payload.c payload.h

clean:
	rm -f *.o asset_tracking
