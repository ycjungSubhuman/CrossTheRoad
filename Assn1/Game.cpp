#include "Game.h"
#include "Car.h"
#include "Tree.h"
#include <stdlib.h>

Game::Game()
{
	/* Game Initiallization */
	//scene setup
	scene = new GScene();

	//GameMap
	GameMap* map = new GameMap();
	scene->addObject(map);

	//Player
	player = new Player();
	scene->addObject(player);

	//Trees - randomly  place 0~2 trees in grass
	//the start and the goal should be treeless
	for (int i = 1; i < GameMap::MAPLENGTH-1; i++) {
		if (map->getLine(i) == GameMap::GRASS) { //if grass
			int pos_pool = GameMap::MAPHEIGHT / Tree::GRIDHEIGHT;

			int tree_cnt = 0;
			int pos = 0;
			//determin positions of trees using binary expression
			for (int j = 0; j < pos_pool; j++) {
				if (tree_cnt > 2) break;
				else {
					if (rand() % 2 == 0) {
						pos = pos | 0x01;
						tree_cnt++;
					}
					else {
						pos = pos | 0x00;
					}
					pos = pos << 1;
				}
			}
			//place trees
			int position = 0;
			for (int j = 0; j < pos_pool; j++) {
				if (0x01 & pos) { //only when LSB is 1
					Tree* tree = new Tree(i, position); //place tree
					scene->addObject(tree);
				}
				pos >>= 1; //right shift once
			}
		}
	}
	//Cars are placed with timer events.
}
GScene* Game::getScene() {
	return scene;
}
Player* Game::getPlayer() {
	return player;
}
Game::~Game() {
	delete scene;
}
