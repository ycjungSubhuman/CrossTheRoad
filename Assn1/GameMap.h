#pragma once
#include "GObject.h"

class GameMap : public GObject {
private:
	/*mapinfo stored information about columns of background tiles.
	for example, 
		[GRASS, ROAD, ROAD, ROAD, GRASS, ROAD, ROAD, ROAD, ROAD]  */
public:
	enum { MAPLENGTH=20, COLUMN_WIDTH=20, MAPHEIGHT=50 };
	enum Linetype { GRASS, ROADUP, ROADDOWN };
	GameMap(int z=-1);
	virtual void frameAction();
private:
	Linetype mapinfo[MAPLENGTH];

};
