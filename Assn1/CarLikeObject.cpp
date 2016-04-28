#include "CarLikeObject.h"
#include "GameMap.h"
#include <cmath>
#include "ModelManager.h"

extern ModelManager* modelManager;

CarLikeObject::CarLikeObject(int line, GameMap::Linetype linetype, double width, double height, std::string type) 
	:O3DModel(0, 0, 0, CENTER, 0, 0, "CAR", modelManager->getModel("police_car"))
{
	//init obj speed
	dis_y = 1;

	//set initial position
	int x, y;
	//start from up or down
	if (linetype == GameMap::ROADDOWN || linetype == GameMap::WATERDOWN) {
		dis_y = -dis_y;//goes down
		y = height;
	}
	else {
		y = -GameMap::MAPHEIGHT;
	}
	//line number
	x = line*GameMap::COLUMN_WIDTH + GameMap::COLUMN_WIDTH / 2 - width / 2;
	setRect(Rect(x, y, width, height));
}
void CarLikeObject::setDisY(double dis_y) {
	if (this->dis_y < 0) {
		this->dis_y = -abs(dis_y);
	}
	else {
		this->dis_y = abs(dis_y);
	}
}

void CarLikeObject::frameAction() {
	//move
	setPos(getX(), getY() + dis_y);
}