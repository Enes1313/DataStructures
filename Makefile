CC=gcc
CFLAGS= -std=c99 -O0 -Wall -pedantic

IDIR:= DS/inc/
SDIR:= DS/*.c \
	Test/*.c

EX=main

all: $(EX)

$(EX):
	$(CC) $(CFLAGS) -I$(IDIR) $(SDIR) -o $(EX)

clean:
	rm $(EX)


