#pragma once
#include "GObject.h"
#include "GameMap.h"

class Player : public GObject {
private:
	int linenum, gridnum;
public:
	Player(int z=1);
	enum Status { ALIVE, DEAD };
	enum { PLAYERWIDTH=10, PLAYERHEIGHT=GameMap::MAPHEIGHT/GameMap::GRIDNUM };
	enum Direction { RIGHT, UP, DOWN };
	virtual void draw();
	virtual void frameAction();
	void move(Direction dir);
	Direction getPrevDir();
	Status getPlayerStatus();
	int getLinenum();
	int getGridnum();
	int incrLInenum(int num=1);
	int incrGridnum(int num);
private:
	Status status;
	Direction prevdir;

};
