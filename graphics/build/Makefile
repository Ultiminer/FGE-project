SRC= ../src
TEST= ../test
EXT=../../SDL2
LIB=$(EXT)/lib
INC= $(EXT)/include
OPT=O0

FLAGS= -std=c++17 -Wall -Wextra  -$(OPT) -I$(INC) -L$(LIB) -llibSDL2 -mconsole
CC=g++
OBJ=main.o glad.o
APP=test.exe

execute: $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -o $(APP)
	./$(APP) 
	
main.o: $(SRC)/*.h
	$(CC) -c $(SRC)/main.cpp $(FLAGS)

glad.o: $(SRC)/glad.h
	$(CC) -c $(SRC)/glad.c $(FLAGS)
