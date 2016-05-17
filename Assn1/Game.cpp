#include "Game.h"
#include "Car.h"
#include "Tree.h"
#include <stdlib.h>
#include <time.h>
#include "AssetManager.h"

extern AssetManager* assetManager;

Game::Game()
{
	srand((unsigned int)time(NULL));
	/* Game Initiallization */
	//scene setup
	scene = new GScene();
	
	//Sky box setup
	box = new SkyBox(
		"mp_blood/blood_ft.png",
		"mp_blood/blood_bk.png",
		"mp_blood/blood_lf.png",
		"mp_blood/blood_rt.png",
		"mp_blood/blood_up.png",
		"mp_blood/blood_dn.png"
	);
	scene->addObject(box);

	//GameMap
	map = new GameMap(GameMap::MODE_ROAD);
	scene->addObject(map);

	//Player
	player = new Player();
	map->addObject(player);

	//Trees - randomly  place 0~2 trees in grass
	//the start and the goal should be treeless
	for (int i = 1; i < (map->getLineLen())-1; i++) {
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
					map->addObject(tree);
				}
				pos >>= 1; //right shift once
				position++;
			}
		}
	}
	//Cars are placed with timer events.

	//place chiken
	GModel* model_chicken = assetManager->getModel("Mesh0");
	chicken = new O3DModel(
		vec3(-200, 0, 0), O3DModel::CENTER,
		0, 0, "CHICKEN",
		model_chicken);
	scene->addObject(chicken);
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
O3DModel* Game::getChicken() {
	return chicken;
}
void Game::newPlayer() {
	Player* old = player;
	player = new Player();
	getMap()->addObject(player);
	getMap()->removeObject(old);
}
Game::~Game() {
	delete chicken;
	delete scene;
}
