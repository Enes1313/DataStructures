CC=gcc
CFLAGS= -std=c90 -Wall -Wextra -Wconversion -pedantic

IDIR:= DS/inc/
S1DIR:= DS/*.c \
	Test/*.c

S2DIR:= DS/*.c \
	Simulation/*.c

EX=main

all: $(EX)

$(EX):
	$(CC) $(CFLAGS) -I$(IDIR) $(S1DIR) -o test
	$(CC) $(CFLAGS) -I$(IDIR) $(S2DIR) -o simulation

clean:
	rm test
	rm simulation


