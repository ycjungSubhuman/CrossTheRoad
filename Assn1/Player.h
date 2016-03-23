#pragma once
#include "GObject.h"

class Player : public GObject {
private:
	int linenum;
public:
	Player(int z=1);
	enum Status { ALIVE, DEAD };
	enum { PLAYERWIDTH=10, PLAYERHEIGHT=10 };
	enum Direction { RIGHT, UP, DOWN };
	virtual void draw();
	virtual void frameAction();
	int move(Direction dir);
	Status getPlayerStatus();
	int getLinenum();
	int incrLInenum(int num=1);
private:
	Status status;

};
