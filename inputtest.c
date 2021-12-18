#include "project.h"


void openJoystick(void);
void closeJoystick(void);
void checkJoystick(void(*callback)(unsigned int code), int delay);
void shake(void);
void done(void);
void handler(unsigned int code);

int main(void){
	openJoystick();
	//checkJoystick(void(*callback)(unsigned int code), 1000);
	shake();

	closeJoystick();
	return 1;
}
