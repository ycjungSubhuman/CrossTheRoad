#include "ORect.h"

extern GLint u_Model;
extern GLint color_in;
extern GLuint rectbuffer;
extern GLint u_isTextured;

ORect::ORect(double x, double y, double width, double height, RotPoint rotcnt, double rot, std::string type)
: GObject(Rect(x, y, width, height), Rect(0, 0, width, height), type){
	/* ---------------------------------------------------------------------- */
	/* implement color initiallizing(maybe blue?) and setting rotx, roty, rot */
	/* ---------------------------------------------------------------------- */
	double rotx, roty;
	this->r = 1;
	this->g = 1;
	this->b = 1;

	switch(rotcnt){
	case TOPLEFT:
		rotx = 0; roty = 0; break;
	case TOPMIDDLE:
		rotx = 0 + width / 2; roty = 0; break;
	case TOPRIGHT:
		rotx = 0 + width; roty = 0; break;
	case MIDDLELEFT:
		rotx = 0; roty = 0 - height / 2; break;
	case CENTER:
		rotx = 0 + width / 2; roty = 0 - height / 2; break;
	case MIDDLERIGHT:
		rotx = 0 + width; roty = 0 - height / 2; break;
	case BOTTOMLEFT:
		rotx = 0; roty = 0 - height; break;
	case BOTTOMMIDDLE:
		rotx = 0 + width / 2; roty = 0 - height; break;
	case BOTTOMRIGHT:
		rotx = 0 + width; roty = 0 - height; break;
	}
	setRotCenter(rotx, roty);
	setRotation(rot);
}
void ORect::setColor(int r, int g, int b)
{
	/* ------------------------------------------------------ */
	/* implement converting int rgb to double rgb and storing */
	/* ------------------------------------------------------ */
	this->r = ((double)r / 256.0f);
	this->g = ((double)g / 256.0f);
	this->b = ((double)b / 256.0f);
}

void ORect::draw(mat4 MVMatrix)
{
	/* ------------------------------------------------------- */
	/* implement drawing ORect according to obj and rgb values */
	/* ------------------------------------------------------- */
	float height = this->getobj().height();
	float width = this->getobj().width();
	GLint error;

	MVMatrix = MVMatrix * Scale(width, height, 1);
	
	vec4 colors = vec4(r, g, b, 1);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, rectbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glUniform1i(u_isTextured, 0);
	glUniform4fv(color_in, 1, colors);
	glUniformMatrix4fv(u_Model, 1, true, MVMatrix);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("%x\n", error);
	}
}

void ORect::frameAction()
{
	//do nothing
}
void ORect::setPosZ(double z) {
	setPos(getX(), getY(), z);
}
