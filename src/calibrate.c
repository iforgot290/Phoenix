#include "main.h"

extern int leftdraw;
extern int rightdraw;

void calibrate(){

	/*if (joystickGetDigital(1, 7, JOY_DOWN)){
		wind(127);
	} else if (joystickGetDigital(1, 7, JOY_UP)){
		wind(-127);
	} else {
		wind(0);
	}*/

	int oldval = leftdraw;

	//raise the left shooting value
	while (joystickGetDigital(1, 7, JOY_UP)){
		leftdraw = oldval - 5;
		delay(25);
	}

	//lower left shooting value
	while (joystickGetDigital(1, 7, JOY_DOWN)){
		leftdraw = oldval + 5;
		delay(25);
	}

	oldval = rightdraw;

	//raise right shooting value
	while (joystickGetDigital(1, 8, JOY_UP)){
		rightdraw = oldval + 5;
		delay(25);
	}

	//lower left shooting value
	while (joystickGetDigital(1, 8, JOY_DOWN)){
		rightdraw = oldval - 5;
		delay(25);
	}

	char buf[16];
	sprintf(buf, "R: %d L: %d", rightdraw, leftdraw);
	lcdSetText(uart1, 2, buf);


}
