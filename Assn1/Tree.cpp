#include "Tree.h"
#include "GameMap.h"
#include "AssetManager.h"
#include "O3DModel.h"

extern AssetManager* assetManager;

Tree::Tree(int linenum, int gridnum)
	:O3DModel(assetManager->getGlobalPos("christmas_tree")+vec3(linenum*GameMap::COLUMN_WIDTH+(double)GameMap::COLUMN_WIDTH/2, 
		-((gridnum)*GRIDHEIGHT-(double)GRIDHEIGHT/2+(double)TREEHEIGHT/2), 
			0), CENTER, 0, 0, "TREE", assetManager->getModel("christmas_tree"))
{
	setColor(182, 52, 0);
	setHitBox(Rect(-TREEWIDTH/2, TREEHEIGHT, TREEWIDTH, TREEHEIGHT));
}
void Tree::frameAction() {
	/* do things like color changing */
}