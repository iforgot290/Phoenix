#include "main.h"

void lockLeft(){

}

void lockRight(){

}

void handleLocks(){
	//Locking thinger
	if (joystickGetDigital(1, 5, JOY_UP) == true){
		motorSet(1, 127);
	} else if (joystickGetDigital(1, 5, JOY_DOWN) == true){
		motorSet(1, -127);
	} else {
		motorSet(1, 0);
	}

	//Other locking thinger
	if (joystickGetDigital(1, 6, JOY_UP) == true){
		motorSet(10, 127);
	} else if (joystickGetDigital(1, 6, JOY_DOWN) == true){
		motorSet(10, -127);
	} else {
		motorSet(10, 0);
	}
}
