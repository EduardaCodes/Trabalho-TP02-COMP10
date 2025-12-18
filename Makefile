CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = compilador
SOURCES = main.c lexico.c sintatico.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c tokens.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	./$(TARGET) teste.pas

.PHONY: all clean test