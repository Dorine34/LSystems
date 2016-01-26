CC = g++
CFLAGS = -std=c++11 -g -Wall -ansi
LDFLAGS =
objects = ter3.o node.o afficheps.o
executable = ter1

all: executable

executable: $(objects)
	$(CC) $(objects) -o $(executable)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	$(RM) $(objects) $(executable)
