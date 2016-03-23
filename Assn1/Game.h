#pragma once
#include "GScene.h"
#include "Player.h"
#include "GameMap.h"

class Game {
private:
	GScene* scene;
	GameMap* map;
	Player* player;
public:
	Game();
	GScene* getScene();
	Player* getPlayer();
	~Game();
};