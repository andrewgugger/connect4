#include "project.h"

#define BLACK 0x0000
#define RED 0xF800
#define BLUE  0x00FF
#define YELLOW 0xFF00
#define WHITE 0xFFFF


pi_framebuffer_t *fb = NULL;

int a=1;
int b=2;

//score of player  A and B
int scoreA=0, scoreB=0;

/*total_chips keeps track of how many total chips
have been placed. In the event that the board gets filled 
up and no connect-4s are made the game must restart*/
int total_chips=0;

 /*create the connect 4 board, this will be used
to check if a connect 4 was made */
char board_spots[4][5];

void openDisplay(void){
	if(fb==NULL){
		fb=getFrameBuffer();
	}
}

void closeDisplay(void){
	if(fb){
		clearFrameBuffer(fb, BLACK);
		freeFrameBuffer(fb);
		fb=NULL;
	}
}

void displayWinner(void){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(scoreA>scoreB){
				fb->bitmap->pixel[j][i]=BLUE;
				usleep(1500);
			}
			else{
				fb->bitmap->pixel[j][i]=RED;
				usleep(1500);
			}
		}
	}
	shake();
}
			




void clear_board(void){


	//clear sense hat
	for(int i=2;i<=6;i++){
		for(int j=3;j<7;j++){
			fb->bitmap->pixel[j][i]=BLACK;
		}
	}

	//clear matrix
	for(int q=0;q<4;q++){
		for(int w=0;w<5;w++){
			board_spots[q][w]='o';
		}
	}
	
}

//function checks if the new input gets a connect 4
void check_connect(int i, int x, char letter){
	int rx = x-2;
	int count = 0;
	//check all rows
	for(int j=0;j<4;j++){
		if(board_spots[j][rx]==letter){
			count++;
			if(count==4){
				if(letter=='A'){
					fb->bitmap->pixel[0][scoreA]=BLUE;
					scoreA++;
					shake();
					return;
				}else{
					fb->bitmap->pixel[1][scoreB]=RED;
					scoreB++;
					shake();
					return;
				}
			}
			else{
				continue;
			}
		}
		else{
			break;
		}
	}

	count=0;
	//check all columns
	for(int c=0;c<5;c++){
		//fprintf(stderr,"column %d \n",c);
		if(board_spots[i][c]==letter){
			count++;
			if(count==4){
				if(letter=='A'){
					fb->bitmap->pixel[0][scoreA]=BLUE;
					scoreA++;
					shake();
					return;
				}else{
					fb->bitmap->pixel[1][scoreB]=RED;
					scoreB++;
					shake();
					return;
				}
			}
			else{
				continue;
			}
		}
		else{
			break;
		}
	}
	
	count=0;
	//check all columns part 2
	for(int c=1;c<5;c++){
		//fprintf(stderr,"column %d \n",c);
		if(board_spots[i][c]==letter){
			count++;
			if(count==4){
				if(letter=='A'){
					fb->bitmap->pixel[0][scoreA]=BLUE;
					scoreA++;
					shake();
					return;
				}else{
					fb->bitmap->pixel[1][scoreB]=RED;
					scoreB++;
					shake();
					return;
				}
			}
			else{
				continue;
			}
		}
		else{
			break;
		}
	}

	//check all diagonals

	/*
	since there are 4 rows and 5 columns I will just check each turn
	if the new piece played is a digonal conenct 4.
	*/
	int col=0, col2=1, countA=0, countB=0;

	for(int q=0;q<4;q++){
		//fprintf(stderr,"column %d \n",c);
		if(board_spots[q][col]=='A'){
			countA++;
		}
		else if(board_spots[q][col]=='B'){
			countB++;
		}
		col++;
		col2++;
	}

	if(countA==4){
		fb->bitmap->pixel[0][scoreA]=BLUE;
		scoreA++;
		shake();
		return;
	}
	else if(countB==4){
		fb->bitmap->pixel[1][scoreB]=RED;
		scoreB++;
		shake();
		return;
	}


	//second first diagonal
	col2=1, countA=0, countB=0;

	for(int q=0;q<4;q++){
		//fprintf(stderr,"column %d \n",c);
		if(board_spots[q][col2]=='A'){
			countA++;
		}
		else if(board_spots[q][col2]=='B'){
			countB++;
		}
		col++;
		col2++;
	}

	if(countA==4){
		fb->bitmap->pixel[0][scoreA]=BLUE;
		scoreA++;
		shake();
		return;
	}
	else if(countB==4){
		fb->bitmap->pixel[1][scoreB]=RED;
		scoreB++;
		shake();
		return;
	}





	
	//other upward diagonal
	col=0, col2=1, countA=0, countB=0;
	countA=0;
	countB=0;
	for(int q=3;q>=0;q--){
		if(board_spots[q][col]=='A'){
			countA++;
		}
		else if(board_spots[q][col]=='B'){
			countB++;
		}
		col++;
		col2++;
	}

	if(countA==4){
		fb->bitmap->pixel[0][scoreA]=BLUE;
		scoreA++;
		shake();
		return;
	}
	else if(countB==4){
		fb->bitmap->pixel[1][scoreB]=RED;
		scoreB++;
		shake();
		return;
	}



	
	//second other upward diagonal
	col2=1, countA=0, countB=0;
	for(int q=3;q>=0;q--){
		if(board_spots[q][col2]=='A'){
			countA++;
		}
		else if(board_spots[q][col2]=='B'){
			countB++;
		}
		col2++;
	}


	
	if(countA==4){
		fb->bitmap->pixel[0][scoreA]=BLUE;
		scoreA++;
		shake();
		return;
	}
	else if(countB==4){
		fb->bitmap->pixel[1][scoreB]=RED;
		scoreB++;
		shake();
		return;
	}
}


