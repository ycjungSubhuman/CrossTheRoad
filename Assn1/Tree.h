#pragma once
#include "GObject.h"

class Tree : public GObject {
public:
	enum { TREEWIDTH=10, TREEHEIGHT=10, GRIDHEIGHT=10 };
	Tree(int linenum, int position); //vertical position for the tree, one of 0, 1, 2, 3, 4
	virtual void frameAction();
};