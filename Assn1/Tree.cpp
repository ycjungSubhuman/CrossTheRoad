#include "Tree.h"
#include "GameMap.h"

Tree::Tree(int linenum, int gridnum)
	:ORect(linenum*GameMap::COLUMN_WIDTH+(double)GameMap::COLUMN_WIDTH/2-(double)TREEWIDTH/2, (gridnum+1)*GRIDHEIGHT-((double)GRIDHEIGHT/2+(double)TREEHEIGHT/2), TREEWIDTH, TREEHEIGHT, ORect::CENTER, 0, "TREE")
{
}
void Tree::frameAction() {
	/* do things like color changing */
}