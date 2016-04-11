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
	ORect *pelvis, *neck, *head;
	ORect *leg_left_upper, *leg_left_lower, *leg_right_upper, *leg_right_lower;
	ORect *foot_left, *foot_right;
	ORect *torso;
	ORect *arm_left_upper, *arm_left_lower, *arm_right_upper, *arm_right_lower;
	ORect *hand_left, *hand_right;
public:
	Player();
	enum Status { ALIVE, WALKING, BOUND, DEAD };
	enum { PLAYERWIDTH=10, PLAYERHEIGHT=GameMap::MAPHEIGHT/GameMap::GRIDNUM };
	enum {
		PELVISWIDTH = 1,
		PELVISHEIGHT = 1,
		FOOTWIDTH = 2,
		FOOTHEIGHT = 1,
		NECKWIDTH = 1,
		NECKHEIGHT = 1,
		HEADWIDTH = 1,
		HEADHEIGHT = 2,
		LEGWIDTH = 1,
		LEGHEIGHT = 2,
		ARMHEIGHT = 2,
		ARMWIDTH = 1,
		TORSOHEIGHT = 3,
		TORSOWIDTH = 1,
		HANDWIDTH = 1,
		HANDHEIGHT = 1,
	};
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
	int incrLInenum(int num=1);
	int incrGridnum(int num);
private:
	Status status;
	Direction movedir;
};
