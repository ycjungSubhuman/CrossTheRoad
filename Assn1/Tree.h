#pragma once
#include "ORect.h"
#include "GameMap.h"
#include "mat.h"

class Tree : public ORect {
public:
	enum { TREEWIDTH=8, TREEHEIGHT=8, GRIDHEIGHT=GameMap::MAPHEIGHT/GameMap::GRIDNUM };//GRID -- bottom: 0, top: GRIDNUM
	Tree(int linenum, int gridnum); //vertical position for the tree
	virtual void frameAction();
};