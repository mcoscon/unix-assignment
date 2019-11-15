CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -std=c89 
OBJ = TicTacToe.o userInterface.o inputFileProcess.o logs.o playBoard.o
EXEC = TicTacToe

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

TicTacToe.o : TicTacToe.c userInterface.h inputFileProcess.h logs.h playBoard.h
	$(CC) -c TicTacToe.c $(CFLAGS)

userInterface.o :  userInterface.c userInterface.h
	$(CC) -c userInterface.c $(CFLAGS)

inputFileProcess.o : inputFileProcess.c inputFileProcess.h
	$(CC) -c inputFileProcess.c $(CFLAGS)

logs.o : logs.c logs.h
	$(CC) -c logs.c $(CFLAGS)

playBoard.o : playBoard.c playBoard.h logs.h




