#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "inputFileProcess.h"
#include "userInterface.h"
#include "logs.h"
#include "playBoard.h"


int main(int argc, char *argv[]){
	/* These are variables used for user menu selection, dimensions of the TicTacToe board and the number of consecutive tiles to win */
	int initChoice, height, width, tilestoWin;
	/* Variable used for game count */
	int gameCount = 0;
	/* The keys & values array are used for storing settings M, N, K */
	char keys[3];
	int values[3];
	/* The variable gameBoard is a pointer to an array which is the board used to play TicTacToe */
	char * gameBoard;
	/* File pointer used for the settings file */
	FILE* fptr;
	/* Get command line arguments */
	fptr = fopen(argv[1], "r");
	/* Necessary checks (see inputFileProcess.c for details) */
	checkRequired(fptr);
	/* Editor Conditional Compiling */
	#ifdef EDITOR
	writeToFileCond();
	#endif
	
	/*Here we read the file and do some check then store the settings values in the keys & values array*/
	ReadFile(fptr, keys, values);
	width = values[0];
	height = values[1];
	tilestoWin = values[2];
	/*Allocate some memory for the gameBoard char array*/
	gameBoard = (char*)malloc(width*height*sizeof(char));

	/* Do while loop unless user exits or when user enters an invalid choice from the menu*/
	do{
		/*User is presented with the menu and stores their choice in initChoice (see userInterface.c) */
		initChoice = userInterface();
		switch(initChoice){
		case 1:
			/* Plays TicTacToe (see playBoard.c) */
			playGame(gameBoard, width, height, tilestoWin);      
			gameCount++;
			break;
		
		case 2:
			/*Prints out current settings using the keys and values array that was set earlier (see userInterface.c) */
			displaySettings(keys, values);	
			break;
			
		case 3:
			/*Prints out the game logs that was stored in a linked list */
			printf("\n");
			displaySettings(keys, values);
			printf("\n");
			printf("GAME %d \n", gameCount);
			print_list();
			printf("\n");
			break;
		case 4:
			/*Secret Conditional Compiling*/
			#ifdef SECRET
			printf("You're in secret mode! You lost the ability to save logs to file!\n");
			break;
			#endif 
			/*Save logs to a file (see logs.c)*/
			saveLogs(width, height, tilestoWin);
			printf("\n");
			break;
		case 5:
			/*Exit application*/
			printf("The application will now exit. Bye!\n");
			break;
		default:
			printf("Invalid input! Please try again.\n");
			break;
		}
	
	}while(initChoice!=5);
	/* free the gameboard array as we are done with the application*/
	free(gameBoard);
	/*close the file pointer as we are done with the application */
	fclose(fptr);
	return 0;
}