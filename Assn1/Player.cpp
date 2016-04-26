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
void Player::incrRotDest(double rot) {
	if (rot < 0) rot = 360 + rot;
	rotdest = rotdest + rot;
	rotdest = rotdest - floor(rotdest / 360) * 360;
}

Player::Player() 
	: GObject(Rect(GameMap::COLUMN_WIDTH/2 - PLAYERWIDTH/2, -(double)GameMap::MAPHEIGHT/GameMap::GRIDNUM*(GameMap::GRIDNUM/2), PLAYERWIDTH, PLAYERHEIGHT), Rect(PLAYERWIDTH*0.25, -PLAYERWIDTH*0.25, PLAYERWIDTH*0.5, PLAYERHEIGHT*0.5), "PLAYER")
{
	linenum = 0;
	gridnum = GameMap::GRIDNUM / 2;
	status = ALIVE;
	movedir = NONE;
	isBound = false;
	isDead = false;
	headdir = RIGHT;
	rotdest = 0;
	setRotCenter(PLAYERWIDTH / 2, -PLAYERHEIGHT / 2);

	std::map<std::string, std::tuple<GLint, double, double, double>> map_modeldata =
		O3DModel::loadModelFromFile("player.wobj");

	wow = new ORect(0, 0, 10, 10, ORect::CENTER, 0, "TEST");
	this->addObject(wow);

	//assemble palyer hierarchy
	try {
		neck = new O3DModel(0, 0, 0,
			O3DModel::BBC, 0, 0,
			"NECK",
			map_modeldata.at("Neck"));
		head = new O3DModel(0, 0, 0,
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
	catch (...) {
		std::cerr << "Error Occured when trying to load the player" << std::endl;
	}
}
void Player::move(Player::Key key) {
	if (isDead) return;
	isBound = false;
	switch (key) {
	case KEY_RIGHT:
		status = WALKING;
		movedir = TURN_RIGHT;
		incrRotDest(-90);
		incrHead(false);
		break;
	case KEY_UP:
		if (characterIsMovableTo(headdir)) {
			undoMove();
			status = WALKING;
			movedir = headdir;
		}
		break;
	case KEY_DOWN:
		if (characterIsMovableTo(reverseOf(headdir))) {
			undoMove();
			status = WALKING;
			movedir = reverseOf(headdir);
		}
		break;
	case KEY_LEFT:
		status = WALKING;
		movedir = TURN_LEFT;
		incrRotDest(90);
		incrHead(true);
		break;
	}
	//check for tree collisions
}
void Player::undoMove() {
	movedir = NONE;
	setRotation(rotdest);
	if (!isDead)
		setPos((linenum)*GameMap::COLUMN_WIDTH + (double)GameMap::COLUMN_WIDTH / 2-PLAYERWIDTH/2, -(double)(gridnum)*GameMap::MAPHEIGHT / GameMap::GRIDNUM);
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
	case TURN_RIGHT:
	case TURN_LEFT:
		setRotation(rotdest);
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
	isBound = true;
	bound_object = obj;
}
void Player::unbindPlayer() {
	isBound = false;
}
bool Player::isPlayerBound() {
	return isBound;
}
bool Player::isPlayerDead() {
	return isDead;
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
	if (status == WALKING && !isDead) {
		switch (movedir) {
		case UP:
			if (getY() + 5 < -(gridnum-1)*(GameMap::MAPHEIGHT/GameMap::GRIDNUM) ){
				double next = -(gridnum - 1)*GameMap::MAPHEIGHT / GameMap::GRIDNUM - getY();
				next = next*0.5;
				setPos(getX(), getY() + next);
			}
			else {
				finishMove();
			}
			break;
		case DOWN:
			if (getY() - 5 > -(gridnum+1)*GameMap::MAPHEIGHT / GameMap::GRIDNUM) {
				double next = -(gridnum+1)*GameMap::MAPHEIGHT / GameMap::GRIDNUM - getY();
				next = next*0.5;
				setPos(getX(), getY() + next);
			}
			else {
				finishMove();
			}
			break;
		case RIGHT:
			if (getX() + 5 < (linenum + 1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2) {
				double next = (linenum + 1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2 - getX();
				next = next*0.5;
				setPos(getX() + next, getY());
			}
			else {
				finishMove();
			}
			break;
		case LEFT:
			if (getX() - 5 > (linenum-1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2) {
				double next = (linenum-1)*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - Player::PLAYERWIDTH / 2 - getX();
				next = next*0.5;
				setPos(getX() + next, getY());
			}
			else {
				finishMove();
			}
			break;
		case TURN_LEFT:
		{
			double rot_curr = getRotation();
			if (rotdest>rot_curr || rot_curr-rotdest >180) {
				setRotation(rot_curr + 20);
			}
			else {
				finishMove();
			}
		}
			break;
		case TURN_RIGHT:
		{
			double rot_curr = getRotation();
			if (rotdest<rot_curr && rot_curr - rotdest < 180 || rot_curr==0) {
				setRotation(rot_curr - 20);
			}
			else {
				finishMove();
			}
		}
			break;
		}
	}
	if(isBound) { //when bound to some object
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
void Player::incrHead(bool incr) {
	if (incr) {
		switch (headdir) {
		case RIGHT: 
			headdir = UP;
			break;
		case UP:
			headdir = LEFT;
			break;
		case LEFT:
			headdir = DOWN;
			break;
		case DOWN:
			headdir = RIGHT;
			break;
		}
	}
	else {
		switch (headdir) {
		case RIGHT: 
			headdir = DOWN;
			break;
		case UP:
			headdir = RIGHT;
			break;
		case LEFT:
			headdir = UP;
			break;
		case DOWN:
			headdir = LEFT;
			break;
		}
	}
}
void Player::markDead() {
	isDead = true;
}
bool Player::characterIsMovableTo(Direction dir) {
	switch (dir) {
	case RIGHT: 
		if (linenum - 1 < GameMap::MAPLENGTH) return true;
		else return false;
	case LEFT:
		if (linenum > 0) return true;
		else return false;
	case UP:
		if (gridnum - 1 < GameMap::GRIDNUM) return true;
		else return false;
	case DOWN:
		if (gridnum > 0) return true;
		else return false;
	default: return true;
	}
	
}
Player::Direction Player::reverseOf(Player::Direction dir) {
	switch (dir) {
	case RIGHT: return LEFT;
	case LEFT: return RIGHT;
	case UP: return DOWN;
	case DOWN: return UP;
	default: return dir;
	}
}