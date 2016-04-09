#pragma once
#include "GObject.h"
#include "GameMap.h"
#include "mat.h"
#include "OEllipse.h"
#include "ORect.h"

class Player : public GObject {
private:
	int linenum, gridnum;
	//these pointes are referenced only from inside. a change in the 'status' can be
	//done to manipulate player limbs
	OEllipse *pelvis, *neck, *head;
	ORect *leg_left_upper, *leg_left_lower, *leg_right_upper, *leg_right_lower;
	ORect *foot_left, *foot_right;
	ORect *torso;
	ORect *arm_left_upper, *arm_left_lower, *arm_right_upper, *arm_right_lower;
	ORect *hand_left, *hand_right;
public:
	Player(int z=1);
	enum Status { ALIVE, WALKING, DEAD };
	enum { PLAYERWIDTH=10, PLAYERHEIGHT=GameMap::MAPHEIGHT/GameMap::GRIDNUM };
	enum {
		PELVISRADIUS = 3,
		FOOTWIDTH = 3,
		FOOTHEIGHT = 2,
		NECKRADIUS = 1,
		HEADMAJOR = 2,
		HEADMINOR = 4,
		LEGWIDTH = 7,
		LEGHEIGHT = 2,
		ARMHEIGHT = 5,
		ARMWIDTH = 2,
		TORSOHEIGHT = 8,
		TORSOWIDTH = 3,
		HANDWIDTH = 1,
		HANDHEIGHT = 3,
	};
	enum Direction { NONE, RIGHT, UP, DOWN, LEFT };
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
	void move(Direction dir);
	void undoMove();
	Direction getMoveDir();
	Status getPlayerStatus();
	int getLinenum();
	int getGridnum();
	int incrLInenum(int num=1);
	int incrGridnum(int num);
private:
	Status status;
	Direction movedir;

};
