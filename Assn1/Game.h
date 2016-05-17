#pragma once
#include "GScene.h"
#include "Player.h"
#include "GameMap.h"
#include "O3DModel.h"
#include "SkyBox.h"

class Game {
private:
	GScene* scene;
	SkyBox* box;
	GameMap* map;
	Player* player;
	O3DModel* chicken;
public:
	Game();
	GameMap* getMap();
	GScene* getScene();
	Player* getPlayer();
	O3DModel* getChicken();
	void newPlayer();
	~Game();
};