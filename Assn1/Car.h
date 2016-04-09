#pragma once
#include "GObject.h"
#include "CarLikeObject.h"
#include "GameMap.h"
#include "mat.h"

/* Car : cars that moves on the road */
class Car : public CarLikeObject {
public:
	enum { CARWIDTH = 10, CARHEIGHT = 15, GENTIME = 1000, SPEED = 3 };//SPEED: per frame GENTIME:millisec
	Car(int line, GameMap::Linetype linetype);
};