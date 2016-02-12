#include "main.h"
#include "string.h"
#include "robotstate.h"

enum linkstate current = offline;
float lasttime = 0;
char state[13];

float lastannounce = 0;
char announce[16];

void display(char*);
extern void saveValues();

extern Encoder encode;
extern void shootLeft();
extern void shootRight();

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
		if (announce != NULL && millis() - lastannounce <= 3000){
			lcdSetText(uart1, 1, announce);
		}

		else {
			char buf[16];
			sprintf(buf, "Encoder: %d", encoderGet(encode));
			lcdSetText(uart1, 1, buf);
		}
	}

	else {
		lcdSetText(uart1, 1, disp);
	}
}

void showAnnounce(char* disp){
	lastannounce = millis();
	strncpy(announce, disp, 16);
}

void handleLcdButtons(){

	int but = lcdReadButtons(uart1);

	int shouldsave = 0;

	while (but == 1){
		shouldsave = 1;
		but = lcdReadButtons(uart1);
		delay(25);
	}

	if (shouldsave == 1){ //save values
		saveValues();
		showAnnounce("Saved");
	}

	else if (but == 2){
		showAnnounce("Shooting Right");
		shootLeft();
	}

	else if (but == 3){
		showAnnounce("Shooting Left");
		shootRight();
	}

}
