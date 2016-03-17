#include "Player.h"
#include "GameMap.h"

Player::Player() : GObject(Rect(GameMap::COLUMN_WIDTH/2 - PLAYERWIDTH/2, GameMap::MAPHEIGHT/2 - PLAYERHEIGHT/2, PLAYERWIDTH, PLAYERHEIGHT), Rect(0, 0, PLAYERWIDTH, PLAYERHEIGHT), 1, "PLAYER")
{
	linenum = 0;
	status = ALIVE;
	//set draw function
	setFunc([this](const Rect& rect, int r, int g, int b)->void {
		switch (this->getPlayerStatus()) {
		case Player::ALIVE:
			/* write player graphics */
			break;
		case Player::DEAD:
			/* show blank space */
			break;
		}
	});
}
Player::Status Player::getPlayerStatus() {
	return status;
}
void Player::frameAction() {
	/*the controls will be processed in keyboard event callback.
	in this function. do things the player have to do frame by frame
	ex) flickering colors*/
}
int Player::getLinenum() {
	return linenum;
}
int Player::incrLinenum(int num) {
	this->linenum += num;
}