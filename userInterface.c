#include <stdio.h>
#include <stdlib.h>
/* Function that gets the user input used to access different functionalities of the application */
int userInterface(){
	int choice = 0;
	printf("Please select your action by entering 1, 2, 3, 4 or 5:\n");
	printf("1.Start a new game\n2.View Game settings\n3.View Current Logs\n4.Save logs\n5.Exit application\n");
	printf("\nEnter: ");
	scanf("%d", &choice);
	
	return choice;
}

/* Display settings values from the settings file */
void displaySettings(char* keys, int * values){
	int i = 0;
	printf("SETTINGS:\n");
	/* loop through the array to print out keys (M, N, K) and corresponding values */
	for(i=0; i<3; i++){
		printf("  %c=%d\n", keys[i], values[i]);
	}
}
