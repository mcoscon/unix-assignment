#ifndef PLAY_BOARD
#define PLAY_BOARD
int playGame(char* gameBoard, int ROWS, int COLS, int N);
void initBoard (char*gameBoard , int COLS, int ROWS);
void printBoard (char* gameBoard, int ROWS, int COLS);
void makeMove (char* gameBoard,int player, int ROWS, int COLS);
int checkWinner(char* gameBoard, int player, int ROWS, int COLS, int N);
#endif  
