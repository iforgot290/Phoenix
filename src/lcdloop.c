#include "main.h"
#include "string.h"
#include "robotstate.h"

enum linkstate current = offline;
float lasttime = 0;
char state[13];

float lastannounce = 0;
char announce[16];

extern enum state bot;

void display(char*);

void startTask(){
	while (1==1){
		char buf[15];

		if (isAutonomous()){
			if (current != auton){
				lasttime = millis();
				current = auton;
				float seconds = ((float)millis() - lasttime) / 1000;
				sprintf(buf, "Auton: %.2f", seconds);
			}

			float seconds = ((float)millis() - lasttime) / 1000;
			sprintf(buf, "Auton: %.2f", seconds);
		}

		else if (!isEnabled()){
			if (current != disabled){
				lasttime = millis();
				current = disabled;
				float seconds = ((float)millis() - lasttime) / 1000;
				sprintf(buf, "Disabled: %.2f", seconds);
			}

			float seconds = ((float)millis() - lasttime) / 1000;
			sprintf(buf, "Disabled: %.2f", seconds);
		}

		else {
			if (current != driver){
				lasttime = millis();
				current = driver;
				float seconds = ((float)millis() - lasttime) / 1000;
				sprintf(buf, "Driver: %.2f", seconds);
			}

			float seconds = ((float)millis() - lasttime) / 1000;
			sprintf(buf, "Driver: %.2f", seconds);
		}

		display(buf);

		delay(50);
	}
}

void display(char* disp){
	if (current == driver){
		if (announce != NULL && millis() - lasttime <= 5000){
			lcdSetText(uart1, 1, announce);
		}

		if (bot == calib){
			lcdSetText(uart1, 1, "Calibrate");
		}

		else {
			lcdSetText(uart1, 1, "Driver");
		}
	}

	else {
		lcdSetText(uart1, 1, disp);
	}
}

void showAnnounce(char* disp){
	lasttime = millis();
}
