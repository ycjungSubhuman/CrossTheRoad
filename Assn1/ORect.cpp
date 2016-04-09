#include "ORect.h"

extern GLint u_Model;

ORect::ORect(double x, double y, double width, double height, RotPoint rotcnt, double rot, std::string type)
: GObject(Rect(x, y, width, height), Rect(0, 0, width, height), type){
	/* ---------------------------------------------------------------------- */
	/* implement color initiallizing(maybe blue?) and setting rotx, roty, rot */
	/* ---------------------------------------------------------------------- */
	this->r = 0;
	this->g = 0;
	this->b = 0;
}
void ORect::setColor(int r, int g, int b)
{
	/* ------------------------------------------------------ */
	/* implement converting int rgb to double rgb and storing */
	/* ------------------------------------------------------ */
	this->r = ((double)r / 256);
	this->g = ((double)g / 256);
	this->b = ((double)b / 256);
}

void ORect::draw(mat4 MVMatrix)
{
	/* ------------------------------------------------------- */
	/* implement drawing ORect according to obj and rgb values */
	/* ------------------------------------------------------- */
	float x = this->getobj().x();
	float y = this->getobj().y();
	float height = this->getobj().height();
	float width = this->getobj().width();
	vec3 points[4] = { vec3(x, y, 0), vec3(x + width, y, 0), vec3(x + width, y - height, 0), vec3(x, y - height, 0) };
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glUniformMatrix4fv(u_Model, 1, false, MVMatrix);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ORect::frameAction()
{
	//do nothing
}
