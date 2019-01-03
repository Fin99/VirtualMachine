CC=gcc
CFLAGS=-c -Wall -g
SOURCES=parsing-bytecode/file.c parsing-bytecode/loader.c parsing-bytecode/string.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lab6

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@