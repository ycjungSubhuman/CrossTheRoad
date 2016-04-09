#pragma once
#include "GObject.h"

/* ORect: Any rectangular object that appears in the game. It has certain rgb values.
	when drawed, it draws a rectangle according to obj, rotx, roty, rot in GObject and 
	rgb values. */

class ORect : public GObject {
private:
	double r, g, b;
public:
	/* enum RotPoint is for easily deciding the center of rotation when calling the constructor. 
	when rotcnt is given in the constructor, it generates proper rotx and roty value to specified RotPoint
	for example, TOPLEFT is for the top left corner of obj. Similarly, CENTER is the center point of obj.
	*/
	enum RotPoint {TOPLEFT, TOPMIDDLE, TOPRIGHT, MIDDLELEFT, CENTER, MIDDLERIGHT, BOTTOMLEFT, BOTTOMMIDDLE, BOTTOMRIGHT };
	ORect(double x, double y, double width, double height, RotPoint rotcnt, double rot, std::string type);
	void setColor(int r, int g, int b);
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction(); //does nothing, placeholder
};