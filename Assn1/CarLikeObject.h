#pragma once
#include "ORect.h"
#include "GameMap.h"
#include "mat.h"

/* CarLikeObject : 
		it is an object that are generated at the top and bottom of the map.
		They move vertically every frame according to given dis_y. 
*/
class CarLikeObject : public ORect {
protected:
	double dis_y;
public:
	CarLikeObject(int line, GameMap::Linetype linetype, double widht, double height, std::string type);
	void setDisY(double dis_y); //sets dis_y(speed), preserves sign because it will never change
	virtual void frameAction(); //moving
};