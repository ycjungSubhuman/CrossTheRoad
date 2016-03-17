#include "Tree.h"
#include "GameMap.h"

Tree::Tree(int linenum, int position) : GObject(Rect(linenum*GameMap::COLUMN_WIDTH+GameMap::COLUMN_WIDTH/2-TREEWIDTH/2, position*GRIDHEIGHT+GRIDHEIGHT/2-TREEHEIGHT/2,TREEWIDTH,TREEHEIGHT),Rect(0,0,TREEWIDTH, TREEHEIGHT), 1, "TREE")
{
	//set drawfunc
	setFunc([this](const Rect& rect, int r, int g, int b)->void {
		/* drawfunc for tree */
	});
}
void Tree::frameAction() {
	/* do things like color changing */
}