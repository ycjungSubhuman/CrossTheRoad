#include "ORect.h"

ORect::ORect(double x, double y, double width, double height, RotPoint rotcnt, double rot)
: GObject(Rect(x, y, width, height), Rect(0, 0, width, height), "ORect"){
	/* ---------------------------------------------------------------------- */
	/* implement color initiallizing(maybe blue?) and setting rotx, roty, rot */
	/* ---------------------------------------------------------------------- */
}
void ORect::setColor(int r, int g, int b)
{
	/* ------------------------------------------------------ */
	/* implement converting int rgb to double rgb and storing */
	/* ------------------------------------------------------ */
}

void ORect::draw(mat4 MVMatrix)
{
	/* ------------------------------------------------------- */
	/* implement drawing ORect according to obj and rgb values */
	/* ------------------------------------------------------- */
}

void ORect::frameAction()
{
	//do nothing
}
