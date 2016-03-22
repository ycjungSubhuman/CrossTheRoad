#include "Player.h"
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

Player::Player() : GObject(Rect(GameMap::COLUMN_WIDTH/2 - PLAYERWIDTH/2, GameMap::MAPHEIGHT/2 - PLAYERHEIGHT/2, PLAYERWIDTH, PLAYERHEIGHT), Rect(0, 0, PLAYERWIDTH, PLAYERHEIGHT), 1, "PLAYER")
{
	linenum = 0;
	status = ALIVE;
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
	return linenum;
}
int Player::incrLInenum(int num)
{
	return this->linenum += num;
}