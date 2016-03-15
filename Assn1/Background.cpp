#include "Background.h"
#include <stdlib.h>

Background::Background(int z) : GObject(Rect(0, 0, COLUMN_WIDTH*MAPLENGTH, MAPHEIGHT), Rect(0,0,0,0), z, "BACKGROUND")
{
	//init mapinfo
	mapinfo[0] = GRASS;
	mapinfo[1] = rand()%2 ? ROADUP : ROADDOWN;
	mapinfo[MAPLENGTH - 2] = rand()%2 ? ROADUP : ROADDOWN;
	mapinfo[MAPLENGTH - 1] = GRASS; //the first and the last should be GRASS
	int prevroad = 0;
	for (int i = 2; i < MAPLENGTH-2; i++) {
		if (prevroad < 3)
			mapinfo[i] = rand() % 2 ? ROADUP : ROADDOWN;
		else {
			switch (rand() % 3) {
				case 0: mapinfo[i] = ROADUP;
				case 1: mapinfo[i] = ROADDOWN;
				case 2: mapinfo[i] = GRASS;
			}
			if(mapinfo[i]==GRASS) prevroad = 0;
		}
	}
	//sets drawfunc
	std::function<void(const Rect& rect, int, int, int)> drawFunc = [](const Rect& rect, int r, int g, int b) {

	};
	setFunc(drawFunc);
}
