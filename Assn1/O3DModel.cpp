#include "O3DModel.h"
#include <vector>
#include "AssetManager.h"
extern GLint u_Model;
extern GLint color_in;
extern AssetManager* assetManager;
O3DModel::O3DModel(vec3 pos, RotPoint rotcnt, double rotz, double rotx, std::string type, GModel* model)
	:GObject(Rect(pos.x, pos.y, 0, 0), Rect(0, 0, 0, 0), type)
{
	double rcntx, rcnty, rcntz;
	//inits model... just as ORect
	switch (rotcnt) {
	case CENTER:
		rcntx = pos.x;
		rcnty = pos.y;
		rcntz = pos.z;
		break;
	case ORIGIN:
	default:
		rcntx = 0;
		rcnty = 0;
		rcntz = 0;
		break;
	}
	setRotation(rotz, rotx);
	setPos(pos.x, pos.y, pos.z);

	index_vbo = model->getModelID();
	size_vertex = model->getVertexSize();
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}

void O3DModel::draw(mat4 MVMatrix) {
	//TODO : implement drawing the 3d model
	GLint error;
	vec4 colors = vec4(r, g, b, 1);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, index_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glUniform4fv(color_in, 1, colors);
	glUniformMatrix4fv(u_Model, 1, true, MVMatrix);
	glDrawArrays(GL_TRIANGLES, 0, size_vertex);
	glDisableVertexAttribArray(0);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("%x\n", error);
	}
}
void O3DModel::setColor(int r, int g, int b)
{
	/* ------------------------------------------------------ */
	/* implement converting int rgb to double rgb and storing */
	/* ------------------------------------------------------ */
	this->r = ((double)r / 256.0f);
	this->g = ((double)g / 256.0f);
	this->b = ((double)b / 256.0f);
}

void O3DModel::frameAction() {

}

void O3DModel::setModel(GModel* model) {
	index_vbo = model->getModelID();
	size_vertex = model->getVertexSize();
}