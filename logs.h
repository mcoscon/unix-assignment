#ifndef HEADER2_FLAG
#define HEADER2_FLAG
/* This is the structure that contains the coordinates (valX, valY), the player turn, the character (X or O) and the pointer to the next node in the linked list */
struct logStruct{
	int turn;
	int valX;
	int valY;
	char player;
	struct logStruct *next;
};

struct logStruct* create_list( int valX, int valY, int turn, char player);
struct logStruct* add_to_list(int valX, int valY, int turn, char player, bool add_to_end);
void print_list();
void saveLogs(int M, int N, int K);
#endif
