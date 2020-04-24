CC=g++
CPPFLAGS=-std=c++11
LIBS=-lsdl2 -lsdl2_image
LIBS_LINUX=-lSDL2 -lSDL2_image
INPUT=main.cpp
BIN=minecraft
all:
	$(CC) $(INPUT) $(CPPFLAGS) $(LIBS) -o $(BIN)
linux:
	$(CC) $(INPUT) $(CPPFLAGS) $(LIBS_LINUX) -o $(BIN) 
