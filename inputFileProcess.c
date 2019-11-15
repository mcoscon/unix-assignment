#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inputFileProcess.h"
/* This function checks if file does not exist, if files contain duplicates & invalid values */
void checkRequired(FILE * f){
	/*line variable to store the number of lines in the file */
	int lines = 0;
	/*ch variable used for checking file below */
	char ch;

	/*Check if the file is valid and can be found */
	if(f == NULL){
		printf("The settings file is not found!\n");
		exit(0);
	}
	else{
		/*Count number of lines until End of File to verify there are only 3 settings */
		while(!feof(f)){
			ch = fgetc(f);
			if(ch == '\n')
			{
				lines++;
			}
		}
		if(lines!=3)
		{
			printf("There might be duplications or invalid formats in settings!\n");
			exit(0);
		}
	}
	
}

/* This function checks if file contains the required settings of M,N,K and if values are valid */
void ReadFile ( FILE *f, char *keys, int *values) { 
    /* i variable used to access the keys and values array */
    int i = 0; 
    /*temp variables used for crosschecking*/
    char tempChar;
    int tempInt;
    /* charReq array contains the necessary settings, M, N, K that is ued for crosschecking below */
    char charReq[]="MNK";
    /*Reset file pointer to point at the start */
    rewind(f);
    /*Goes through the whole file and checks */
    while(fscanf(f,"%c=%d\n", &tempChar,&tempInt)!=EOF){
	keys[i] = tempChar;
	values[i] = tempInt;
	/* Use strchr to check if any other Letters aside from M,N,K are present and check if 
	values are less than 0 */
	if(values[i]<0 || (strchr(charReq, keys[i])==NULL)){
		printf("Error: please check your settings!\n");
		exit(0);
	}
	i++;
    }
} 