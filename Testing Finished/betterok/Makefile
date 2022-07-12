CC = gcc
CFLAGS = -ggdb -Wall -Wpedantic -Wextra -Og

.PHONY: clean

files = betterok.o

main: $(files) betterok.h
betterok.o: betterok.c betterok.h

clean:
	rm -vf $(files) main