CC = g++
CFLAGS = -g -Wall -ansi -pedantic -std=c++14
LDFLAGS =
objects = creator.o rules.o
executable = ruleMaker

all: executable

executable: $(objects)
	$(CC) $(objects) -o $(executable)

%.o: %.cpp
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	$(RM) $(objects) $(executable)
