SRC=..
TEST= ../test
EXT=../../SDL2
LIB=$(EXT)/lib
INC= $(EXT)/include
OPT=O0

FLAGS= -std=c++17 -Wall -Wextra  -$(OPT) -I$(INC) -L$(LIB) -llibSDL2 -mconsole
CC=g++
OBJ=main.o glad.o
APP=test.exe

fge.o: $(SRC)/*.h
	$(CC) -c $(SRC)/fge.cpp $(FLAGS)