bool check(int i, int x){
	fprintf(stderr, "checking if available\n");
	int rx = x-2;
	if(board_spots[i][rx]=='A' ||board_spots[i][rx]=='B'){
		return true;
	}else{
		return false;
	}
}

//adds the letter to the matrix and counts total_chips
void append(int i, int x, char letter){
	fprintf(stderr, "appending\n");
	int rx = x-2;
	fprintf(stderr, "i %d rx %d \n", i, rx);
	board_spots[i][rx] = letter;
	total_chips++;
}

void board(void){
	for(int i=3;i<7;i++){
		fb->bitmap->pixel[i][7]=WHITE;
		fb->bitmap->pixel[i][1]=WHITE;

	}
	for(int i=1;i<=7;i++){
		fb->bitmap->pixel[7][i]=WHITE;
	}
}

void place(char letter, int x){
	fprintf(stderr, "checking to place\n");
	int y = 6;
	for(int i=0;i<4;i++){
		if(check(i,x)){
			y--;
			continue;
		}
		else{
			append(i,x, letter);
			if(letter=='A'){
				fb->bitmap->pixel[y][x]=BLUE;
			}
			else{
				fb->bitmap->pixel[y][x]=RED;
			}
			check_connect(i,x,letter);

			//if board is full -> reset board
			if(total_chips==20){
				shake();
			}
			fprintf(stderr, "%d %d\n", y, x);
			break;
		}
	}

}

void displayDot(char letter, int x, int y){
	if(fb==NULL){
		fprintf(stderr, "Tried to draw(%d,%d) to a non-existent frame buffer!\n",x,y);
		return;
	}

	fb->bitmap->pixel[b][a]=BLACK;
	if(letter=='A'){
		fb->bitmap->pixel[y][x]=BLUE;
	}
	else{
		fb->bitmap->pixel[y][x]=RED;
	}
	a=x;
	b=y;
}


void clearDisplay(void){
	clearFrameBuffer(fb,BLACK);
}

//set to 3 so once the third score is made
//shake the pi and then it will display the winner
bool check_score(void){
	if(scoreA==3 || scoreB==3){
		return true;
	}
	else{
		return false;
	}
}
