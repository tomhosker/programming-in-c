CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra -pedantic -ansi -Wfloat-equal
TARGET = translator
SOURCES =  $(TARGET).c
LIBS =  `sdl2-config --libs` -lm
CC = gcc

trans: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) main.c hoskersdl2.c -o printer $(CFLAGS) $(LIBS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)
	$(CC) wab.c -o wab $(CFLAGS) $(LIBS)

print:
	./$(TARGET) input.txt
	./wab
	./printer translated.m7
