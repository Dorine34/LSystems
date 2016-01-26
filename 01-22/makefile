CC = g++
CFLAGS = -std=c99 -Wall -ansi
LDFLAGS =
objects = ter2.cpp
executable = ter1

all: executable

executable: $(objects)
	$(CC) $(objects) -o $(executable)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $< 

clean:
	$(RM) $(objects) $(executable)
