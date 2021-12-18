#include "project.h"

pi_joystick_t* joystick;


void openJoystick(void){
	joystick = getJoystickDevice();
}

void closeJoystick(void){
	if(joystick!=NULL){
		freeJoystick(joystick);
	}
}

void checkJoystick(void(*callback)(unsigned int code), int delay){
	pollJoystick(joystick,callback,delay);
}


int run=1;

void done(void){
	run =0;
}
/*
void interrupt_handler(int sig){
	fprintf(stderr, "end shake loop");
	run=0;
}*/

void shake(void){
	float threshold=1.5;
	pi_i2c_t* device;
	coordinate_t data;
	//signal(SIGINT, interrupt_handler);
	device=geti2cDevice();
	if(device){
		configureAccelGyro(device);

		float x=0,y=0,z=0;
		float maxx=0,maxy=0,maxz=0;
		//run && getAccelData(device,&data)
		while (run && getAccelData(device,&data)){
			float dx=data.x-x,dy=data.y-y,dz=data.z-z;
			if(dx>maxx) maxx=dx;
			if(dy>maxy) maxy=dy;
			if(dz>maxz) maxz=dz;

			if(dx*dz+dy*dy+dz*dz > threshold){
				printf("erased bumped: %f %f %f\n",dx,dy,dz);
				clear_board();
				done();
				//interrupt_handler(4);
				//freei2cDevice(device);
				
			}
			x=data.x; y=data.y; z=data.z;
		}
		run =1;
		//freei2cDevice(device);
	}

}
