#pragma once
#include "GObject.h"
#include "GameMap.h"

class Tree : public GObject {
public:
	enum { TREEWIDTH=8, TREEHEIGHT=8, GRIDHEIGHT=GameMap::MAPHEIGHT/GameMap::GRIDNUM };//GRID -- bottom: 0, top: GRIDNUM
	Tree(int linenum, int gridnum); //vertical position for the tree
	virtual void draw();
	virtual void frameAction();
};