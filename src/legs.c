#include "main.h"
#include "robotstate.h"

int left_front_leg = 4;
int left_rear_leg = 5;
int right_front_leg = 6;
int right_rear_leg = 7;

int left_front_leg_speed = -127;
int left_rear_leg_speed = 127;
int right_front_leg_speed = 127;
int right_rear_leg_speed = -127;

int lflhold = -20;
int lrlhold = 20;
int rflhold = 20;
int rrlhold = -20;

int oneleg_hold = 0;
int otherleg_hold = 0;

int drinv = 1;

extern enum state bot;

void stopLift();

void legs(){
	if (bot == lift){

		if (joystickGetDigital(2, 7, JOY_UP)){
			drinv = 1;
		}

		if (joystickGetDigital(2, 7, JOY_DOWN)){
			drinv = -1;
		}

		if (joystickGetDigital(2, 7, JOY_LEFT)){
			oneleg_hold = 1;
			otherleg_hold = 1;
		}

		if (joystickGetDigital(2, 7, JOY_RIGHT)){
			oneleg_hold = 0;
			otherleg_hold = 0;
		}

		int lflgo = joystickGetDigital(2, 5, JOY_UP);
		int lrlgo = joystickGetDigital(2, 5, JOY_DOWN);
		int rflgo = joystickGetDigital(2, 6, JOY_UP);
		int rrlgo = joystickGetDigital(2, 6, JOY_DOWN);

		if (oneleg_hold){
			if (lflgo){
				motorSet(left_front_leg, drinv * left_front_leg_speed);
			} else if (joystickGetDigital(2, 8, JOY_UP)){
				oneleg_hold = 0;
			} else {
				motorSet(left_front_leg, lflhold);
			}
		} else {
			if (joystickGetDigital(2, 8, JOY_UP)){
				motorSet(left_front_leg, -left_front_leg_speed);
			} else if (lflgo){
				motorSet(left_front_leg, drinv * left_front_leg_speed);
			} else {
				motorSet(left_front_leg, 0);
			}
		}

		if (lrlgo){
			motorSet(left_rear_leg, drinv * left_rear_leg_speed);
		} else {
			if (otherleg_hold){
				motorSet(left_rear_leg, lrlhold);
			} else {
				motorSet(left_rear_leg, 0);
			}
		}

		if (rflgo){
			motorSet(right_front_leg, drinv * right_front_leg_speed);
		} else {
			if (otherleg_hold){
				motorSet(right_front_leg, rflhold);
			} else {
				motorSet(right_front_leg, 0);
			}
		}

		if (rrlgo){
			motorSet(right_rear_leg, drinv * right_rear_leg_speed);
		} else if (joystickGetDigital(2, 8, JOY_RIGHT)){
			motorSet(right_rear_leg, -right_rear_leg_speed);
		} else {
			if (otherleg_hold){
				motorSet(right_rear_leg, rrlhold);
			} else {
				motorSet(right_rear_leg, 0);
			}
		}

	} else {
		stopLift();
	}
}

//Stop all lift motors
void stopLift(){
	motorSet(left_front_leg, 0);
	motorSet(left_rear_leg, 0);
	motorSet(right_front_leg, 0);
	motorSet(right_rear_leg, 0);
}
