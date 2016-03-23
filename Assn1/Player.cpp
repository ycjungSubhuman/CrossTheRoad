#include "Player.h"
#include "GameMap.h"
#include <list>
#include <iostream>

void drawcircle(double x, double y, double radius)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (double angle = 1.0f; angle<361.0f; angle += 0.2)
	{
		glVertex2f(x + sin(angle)*radius, y + cos(angle)*radius);
	}
	glEnd();
}

Player::Player(int z) : GObject(Rect(GameMap::COLUMN_WIDTH/2 - PLAYERWIDTH/2, PLAYERHEIGHT*(GameMap::GRIDNUM/2+1), PLAYERWIDTH, PLAYERHEIGHT), Rect(PLAYERWIDTH*0.25, -PLAYERWIDTH*0.25, PLAYERWIDTH*0.5, PLAYERHEIGHT*0.5), z, "PLAYER")
{
	linenum = -1;
	gridnum = GameMap::GRIDNUM / 2;
	status = ALIVE;
	movedir = NONE;
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
	glColor3f(1.0f, 0.0f, 0.0f);
	Rect playerobj = getobj();
	double playerX = (playerobj.left() + playerobj.right()) / 2;
	double playerY = (playerobj.top() + playerobj.bottom()) / 2;
	double radius = (playerobj.right() - playerobj.left()) / 2;
	switch (getPlayerStatus()) {
	case Player::ALIVE:
		/* show red circle */
		drawcircle(playerX, playerY, radius);
		break;
	case Player::DEAD:
		/* show blank space */
		break;
	}
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