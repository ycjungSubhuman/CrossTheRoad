#include "O3DModel.h"
#include <vector>

O3DModel::O3DModel(double x, double y, double z, RotPoint rotcnt, double rotz, double rotx, std::string type, GModel& model)
	:GObject(Rect(x, y, 0, 0), Rect(0, 0, 0, 0), type)
{
	double rcntx, rcnty, rcntz;
	//inits model... just as ORect
	switch (rotcnt) {
	case CENTER:
		rcntx = model.getBoundboxX() / 2;
		rcnty = model.getBoundboxY() / 2;
		rcntz = model.getBoundboxZ() / 2;
		break;
	case ORIGIN:
	default:
		rcntx = 0;
		rcnty = 0;
		rcntz = 0;
		break;
	}
	setRotCenter(rcntx, rcnty, rcntz);
	setRotation(rotz, rotx);

	index_vbo = model.getModelID();
	size_vertex = model.getVertexSize();
}

void O3DModel::draw(mat4 MVMatrix) {
	//TODO : implement drawing the 3d model
}

void O3DModel::frameAction() {

}