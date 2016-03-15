#include "Background.h"
#include <stdlib.h>

Background::Background(const Rect& obj, const Rect& hitbox, int z, std::string type) : GObject(obj, hitbox, z, type)
{
	//init mapinfo
	mapinfo[0] = GRASS;
	mapinfo[1] = ROAD;
	mapinfo[MAPLENGTH - 2] = ROAD;
	mapinfo[MAPLENGTH - 1] = GRASS; //the first and the last should be GRASS
	int prevroad = 0;
	for (int i = 2; i < MAPLENGTH-2; i++) {
		if (prevroad < 3)
			mapinfo[i] = ROAD;
		else
			mapinfo[i] = (rand() % 2 == 0) ? ROAD : GRASS;
	}
	//sets drawfunc
	std::function<void(const Rect& rect, int, int, int)> drawFunc = [](const Rect& rect, int r, int g, int b) {

	};

	setFunc(drawFunc);
}

