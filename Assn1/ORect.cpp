#include "ORect.h"

extern GLint u_Model;
extern GLint color_in;
extern GLuint rectbuffer;

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
	GLint error;

	MVMatrix = MVMatrix * Scale(width, height, 1);
	
	vec4 colors = vec4(r, g, b, 1);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, rectbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glUniform4fv(color_in, 1, colors);
	glUniformMatrix4fv(u_Model, 1, false, transpose(MVMatrix));
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
