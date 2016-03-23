#include "Tree.h"
#include "GameMap.h"

Tree::Tree(int linenum, int gridnum) : GObject(Rect(linenum*GameMap::COLUMN_WIDTH+GameMap::COLUMN_WIDTH/2-TREEWIDTH/2, (gridnum+1)*(GRIDHEIGHT)-GRIDHEIGHT/2+TREEHEIGHT/2,TREEWIDTH,TREEHEIGHT),Rect(0,0,TREEWIDTH, TREEHEIGHT), 1, "TREE")
{
}
void Tree::draw() {
	glColor3f(150.0f / 256.0f, 75.0f / 256.0f, 0.0f);
	Rect treerect = getobj();
	glRectf(treerect.left(), treerect.bottom(), treerect.right(), treerect.top());
}
void Tree::frameAction() {
	/* do things like color changing */
}