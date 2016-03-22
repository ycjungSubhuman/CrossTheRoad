#include "Car.h"
#include "GameMap.h"

Car::Car(int line, GameMap::Linetype linetype, int z) : GObject(Rect(0,0,CARWIDTH,CARHEIGHT), Rect(0,0,CARWIDTH,CARHEIGHT), z, "CAR")
{
	//set car speed
	dis_y = 0.01;

	//set initial position
	int x, y;
	//start from up or down
	if (linetype = GameMap::ROADDOWN) {
		dis_y = -dis_y;//goes left
		y = 0 - CARHEIGHT;
	}
	else {
		y = GameMap::MAPHEIGHT;
	}
	//line number
	x = line*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - CARWIDTH / 2;
	setRect(Rect(x, y, CARWIDTH, CARHEIGHT));
}
void Car::draw() {
	/* implement car drawing here */
}
void Car::frameAction() {
	//move
	setPos(getX(), getY() + dis_y);
}