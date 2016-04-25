#include "Player.h"
#include "GameMap.h"
#include <list>
#include <iostream>
#include <map>

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
	: GObject(Rect(GameMap::COLUMN_WIDTH/2, -(double)GameMap::MAPHEIGHT/GameMap::GRIDNUM*(GameMap::GRIDNUM/2), PLAYERWIDTH, PLAYERHEIGHT), Rect(PLAYERWIDTH*0.25, -PLAYERWIDTH*0.25, PLAYERWIDTH*0.5, PLAYERHEIGHT*0.5), "PLAYER")
{
	linenum = 0;
	gridnum = GameMap::GRIDNUM / 2;
	status = ALIVE;
	movedir = NONE;

	std::map<std::string, std::tuple<GLint, double, double>> map_modeldata =
		O3DModel::loadModelFromFile("player.wobj");

	//assemble palyer hierarchy
	neck = new O3DModel(0, 0, 0,
		O3DModel::BBC, 0, 0, 
		"NECK",
		map_modeldata.at("Neck"));
	head = new O3DModel(0,0,0,
		O3DModel::BBC, 0, 0,
		"HEAD",
		map_modeldata.at("Head"));
	eyes = new O3DModel(0, 0, 0,
		O3DModel::BBB, 0, 0,
		"EYES",
		map_modeldata.at("Eyes"));
	hair = new O3DModel(0, 0, 0,
		O3DModel::BBC, 0, 0,
		"HAIR",
		map_modeldata.at("Hair"));
	arm_left = new O3DModel(0, 0, 0,
		O3DModel::BAC, 0, 0,
		"ARMLEFT",
		map_modeldata.at("ArmLeft"));
	arm_right = new O3DModel(0, 0, 0,
		O3DModel::BCC, 0, 0,
		"ARMRIGHT",
		map_modeldata.at("ArmRight"));

	neck->addObject(head);
		head->addObject(hair);
		head->addObject(eyes);
	neck->addObject(arm_left);
	neck->addObject(arm_right);
}
void Player::move(Player::Direction dir) {
	status = ALIVE; //unbound from Log
	switch (dir) {
	case RIGHT:
		if (linenum < GameMap::MAPLENGTH - 1) {
			if (movedir == LEFT) linenum--;
			movedir = RIGHT;
		}
		break;
	case UP:
		if (gridnum > 0) {
			if (movedir == DOWN) gridnum++;
			movedir = UP;
		}
		break;
	case DOWN:
		if (gridnum < GameMap::GRIDNUM - 1) {
			if (movedir == UP) gridnum--;
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
	movedir = NONE;
	setPos((linenum)*GameMap::COLUMN_WIDTH + (double)GameMap::COLUMN_WIDTH / 2, -(double)(gridnum)*GameMap::MAPHEIGHT / GameMap::GRIDNUM);
}
void Player::finishMove() {

	switch (movedir) {
	case UP:
		gridnum--;
		undoMove();
		break;
	case DOWN:
		gridnum++;
		undoMove();
		break;
	case LEFT:
		linenum--;
		undoMove();
		break;
	case RIGHT:
		linenum++;
		undoMove();
		break;
	}
}
Player::Direction Player::getMoveDir() {
	return movedir;
}
Player::Status Player::getPlayerStatus() {
	return status;
}
void Player::bindPlayerToCenter(GObject* obj) {
	this->status = BOUND;
	bound_object = obj;
}
GObject* Player::getBoundObject() {
	return this->bound_object;
}
/*void Player::draw() {
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
	}
}*/
void Player::draw(mat4 MVMatrix) {

}
void Player::frameAction() {
	/*the controls will be processed in keyboard event callback.
	in this function. do things the player have to do frame by frame
	ex) flickering colors*/
	//moves player according to movedir
	if (status == ALIVE) {
		switch (movedir) {
		case UP:
			if (getY() + 2 < -(gridnum-1)*(GameMap::MAPHEIGHT/GameMap::GRIDNUM) ){
				double next = -(gridnum - 1)*GameMap::MAPHEIGHT / GameMap::GRIDNUM - getY();
				next = next*0.5;
				setPos(getX(), getY() + next);
			}
			else {
				finishMove();
			}
			break;
		case DOWN:
			if (getY() - 2 > -(gridnum+1)*GameMap::MAPHEIGHT / GameMap::GRIDNUM) {
				double next = -(gridnum+1)*GameMap::MAPHEIGHT / GameMap::GRIDNUM - getY();
				next = next*0.5;
				setPos(getX(), getY() + next);
			}
			else {
				finishMove();
			}
			break;
		case RIGHT:
			if (getX() + 2 < (linenum + 1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2) {
				double next = (linenum + 1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2 - getX();
				next = next*0.5;
				setPos(getX() + next, getY());
			}
			else {
				finishMove();
			}
			break;
		case LEFT:
			if (getX() - 2 > (linenum-1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2) {
				double next = (linenum-1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2 - getX();
				next = next*0.5;
				setPos(getX() + next, getY());
			}
			else {
				finishMove();
			}
			break;
		}

		//animation
		//head->setRotation(head->getRotation() + 10);
		if (movedir != NONE) {
			const double scale = 0.8;
			double arm_upper_rot_dist = scale * (ROTATION - arm_left_upper->getRotation());
			double arm_lower_rot_dist = scale * (ROTATION - arm_left_lower->getRotation());
			double leg_upper_rot_dist = scale * (ROTATION - leg_left_upper->getRotation());
			double leg_lower_rot_dist = scale * (ROTATION - leg_left_lower->getRotation());

			arm_left_upper->setRotation(arm_left_upper->getRotation() + arm_upper_rot_dist);
			arm_right_upper->setRotation(arm_right_upper->getRotation() + arm_upper_rot_dist);
			arm_left_lower->setRotation(arm_left_lower->getRotation() + arm_lower_rot_dist);
			arm_right_lower->setRotation(arm_right_upper->getRotation() + arm_lower_rot_dist);
			leg_left_upper->setRotation(leg_left_upper->getRotation() + leg_upper_rot_dist);
			leg_left_lower->setRotation(leg_left_lower->getRotation() + leg_lower_rot_dist);
			leg_right_upper->setRotation(leg_right_upper->getRotation() + leg_upper_rot_dist);
			leg_right_lower->setRotation(leg_right_lower->getRotation() + leg_lower_rot_dist);
		}
		else {
			const double scale = 0.8;
			double arm_upper_rot_dist = scale * (20 - arm_left_upper->getRotation());
			double arm_lower_rot_dist = scale * (40 - arm_left_lower->getRotation());
			double leg_upper_rot_dist = scale * (-20 - leg_left_upper->getRotation());
			double leg_lower_rot_dist = scale * (20 - leg_left_lower->getRotation());

			arm_left_upper->setRotation(arm_left_upper->getRotation() + arm_upper_rot_dist);
			arm_right_upper->setRotation(arm_right_upper->getRotation() + arm_upper_rot_dist);
			arm_left_lower->setRotation(arm_left_lower->getRotation() + arm_lower_rot_dist);
			leg_left_upper->setRotation(leg_left_upper->getRotation() + leg_upper_rot_dist);
			leg_left_lower->setRotation(leg_left_lower->getRotation() + leg_lower_rot_dist);
			leg_right_upper->setRotation(leg_right_upper->getRotation() + leg_upper_rot_dist);
			leg_right_lower->setRotation(leg_right_lower->getRotation() + leg_lower_rot_dist);		arm_right_lower->setRotation(arm_right_upper->getRotation() + arm_lower_rot_dist);
		}
	}
	else if(status == BOUND) { //when bound to some object
		//always set the position of this object to bound object
		Rect rect_bound = bound_object->getgloobj();
		Rect parent_rect = getParent()->getgloobj();
		this->setPos(
			(rect_bound.x() + rect_bound.width()/2)-parent_rect.x(), 
			rect_bound.y() - rect_bound.height()/2 - parent_rect.y());

		//set gridnum according to current location
		gridnum = floor(abs(getobj().y() / ((double)GameMap::MAPHEIGHT / GameMap::GRIDNUM)));
	}
}
int Player::getLinenum() {
	return linenum; //horizontal position
}
int Player::getGridnum() {
	return gridnum; //vertical position
}
int Player::incrLinenum(int num)
{
	return this->linenum += num;
}
int Player::incrGridnum(int num) {
	return this->gridnum += num;
}