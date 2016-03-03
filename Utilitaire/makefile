CC = g++
CFLAGS = -std=c++14 -g -Wall -ansi
LDFLAGS =
objects = creator.o rules.o
executable = ruleMaker

all: executable

executable: $(objects)
	$(CC) $(objects) -o $(executable)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

clean:
	$(RM) $(objects) $(executable)
