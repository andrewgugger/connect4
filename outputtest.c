#include "project.h"


void openDisplay(void);
void closeDisplay(void);
void displayWinner(void);
void clear_board(void);
void check_connect(int i, int x, char letter);
bool check(int i, int x);
void append(int i, int x, char letter);
void board(void);
void place(char letter, int x);
void displayDot(char letter, int x, int y);
void clearDisplay(void);
bool check_score(void);


int main(void){
	openDisplay();
	printf("open display\n");
	clearDisplay();
	printf("clear display\n");

	printf("build board \n");
	board();

	printf("displayed dot \n");
	displayDot('A', 2, 2);


	place('A', 6);
	printf("placed 'chip' \n");
	
	
	return 1;
}
