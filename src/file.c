#include "main.h"

FILE *settings;
extern int rightdraw;
extern int leftdraw;

void loadValues(){

	char filecont[5];

	settings = fopen("r.txt", "r");

	if (settings == NULL){
		fclose(settings);
		settings = fopen("r.txt", "w");
		fputs("0900", settings);
		fclose(settings);
		settings = fopen("r.txt", "r");
	}

	fread(filecont, 1, 4, settings);
	filecont[4] = '\0';

	fclose(settings);

	rightdraw = atoi(filecont);

	settings = fopen("l.txt", "r");

	if (settings == NULL){
		fclose(settings);
		settings = fopen("l.txt", "w");
		fputs("0900", settings);
		fclose(settings);
		settings = fopen("l.txt", "r");
	}

	fread(filecont, 1, 4, settings);
	filecont[4] = '\0';

	fclose(settings);

	leftdraw = -atoi(filecont);

}

void saveValues(){

}
