CC=g++
CFLAGS=-Wall -lGL -lGLU -lglut
SOURCES:=$(wildcard 0*_*/main.cpp)
OBJECTS:=$(patsubst %main.cpp, %exec, $(SOURCES))


$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

clean:
	for i in $(wildcard 0*_*/exec); do rm $$i; done

all:
	for i in $(OBJECTS); do make $$i; done