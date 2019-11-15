#include <stdio.h>
#include<stdbool.h>
#include "playBoard.h"
#include "logs.h"
/* Set initial board values to be empty*/
#define CHARINIT ' '        
/* Set player symmbols used in the game */
#define PLAYER1SYMBOL 'X'     
#define PLAYER2SYMBOL 'O'    
/*Variable used to reset the number of turn back to 1 when a player has won a game */
static int resetTurn = 1;

/* Here we play the TicTacToe game using several functions we defined in this file */
int playGame(char* gameBoard, int ROWS, int COLS, int N)
{
    int turn = 0, player = 0, winner = 0;
 
    initBoard(gameBoard, ROWS, COLS);
    
    do
    {
        /* Every time this loop executes, a unique turn is about to be made */
        turn++;                                
        /* This mod function alternates the player variable between 1 & 2 each turn */
        player = (turn+1)%2+1; 
        /*See makeMove function definition below */
        makeMove(gameBoard,player, ROWS, COLS);
        /*See printBoard function definition below */
        printBoard(gameBoard, ROWS, COLS);
        /*See checkWinner function definition below */
        winner = checkWinner(gameBoard,player, ROWS, COLS, N);

        if (winner != 0)
        {
            /*See printBoard function definition below */
            printBoard(gameBoard, ROWS, COLS);
            printf("\n\nPlayer %i, has won with %d tiles in a row!\n",winner,N);
            /* Reset turns to 1 after winner has been found */
	        resetTurn = 1;
	
            return winner;
        }

    } while ( turn < ROWS*COLS );                           /* Once ROWS*COLS turns have elapsed */

    /* The board is full and the game is over */
    printf("\n\nIts a draw!\n\nThere is no winner\n");  
    return winner;
}

/* Here we initialise the board game values in each row/column to be an empty space everytime a new game starts */
void initBoard (char*gameBoard , int COLS, int ROWS)
{
    int row = 0, col = 0;

    for (row=0;row<ROWS;row++)
    {
        for (col=0;col<COLS;col++)
        {
            /* Set row/column to ' ' */
            *(gameBoard + row*COLS + col) = CHARINIT;     /* Fill the gameBoard with INITCHAR characters */
        }
    }
     /* Having this here prints out the board before*/
    printBoard(gameBoard, COLS, ROWS);                      
    return;                            
}

/* Here we print out the structure of the tictactoe board */
void printBoard (char* gameBoard, int ROWS, int COLS)    
{                                               
    int row = 0, col = 0, i=0;                  
                                                
    printf("\n");                              
                                                
    for (row=0;row<ROWS;row++)                  
    {                                           
        if (row == 0)                          
        {                                       
            printf("  ");                       

            for (i=0;i<COLS;i++)
            {
                printf(" %i  ",i+1);
            }

            printf("\n\n");
        }

        for (col=0;col<COLS;col++)
        {
            if (col==0)
                printf("%i ",row+1);

            printf(" %c ",*(gameBoard + row*COLS + col));

            if (col<COLS-1)
                printf("|");
        }

        printf("\n");

        if (row < ROWS-1)
        {
            for(i=0;i<COLS-1;i++)
            {
                if(i==0)
                    printf("  ----");
                else
                    printf("----");
            }

            printf("---\n");
        }
    }

    return;
}


void makeMove (char* gameBoard,int player, int ROWS, int COLS)
{
    int row = 0, col = 0, i=0;
    char currentChar;
    /* This gets the correct player's mark */
    if (player == 1)                    
        currentChar = PLAYER1SYMBOL;
    else
        currentChar = PLAYER2SYMBOL;

    /* Here we save the user input coordinates to col and row variable respectively */
    printf("\nPlayer %i, please enter your column (y) : ",player);
    scanf("%i",&col);
    printf("Please enter your row (x): ");
    scanf("%i",&row);

    /* These lines translate the user's rows and columns numbering */
    /* (starting with 1) to the computer's (starting with 0) */
    row--;                              
    col--;                              

    /*Here we check if the given input is valid or not */
    while(*(gameBoard + row*COLS + col) != CHARINIT || row > ROWS-1 || col > COLS-1)  
    {                                                                      
        printBoard(gameBoard, ROWS, COLS);
        for (i=0;i<4-2*ROWS;i++)
            printf("\n");
        printf("\nPlayer %i, please enter a valid move! Column first, then row.\n",player);
        scanf("%i %i",&col,&row);

        row--;                          
        col--;
    }
	
    /* Finally, we store the correct mark (X or O) into the given location*/
    *(gameBoard + row*COLS + col) = currentChar;  

    /* And we store the coordinate values, the turn, the current character (X or O) in the linked list node */
    add_to_list(row, col, resetTurn, currentChar, true);
    /*Increase turn by 1 when it is the next player's move */
    resetTurn++;
    return;                             
}

/* Here we check the winner of the game based on the setting file 'K' */
int checkWinner(char* gameBoard, int player, int ROWS, int COLS, int N)     
{                                                           
    int row = 0, col = 0, i = 0;
    char currentChar;

    if (player == 1)
        currentChar = PLAYER1SYMBOL;
    else
        currentChar = PLAYER2SYMBOL;

    for ( row = 0; row < ROWS; row++)                       
    {
        for ( col = 0; col < (COLS-(N-1)); col++)           
        {
            while (*(gameBoard + row*COLS + col) == currentChar)      
            {
                col++;
                i++;
                if (i == N)
                {
                    return player;
                }
            }
            i = 0;
        }
    }

    for ( col = 0; col < COLS; col++)                       
    {
        for ( row = 0; row < (ROWS-(N-1)); row++)
        {
            while (*(gameBoard + row*COLS + col) == currentChar)
            {
                row++;
                i++;
                if (i == N)
                {
                    return player;
                }
            }
            i = 0;
        }
    }

    for ( col = 0; col < (COLS - (N-1)); col++)             
    {
        for ( row = 0; row < (ROWS-(N-1)); row++)
        {
            while (*(gameBoard + row*COLS + col) == currentChar)
            {
                row++;
                col++;
                i++;
                if (i == N)
                {
                    return player;
                }
            }
            i = 0;
        }
    }
                                                        
    for ( col = COLS-1; col > 0+(N-2); col--)           
    {                                                   
        for ( row = 0; row < (ROWS-(N-1)); row++)       
        {
            while (*(gameBoard + row*COLS + col) == currentChar)  
            {
                row++;                                  
                col--;                                  
                i++;                                    
                if (i == N)                             
                {
                    return player;                      
                }
 	    }                                       
            i = 0;                                      
        }                                               
    }
   
    return 0;                                       
}                                                        

