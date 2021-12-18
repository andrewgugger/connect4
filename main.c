#include "project.h"

void handler(unsigned int code);
int xPos=2, yPos=2;
int speed = 1000;
int running=1;

char letter = 'A';

int main(void){
	openDisplay();
	clearDisplay();
	openJoystick();
	board();
	//displayDot('C', 2,2);
	int lastX = -5, lastY=-5;
	printf("completed openign functions");
	while(running==1){
		//right
		//fprintf(stderr,"started loop");
		checkJoystick(handler,speed);
		if(lastX!=xPos || lastY!=yPos){
			lastX = xPos;
			lastY=yPos;
			//displayLetter(letter,xPos, yPos);
			displayDot(letter, xPos, yPos);
		}
	}
	clearDisplay();
	displayWinner();
	closeJoystick();
	closeDisplay();
}


void handler(unsigned int code){
    if(code ==KEY_RIGHT){
		fprintf(stderr,"right");
		if(xPos==6){
			xPos=2;
		}
		else{
			xPos++;
		}

    }

    else if(code ==KEY_LEFT){
		fprintf(stderr,"left");
		if(xPos==2){
			xPos=6;
		}
		else{
			xPos--;
		}

    }

    else if(code ==KEY_ENTER){
    	if(letter=='A'){
    		place('A',xPos);
			letter = 'B';
			displayDot(letter, xPos, yPos);
    	}
    	else if(letter=='B'){
    		place('B',xPos);
    		letter = 'A';
    		displayDot(letter, xPos, yPos);
    	}

    	if(check_score()){
    		running=0;
    	}
    }
}
