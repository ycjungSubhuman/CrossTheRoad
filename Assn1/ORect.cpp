#include "ORect.h"

extern GLint u_Model;
extern GLint color_in;

ORect::ORect(double x, double y, double width, double height, RotPoint rotcnt, double rot, std::string type)
: GObject(Rect(x, y, width, height), Rect(0, 0, width, height), type){
	/* ---------------------------------------------------------------------- */
	/* implement color initiallizing(maybe blue?) and setting rotx, roty, rot */
	/* ---------------------------------------------------------------------- */
	this->r = 1;
	this->g = 1;
	this->b = 1;
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
	float height = this->getobj().height();
	float width = this->getobj().width();
	vec3 points[4] = { vec3(0, 0, 0), vec3(width, 0, 0), vec3(width, -height, 0), vec3(0, -height, 0) };
	vec4 colors[4] = { vec4(1,0,0, 1), vec4(1,0,0, 1), vec4(1,0,0, 1), vec4(1,0,0, 1) };

	glBufferData(GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	glUniformMatrix4fv(u_Model, 1, false, MVMatrix);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void ORect::frameAction()
{
	//do nothing
}
