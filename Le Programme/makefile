CC = g++
CFLAGS = -g -Wall -ansi -pedantic -std=c++14
LDFLAGS =
objects = ter3.o node.o afficheps.o creation.o probabilite.o export.o contexte.o
executable = ter1

all: executable

executable: $(objects)
	$(CC) $(objects) -o $(executable)

%.o: %.cpp
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	$(RM) $(objects) $(executable)
