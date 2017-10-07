#include "Fishing2.h"

int main (void)
{
	int level = 0;
	system("COLOR 3F");

	//printTitle();

	mainMenu(); //May need to be changed
	level = loadProgress();
	switch (level)
	{
		case 0:
		runIntro();
		saveProgress(1);
		CLEAR
		case 1:
		levelOne();
		saveProgress(2);
		case 2:
		runIntermission();
		levelTwo();
		saveProgress(3);
		case 3:
		runIntermission2();
		levelThree();
		credits();
		saveProgress(0);
	}
}