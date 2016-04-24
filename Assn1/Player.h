#pragma once
#include "GObject.h"
#include "GameMap.h"
#include "mat.h"
#include "ORect.h"

class Player : public GObject {
private:
	int linenum, gridnum;
	GObject* bound_object;
	//these pointes are referenced only from inside. a change in the 'status' can be
	//done to manipulate player limbs
public:
	Player();
	enum Status { ALIVE, WALKING, BOUND, DEAD };
	enum { PLAYERWIDTH=10, PLAYERHEIGHT=GameMap::MAPHEIGHT/GameMap::GRIDNUM };
	enum Direction { NONE, RIGHT, UP, DOWN, LEFT };
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
	void move(Direction dir);
	void undoMove();
	void finishMove();
	Direction getMoveDir();
	Status getPlayerStatus();
	void bindPlayerToCenter(GObject* obj);
	GObject* getBoundObject();
	int getLinenum();
	int getGridnum();
	int incrLinenum(int num=1);
	int incrGridnum(int num);
private:
	Status status;
	Direction movedir;
};
