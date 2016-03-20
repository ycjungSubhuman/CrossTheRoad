#pragma once
#include <gl/glut.h>
#include <gl/gl.h>

class Rect {
private:
	double _x, _y, _width, _height;
	static bool isPointInRect(Rect& rect, double x, double y);
public:
	Rect();
	Rect(double x, double y, double width, double height);
	double top();
	double bottom();
	double left();
	double right();
	double x();
	double y();
	double width();
	double height();
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	static bool isCollide(Rect& a, Rect& b);
};