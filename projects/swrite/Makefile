# Not the best makefile, but it's a start...
NAME=swrite
CC=gcc
CFLAGS=-Wall -std=gnu99 -o$(NAME) -I../../lib/
LDFLAGS=
SOURCES=main.c ../../lib/serial.c ../../lib/rs232.c

swrite :
	$(CC) $(LFLAGS) $(CFLAGS) $(SOURCES)

clean: 
	rm $(NAME)
