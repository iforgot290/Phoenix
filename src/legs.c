#include "main.h"

int left_front_leg = 4;
int left_rear_leg = 5;
int right_front_leg = 6;
int right_rear_leg = 7;

int oneleg_auto = 0;
int otherleg_auto = 0;
int oneleg_hold = 0;
int otherleg_hold = 0;

int hold_speed = 40;
int lift_speed = 127;

void stopLift();

void handleLegs(){

	int old = otherleg_hold;

	//switch the holding state
	while(joystickGetDigital(2, 7, JOY_UP)){
		if (old){
			otherleg_hold = 0;
			oneleg_hold = 0;
		} else {
			otherleg_hold = 1;
			oneleg_hold = 1;
		}
		delay(25);
	}

	old = oneleg_auto;

	//switch the one leg auto state
	while(joystickGetDigital(2, 7, JOY_LEFT)){
		if (old){ //stops the leg and hold
			oneleg_auto = 0;
			oneleg_hold = 0;
		} else {
			oneleg_auto = 1;
		}
	}

	old = otherleg_auto;

	//switch the other legs auto state
	while(joystickGetDigital(2, 7, JOY_RIGHT)){
		if (old){ //stops the legs and holds
			otherleg_auto = 0;
			otherleg_hold = 0;
		} else {
			otherleg_auto = 1;
		}
	}

	int left_front_leg_speed = joystickGetAnalog(2, ACCEL_X);
	int left_rear_leg_speed = joystickGetAnalog(2, ACCEL_X);
	int right_front_leg_speed = joystickGetAnalog(1, ACCEL_X);
	int right_rear_leg_speed = joystickGetAnalog(1, ACCEL_X);

	//Checks if when nothing is happening the legs should be held
	if (oneleg_hold){
		//If the joystick wants the motors to go faster than the hold speed, let them
		if (left_front_leg_speed > hold_speed){
			motorSet(left_front_leg, left_front_leg_speed);
		} else {
			motorSet(left_front_leg, hold_speed); //Hold the motors
		}
	} else {
		if (oneleg_auto){
			motorSet(left_front_leg, lift_speed); //Auto leg retract
		} else {
			motorSet(left_front_leg, left_front_leg_speed); //Move legs but without the holding
		}
	}

	//Same as the one leg except for the other 3
	if (otherleg_hold){
		if (left_rear_leg_speed > hold_speed){
			motorSet(left_rear_leg, left_rear_leg_speed);
		} else {
			motorSet(left_rear_leg, hold_speed);
		}

		if (right_front_leg_speed > hold_speed){
			motorSet(right_front_leg, right_front_leg_speed);
		} else {
			motorSet(right_front_leg, hold_speed);
		}

		if (right_rear_leg_speed > hold_speed){
			motorSet(right_rear_leg, right_rear_leg_speed);
		} else {
			motorSet(right_rear_leg, hold_speed);
		}
	} else {
		if (otherleg_auto){
			motorSet(left_rear_leg, lift_speed);
			motorSet(right_front_leg, lift_speed);
			motorSet(right_rear_leg, lift_speed);
		} else {
			motorSet(left_rear_leg, left_rear_leg_speed);
			motorSet(right_front_leg, right_front_leg_speed);
			motorSet(right_rear_leg, right_rear_leg_speed);
		}
	}

}

//Stop all lift motors
void stopLift(){
	motorSet(left_front_leg, 0);
	motorSet(left_rear_leg, 0);
	motorSet(right_front_leg, 0);
	motorSet(right_rear_leg, 0);
}
