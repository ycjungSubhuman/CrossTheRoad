#pragma once
#include "Point.h"

class Rect {
private:
	Point coord;
	double width, height;
public:
	Rect(double x, double y, double width, double height);
	double top();
	double bottom();
	double left();
	double right();
};