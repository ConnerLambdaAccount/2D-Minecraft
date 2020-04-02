CC=g++
CPPFLAGS=-std=c++11 -lsdl2 -lsdl2_image
INPUT=main.cpp
BIN=minecraft
all:
	$(CC) $(INPUT) $(CPPFLAGS) -o $(BIN)
