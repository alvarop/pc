# Not the best makefile, but it's a start...
NAME=eventlog
CC=gcc
CFLAGS=-Wall -std=gnu99 -o$(NAME) -I../../lib/ -pthread
LDFLAGS=
SOURCES=main.c ../../lib/serial.c ../../lib/rs232.c

swrite :
	$(CC) $(LFLAGS) $(CFLAGS) $(SOURCES)

clean: 
	rm $(NAME)
