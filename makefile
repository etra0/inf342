CC=g++
CFLAGS=-Wall -lGL -lGLU -lglut
SOURCES:=$(wildcard 0*_*/main.cpp)
OBJECTS:=$(patsubst %main.cpp, %exec, $(SOURCES))


$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@
