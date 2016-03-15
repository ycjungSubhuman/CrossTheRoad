#pragma once
#include "GObject.h"

class Background : public GObject {
private:
	enum { MAPLENGTH=20, COLUMN_WIDTH=20, MAPHEIGHT=40 };
	/*mapinfo stored information about columns of background tiles.
	for example, 
		[GRASS, ROAD, ROAD, ROAD, GRASS, ROAD, ROAD, ROAD, ROAD]  */
public:
	enum Linetype { GRASS, ROADUP, ROADDOWN };
	Background(int z=-1);
private:
	Linetype mapinfo[MAPLENGTH];

};
