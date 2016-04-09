#pragma once
#include "GObject.h"
#include "GameMap.h"
#include "mat.h"

class CarLikeObject : public GObject {
protected:
	double dis_y;
public:
	CarLikeObject(int line, GameMap::Linetype linetype, double widht, double height, std::string type);
	void setDisY(double dis_y); //sets dis_y(speed), preserves sign because it will never change
	virtual void frameAction(); //moving
};