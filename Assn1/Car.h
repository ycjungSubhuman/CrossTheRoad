#pragma once
#include "GObject.h"
#include "GameMap.h"

class Car : public GObject {
private:
	double dis_y;
public:
	enum { CARWIDTH=10, CARHEIGHT=15, GENTIME=1500, SPEED=4 };//SPEED: per frame GENTIME:millisec
	Car(int line, GameMap::Linetype linetype, int z=1);
	virtual void draw();
	virtual void frameAction();
};