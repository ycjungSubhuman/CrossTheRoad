#pragma once
#include "GObject.h"
#include "GameMap.h"

class Car : public GObject {
private:
	enum { CARWIDTH=10, CARHEIGHT=30, GENTIME=1000, SPEED=5 };//SPEED: per frame GENTIME:millisec
	double dis_y;
public:
	Car(int line, GameMap::Linetype linetype, int z=1);
	virtual void draw();
	virtual void frameAction();
};