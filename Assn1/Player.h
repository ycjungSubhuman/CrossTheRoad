#pragma once
#include "GObject.h"

class Player : public GObject {
private:
	int linenum;
public:
	enum Status { ALIVE, DEAD };
	enum { PLAYERWIDTH=10, PLAYERHEIGHT=10 };
	Player();
	virtual void draw();
	virtual void frameAction();
	Status getPlayerStatus();
	int getLinenum();
	int incrLInenum(int num=1);
private:
	Status status;

};
