#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include "logs.h"

/* Initialising necessary pointers to the structures where we store, access and print the logs obtained from playing */
static struct logStruct *head = NULL;
static struct logStruct *curr = NULL;

/* Here we create the first node of the linked list if it has not been created yet */
struct logStruct* create_list(int valX, int valY, int turn, char player){
    /*Allocate some memory for the first structure */
    struct logStruct *ptr = (struct logStruct*)malloc(sizeof(struct logStruct));
    /*Set the struct fields with the values obtained from the playing the game (See logs.h for explanation on struct fields*/
    ptr->valX = valX;
    ptr->valY=valY;
    ptr->turn=turn; 
    ptr->player=player;
    ptr->next = NULL;
    
    /* Set the pointer allocated earlier to point at the same address of head & curr which is NULL */
    head = curr = ptr;
    return ptr;
}

/* Here we add the following nodes of the linked list */
struct logStruct* add_to_list(int valX, int valY, int turn, char player, bool add_to_end)
{
    /* Allocate some memory for the next nodes of the linked list */
    struct logStruct *ptr = (struct logStruct*)malloc(sizeof(struct logStruct));
    if(NULL == head)
    {
	
        return (create_list(valX+1, valY+1, turn, player));
    }

    if(NULL == ptr)
    {
        return NULL;
    }
    /* We set the following struct values of the node based on the values obtained from the game */
    ptr->valX = valX+1;
    ptr->valY=valY+1;
    ptr->turn=turn;
    ptr->player=player;
    ptr->next = NULL;

    /* Here is a small functionality that can add to the end or at the start of the list. For simplicity's sake we add at the end*/
    if(add_to_end)
    {
        /* Set current pointer to point to the next in the node */
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}

/* Function used to print all the values from nodes in the linked list */
void print_list(void)
{
    /* Here we have a pointer that points to the address of the first node */
    struct logStruct *ptr = head;
    /*Loop through the whole linked list and print out the values of fields from each individual node */
    while(ptr != NULL)
    {
        	printf("  Turn: %d\n  Player: %c\n  Location: %d,%d\n\n",ptr->turn, ptr->player, ptr->valX, ptr->valY);
	ptr = ptr->next;
    }
    return;
}

/* Here we save the logs from the linked list to a file */
void saveLogs(int M, int N, int K){
	/* File pointer to access a file to write the game logs to */
	FILE * fptr;
	/* Pointer that points to the first node in the linked list */
	struct logStruct *logptr = head;
	/* Values for naming the file to be saved */
	int hours, minutes, day, month;
	time_t now;
	/*Here we use the time library to access the struct values of the time now and store in variables hours, minutes, day and month */
	struct tm *local = localtime(&now);
	/* Allocate some space to store the filename */
	char fileName[25];
	hours = local->tm_hour;      	/* get hours since midnight (0-23) */
    	minutes = local->tm_min;     	/* get minutes passed after the hour (0-59) */
    	day = local->tm_mday;        	/* get day of month (1 to 31) */
        month = local->tm_mon + 1;   	/* get month of year (0 to 11) */
        
    /* Store in fileName char array */
	sprintf(fileName, "MNK_%d-%d-%d_%02d-%02d_%02d-%02d.log", M, N, K, hours, minutes, day, month);
    
    /* Create and open the file for writing */
	fptr = fopen(fileName, "w");
	if(fptr == NULL)
    	{
        	/* File not created hence exit */
        	printf("Unable to create file.\n");
        	exit(EXIT_FAILURE);
    	}
	/* Here we loop through the linked list and write every node values to the file */
    	while(logptr != NULL)
   	{
		
			fprintf(fptr,"  Turn: %d\n  Player: %c\n  Location: %d,%d\n",logptr->turn, logptr->player, logptr->valX, logptr->valY);
	        logptr = logptr->next;
 	}
	
	printf("Logs successfully written to %d%d%d_%02d-%02d_%02d-%02d.log!\n", M, N, K, hours, minutes, day, month);
	/*Close the file after we are done */
	fclose(fptr);
   
}



