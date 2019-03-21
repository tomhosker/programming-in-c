CFLAGS = `sdl2-config --cflags` -O2 -Wall -Wextra -pedantic -ansi -Wfloat-equal
INCS = hoskersdl2.h
TARGET = main
SOURCES =  $(TARGET).c hoskersdl2.c
LIBS =  `sdl2-config --libs` -lm
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

$(TARGET)_d:  $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET)_d -g -O $(CFLAGS) $(LIBS)

memchk: $(TARGET)_d
	valgrind --error-exitcode=1 --quiet --leak-check=full ./$(TARGET)_d test.m7

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET) 
