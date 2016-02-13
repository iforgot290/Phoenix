/*
 * shooter.c
 *
 *  Created on: Feb 2, 2016
 *      Author: Neil
 *
 *  Right draw is always positive
 *  Left draw is always negative
 *
 *  Left arm draws back and right arm drops at -500
 *
 */

#include "main.h"

bool leftlocked = true;
bool rightlocked = false;

int lockmotor = 10;

int leftdraw = -400; // distance to wind up left shooter
int leftdrop = 400; //minimum value that left arm drops at
int leftwind = -127; //motor speed to tighten left shooter
int lefthold = -40; //value to hold motors

int rightdraw = 400; //distance to wind up right shooter
int rightdrop = -450; //minimum value that right arm drops at

extern int shootgo;

extern void lockLeft();
extern void lockRight();

void shootLeft();
void shootRight();

void wind();

extern Encoder encode;

extern void calibrate();

void shootLoop(){

	while (shootgo){ //Repeatedly shoots left and right

		shootLeft();
		shootRight();

	}
}

void shootLeft(){
	while (true){

		int encval = encoderGet(encode);

		//not ready to shoot left
		if (encval > leftdraw){
			wind(leftwind);
		}

		//ready to shoot left
		else {
			wind(lefthold);
			lockRight();
			wind(0);
			break;
		}

		//break if stop button is pushed
		if (joystickGetDigital(1, 8, JOY_DOWN)){
			motorStopAll();
			shootgo = 0;
			break;
		}

		calibrate();
		delay(25);
	}
}

void shootRight(){

	while (true){

		int encval = encoderGet(encode);

		//not ready to shoot right
		if (encval < rightdraw){
			wind(-leftwind);
		}

		//ready to shoot right
		else if (encval > rightdraw){
			wind(-lefthold);
			lockLeft();
			wind(0);
			break;
		}

		//break if stop button is pushed
		if (joystickGetDigital(1, 8, JOY_DOWN)){
			motorStopAll();
			shootgo = 0;
			break;
		}

		calibrate();
		delay(25);
	}
}

//motors 2 and 3 are inverse
//motors 8 and 9 are normal

void wind(int speed){
	motorSet(2, -speed);
	motorSet(3, -speed);
	motorSet(4, -speed);
	motorSet(7, speed);
	motorSet(8, speed);
	motorSet(9, speed);
}

