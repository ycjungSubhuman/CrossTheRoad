#pragma once
#include "GObject.h"
#include "mat.h"
#include "ORect.h"
#include <vector>

class GameMap : public GObject {
private:
	/*mapinfo stored information about columns of background tiles.
	for example, 
		[GRASS, ROAD, ROAD, ROAD, GRASS, ROAD, ROAD, ROAD, ROAD]  */
public:
	enum { MAPLENGTH=20, COLUMN_WIDTH=20, MAPHEIGHT=180, GRIDNUM=9 };
	enum Linetype { GRASS, ROADUP, ROADDOWN, WATERUP, WATERDOWN };
	enum GameMode { MODE_ROAD=1, MODE_WATER=2 };
	GameMap(GameMode mode);
	virtual void frameAction();
	virtual void draw(mat4 MVMatrix);
	Linetype getLine(int i);
	int getLineLen();
private:
	std::vector<Linetype> mapinfo;
};
