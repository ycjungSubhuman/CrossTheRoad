#include "Player.h"
#include "Player.h"
#include "GameMap.h"

Player::Player() : GObject(Rect(GameMap::COLUMN_WIDTH/2 - PLAYERWIDTH/2, GameMap::MAPHEIGHT/2 - PLAYERHEIGHT/2, PLAYERWIDTH, PLAYERHEIGHT), Rect(0, 0, PLAYERWIDTH, PLAYERHEIGHT), 1, "PLAYER")
{
	linenum = 0;
	status = ALIVE;
}
Player::Status Player::getPlayerStatus() {
	return status;
}
void Player::draw() {
	switch (getPlayerStatus()) {
	case Player::ALIVE:
		/* write player graphics */
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