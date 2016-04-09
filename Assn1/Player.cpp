#include "Player.h"
#include "GameMap.h"
#include <list>
#include <iostream>

/* void drawcircle(double x, double y, double radius)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (double angle = 1.0f; angle<361.0f; angle += 0.2)
	{
		glVertex2f(x + sin(angle)*radius, y + cos(angle)*radius);
	}
	glEnd();
} */

Player::Player() 
	: GObject(Rect(GameMap::COLUMN_WIDTH/2 - PLAYERWIDTH/2, PLAYERHEIGHT*(GameMap::GRIDNUM/2+1), PLAYERWIDTH, PLAYERHEIGHT), Rect(PLAYERWIDTH*0.25, -PLAYERWIDTH*0.25, PLAYERWIDTH*0.5, PLAYERHEIGHT*0.5), "PLAYER")
{
	linenum = -1;
	gridnum = GameMap::GRIDNUM / 2;
	status = ALIVE;
	movedir = NONE;

	/* making doll */
	//x, y, a, b, rotcnt, rot
	//x, y, width, height, rotcnt, rot

	//because they are all children of this Player, delete will not be called in this
	//class' destructor. when delete for Player is called, the destructor of GObject will delete these limbs.
	pelvis = new ORect(0, 0, PELVISWIDTH, PELVISHEIGHT, 4, 0);
	leg_left_upper = new ORect((double)PELVISWIDTH/2-LEGWIDTH, -(double)PELVISHEIGHT/2, LEGWIDTH, LEGHEIGHT, 1, -0.2);
	leg_left_lower = new ORect(0, -LEGHEIGHT, LEGWIDTH, LEGHEIGHT, 1, 0);
	foot_left = new ORect(0, -LEGHEIGHT, FOOTWIDTH, FOOTHEIGHT, 0, 0);
	leg_right_upper = new ORect((double)PELVISWIDTH/2-LEGWIDTH, -(double)PELVISHEIGHT/2, LEGWIDTH, LEGHEIGHT, 1, 0.2);
	leg_right_lower = new ORect(0, -LEGHEIGHT, LEGWIDTH, LEGHEIGHT, 1, 0);
	foot_right = new ORect(0, -LEGHEIGHT, FOOTWIDTH, FOOTHEIGHT, 0, 0);
	torso = new ORect((double)PELVISWIDTH/2 - (double)TORSOWIDTH / 2, TORSOHEIGHT-(double)PELVISHEIGHT/2*0.3, TORSOWIDTH, TORSOHEIGHT, 7, 0);
	neck = new ORect((double)TORSOWIDTH / 2 - (double)NECKWIDHT/2, NECKHEIGHT*0.8, NECKWIDTH, NECKHEIGHT, 4, 0);
	head = new ORect((double)NECKWIDTH/2 - (double)HEADWIDTH/2, HEADHEIGHT, HEADWIDTH, HEADHEIGHT, 7, 0);
	arm_left_upper = new ORect((double)TORSOWIDTH/2-(double)ARMWIDTH/2, 0, ARMWIDTH, ARMHEIGHT, 1, 0.8);
	arm_left_lower = = new ORect(0, -ARMHEIGHT, ARMWIDTH, ARMHEIGHT, 1, 0.2);
	hand_left = new ORect(0, -ARMHEIGHT, HANDWIDTH, HANDHEIGHT, 0, 0.4);
	arm_right_upper = new ORect((double)TORSOWIDTH / 2 - (double)ARMWIDTH / 2, 0, ARMWIDTH, ARMHEIGHT, 1, -0.8);
	arm_right_lower = new ORect(0, -ARMHEIGHT, ARMWIDTH, ARMHEIGHT, 1, 0.2);
	hand_right = new ORect(0, -ARMHEIGHT, HANDWIDTH, HANDHEIGHT, 0, 0.2);

	//making graph
	pelvis->addObject(leg_left_upper, 0);
		leg_left_upper->addObject(leg_left_lower);
			leg_left_lower->addObject(foot_left);
	pelvis->addObject(leg_right_upper, -1);
		leg_right_upper->addObject(leg_right_lower);
			leg_right_lower->addObject(foot_right);
	pelvis->addObject(torso, 2);
		torso->addObject(neck, -3);
			neck->addObject(head);
		torso->addObject(arm_left_upper, -1);
			arm_left_upper->addObject(arm_left_lower);
				arm_left_lower->addObject(hand_left);
		torso->addObject(arm_right_upper, 1);
			arm_right_upper->addObject(arm_right_lower);
				arm_left_lower->addObject(hand_right);
}
void Player::move(Player::Direction dir) {
	switch (dir) {
	case RIGHT:
		if (linenum < GameMap::MAPLENGTH - 1) {
			if (movedir == LEFT) linenum--;
			movedir = RIGHT;
		}
		break;
	case UP:
		if (gridnum < GameMap::GRIDNUM - 1) {
			if (movedir == DOWN) gridnum--;
			movedir = UP;
		}
		break;
	case DOWN:
		if (gridnum > 0) {
			if (movedir == UP) gridnum++;
			movedir = DOWN;
		}
		break;
	case LEFT:
		if (linenum > 0) {
			if (movedir == RIGHT) linenum++;
			movedir = LEFT;
		}
		break;
	}
	//check for tree collisions
}
void Player::undoMove() {
	std::cout << "woiefjwoiejf" << std::endl;
	movedir = NONE;
	setPos((linenum + 1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2, (gridnum + 1)*GameMap::MAPHEIGHT / GameMap::GRIDNUM);
}
Player::Direction Player::getMoveDir() {
	return movedir;
}
Player::Status Player::getPlayerStatus() {
	return status;
}
void Player::draw() {
	/* draw player pelvis... or just draw nothing (if you have implemented 
	a pelvis node) */

	/* -------------------------------------------------- */
	/* Implement player drawing here...well, draw nothing */
	/* -------------------------------------------------- */

	/* glColor3f(1.0f, 0.0f, 0.0f);
	Rect playerobj = getobj();
	double playerX = (playerobj.left() + playerobj.right()) / 2;
	double playerY = (playerobj.top() + playerobj.bottom()) / 2;
	double radius = (playerobj.right() - playerobj.left()) / 2;
	switch (getPlayerStatus()) {
	case Player::ALIVE:
		drawcircle(playerX, playerY, radius);
		break;
	case Player::DEAD:
		break;
	} */
}
void Player::frameAction() {
	/*the controls will be processed in keyboard event callback.
	in this function. do things the player have to do frame by frame
	ex) flickering colors*/
	//moves player according to movedir
	std::cout << linenum << " " << gridnum << std::endl;
	switch (movedir) {
	case UP:
		if (getY() + 2 < (gridnum + 2)*GameMap::MAPHEIGHT / GameMap::GRIDNUM) {
			double next = (gridnum + 2)*GameMap::MAPHEIGHT / GameMap::GRIDNUM - getY();
			next = next*0.5;
			setPos(getX(), getY() + next);
			std::cout << "moving..." << std::endl;
		}
		else {
			setPos(getX(), (gridnum + 2)*GameMap::MAPHEIGHT / GameMap::GRIDNUM);
			movedir = NONE;
			gridnum++;
			std::cout << "moving...end" << std::endl;
		}
		break;
	case DOWN:
		if (getY() - 2 > (gridnum)*GameMap::MAPHEIGHT / GameMap::GRIDNUM) {
			double next = (gridnum)*GameMap::MAPHEIGHT / GameMap::GRIDNUM - getY();
			next = next*0.5;
			setPos(getX(), getY() + next);
			std::cout << "moving..." << std::endl;
		}
		else {
			setPos(getX(), (gridnum)*GameMap::MAPHEIGHT / GameMap::GRIDNUM);
			movedir = NONE;
			gridnum--;
			std::cout << "moving...end" << std::endl;
		}
		break;
	case RIGHT:
		if (getX() + 2 < (linenum+2)*GameMap::COLUMN_WIDTH+GameMap::COLUMN_WIDTH/2-Player::PLAYERWIDTH/2) {
			double next = (linenum+2)*GameMap::COLUMN_WIDTH +GameMap::COLUMN_WIDTH/2-Player::PLAYERWIDTH/2- getX();
			next = next*0.5;
			setPos(getX()+next, getY());
			std::cout << "moving..." << std::endl;
		}
		else {
			setPos((linenum+2)*GameMap::COLUMN_WIDTH+GameMap::COLUMN_WIDTH/2-Player::PLAYERWIDTH/2, getY());
			movedir = NONE;
			linenum++;
			std::cout << "moving...end" << std::endl;
		}
		break;
	case LEFT:
		if (getX() - 2 > (linenum)*GameMap::COLUMN_WIDTH+GameMap::COLUMN_WIDTH/2-Player::PLAYERWIDTH/2) {
			double next = (linenum)*GameMap::COLUMN_WIDTH +GameMap::COLUMN_WIDTH/2-Player::PLAYERWIDTH/2- getX();
			next = next*0.5;
			setPos(getX()+next, getY());
			std::cout << "moving..." << std::endl;
		}
		else {
			setPos((linenum)*GameMap::COLUMN_WIDTH+GameMap::COLUMN_WIDTH/2-Player::PLAYERWIDTH/2, getY());
			movedir = NONE;
			linenum--;
			std::cout << "moving...end" << std::endl;
		}
		break;
	}
}
int Player::getLinenum() {
	return linenum; //horizontal position
}
int Player::getGridnum() {
	return gridnum; //vertical position
}
int Player::incrLInenum(int num)
{
	return this->linenum += num;
}
int Player::incrGridnum(int num) {
	return this->gridnum += num;
}