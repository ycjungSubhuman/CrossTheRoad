#pragma once
#include "GObject.h"
#include <vector>

class GameMap : public GObject {
private:
	/*mapinfo stored information about columns of background tiles.
	for example, 
		[GRASS, ROAD, ROAD, ROAD, GRASS, ROAD, ROAD, ROAD, ROAD]  */
public:
	enum { MAPLENGTH=20, COLUMN_WIDTH=20, MAPHEIGHT=80 };
	enum Linetype { GRASS, ROADUP, ROADDOWN };
	GameMap(int z=-1);
	virtual void frameAction();
	virtual void draw();
	Linetype getLine(int i);
private:
	std::vector<Linetype> mapinfo;
};
