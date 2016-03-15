#pragma once
#include "GObject.h"

class Background : public GObject {
private:
	enum { MAPLENGTH=20 };
	enum Linetype { GRASS, ROAD };
	/*mapinfo stored information about columns of background tiles.
	for example, 
		[GRASS, ROAD, ROAD, ROAD, GRASS, ROAD, ROAD, ROAD, ROAD]  */
	Linetype mapinfo[MAPLENGTH];
public:
	Background(const Rect& obj, const Rect& hitbox, int z, std::string type = "BACKGROUND");

};
