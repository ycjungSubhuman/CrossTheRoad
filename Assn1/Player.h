#pragma once
#include "GObject.h"
#include "GameMap.h"
#include "mat.h"
#include "O3DModel.h"

class Player : public GObject {
private:
	bool isBound;
	int linenum, gridnum;
	double rotdest;
	GObject* bound_object;
	//these pointes are referenced only from inside. a change in the 'status' can be
	//done to manipulate player limbs
	O3DModel *head, *hair, *arm_left, *arm_right, *eyes, *neck;
	ORect* wow;
	void incrRotDest(double rot);
public:
	Player();
	enum Status { ALIVE, WALKING, TURNING, DEAD };
	enum { PLAYERWIDTH=10, PLAYERHEIGHT=GameMap::MAPHEIGHT/GameMap::GRIDNUM };
	enum Direction { NONE, RIGHT, UP, DOWN, LEFT, TURN_LEFT, TURN_RIGHT };
	enum Key { KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_LEFT };
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
	void move(Key key);
	void undoMove();
	void finishMove();
	Direction getMoveDir();
	Status getPlayerStatus();
	void bindPlayerToCenter(GObject* obj);
	bool isPlayerBound();
	GObject* getBoundObject();
	int getLinenum();
	int getGridnum();
	int incrLinenum(int num=1);
	int incrGridnum(int num);
	void incrHead(bool incr);
	bool characterIsMovableTo(Direction dir);
	static Direction reverseOf(Direction dir);
private:
	Status status;
	Direction movedir;
	Direction headdir;
};
