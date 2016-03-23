#pragma once
#include "GObject.h"
#include "GameMap.h"

class Car : public GObject {
private:
	double dis_y;
public:
	enum { CARWIDTH=5, CARHEIGHT=10, GENTIME=500, SPEED=2 };//SPEED: per frame GENTIME:millisec
	Car(int line, GameMap::Linetype linetype, int z=1);
	virtual void draw();
	virtual void frameAction();
};