#include "Game.h"
#include "Car.h"
#include "Tree.h"
#include <stdlib.h>
#include <time.h>

Game::Game()
{
	srand((unsigned int)time(NULL));
	/* Game Initiallization */
	//scene setup
	scene = new GScene();

	//GameMap
	map = new GameMap();
	scene->addObject(map);

	//Player
	player = new Player();
	map->addObject(player, 2);

	//Trees - randomly  place 0~2 trees in grass
	//the start and the goal should be treeless
	for (int i = 1; i < GameMap::MAPLENGTH-1; i++) {
		if (map->getLine(i) == GameMap::GRASS) { //if grass
			int tree_cnt = 0;
			int pos = 0;
			//determin positions of trees using binary expression
			for (int j = 0; j < GameMap::GRIDNUM; j++) {
				if (tree_cnt > 2) break;
				else {
					if (rand() % 3==0) {
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
			for (int j = 0; j < GameMap::GRIDNUM; j++) {
				if (0x01 & pos) { //only when LSB is 1
					Tree* tree = new Tree(i, position); //place tree
					map->addObject(tree, 3);
				}
				pos >>= 1; //right shift once
				position++;
			}
		}
	}
	//Cars are placed with timer events.
}
GameMap* Game::getMap() {
	return map;
}
GScene* Game::getScene() {
	return scene;
}
Player* Game::getPlayer() {
	return player;
}
void Game::newPlayer() {
	getScene()->removeObject(player);
	player = new Player();
	getScene()->addObject(player);
}
Game::~Game() {
	delete scene;
}
