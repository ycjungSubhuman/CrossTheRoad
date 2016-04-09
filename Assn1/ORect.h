#pragma once
#include "GObject.h"

class ORect : public GObject {
private:
	double r, g, b;
public:
	enum RotPoint {TOPLEFT, TOPMIDDLE, TOPRIGHT, MIDDLELEFT, CENTER, MIDDLERIGHT, BOTTOMLEFT, BOTTOMMIDDLE, BOTTOMRIGHT };
	ORect(double x, double y, double width, double height, RotPoint rotcnt, double rot, std::string type);
	void setColor(int r, int g, int b);
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction(); //does nothing, placeholder
};