CC = g++
CFLAGS = -std=c++11 -g -Wall -ansi
LDFLAGS =
objects = ter2.o node.o 
executable = ter1

all: executable

executable: $(objects)
	$(CC) $(objects) -o $(executable)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	$(RM) $(objects) $(executable)
