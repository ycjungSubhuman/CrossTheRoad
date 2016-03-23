#include "Player.h"
#include "GameMap.h"

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

Player::Player(int z) : GObject(Rect(GameMap::COLUMN_WIDTH/2 - PLAYERWIDTH/2, PLAYERHEIGHT*(GameMap::GRIDNUM/2+1), PLAYERWIDTH, PLAYERHEIGHT), Rect(0, 0, PLAYERWIDTH, PLAYERHEIGHT), z, "PLAYER")
{
	linenum = 0;
	gridnum = GameMap::GRIDNUM / 2;
	status = ALIVE;
}
void Player::move(Player::Direction dir) {
	switch (dir) {
	case RIGHT:
		if (linenum < GameMap::MAPLENGTH - 1) {
			setPos(getX() + GameMap::COLUMN_WIDTH, getY());
			incrLInenum(1);
			prevdir = RIGHT;
		}
		break;
	case UP:
		if (gridnum < GameMap::GRIDNUM - 1) {
			setPos(getX(), getY() + PLAYERHEIGHT);
			incrGridnum(1);
			prevdir = UP;
		}
		break;
	case DOWN:
		if (gridnum > 0) {
			setPos(getX(), getY() - PLAYERHEIGHT);
			incrGridnum(-1);
			prevdir = DOWN;
		}
		break;
	}
}
Player::Direction  Player::getPrevDir() {
	return prevdir;
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