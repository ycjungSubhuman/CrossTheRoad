#include "Background.h"

Background::Background(const Rect& obj, const Rect& hitbox, int z, std::string type = "BACKGROUND") : GObject(obj, hitbox, []() {}, z, type)
{
	//init mapinfo
	mapinfo[0] = GRASS;
	mapinfo[MAPLENGTH - 1] = GRASS;
	for (int i = 1; i < MAPLENGTH-1; i++) {
		
	}

	//sets drawfunc
	std::function<void(const Rect& rect)> drawFunc = [](const Rect& rect) {

	};
	this->setFunc(drawFunc);
}

