#pragma once
#include "GObject.h"

class Car : public GObject {
private:
	enum { CARWIDTH=10, CARHEIGHT=30};
	double dis_y;
public:
	Car(int line, int z=1);
	void move();
};