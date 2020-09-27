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
	$(CC) $(CFLAGS) -I$(IDIR) $(S1DIR) -o Test/test
	$(CC) $(CFLAGS) -I$(IDIR) $(S2DIR) -o Test/simulation

clean:
	rm Test/test
	rm Test/simulation


