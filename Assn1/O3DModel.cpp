#include "O3DModel.h"

O3DModel::O3DModel(double x, double y, double z, double width, double height, RotPoint rotcnt, double rotx, double roty, std::string type, index_vbo)
	:GObject(.......);//fill in this initiallizer list, too.
{
	//inits model... just as ORect
}

std::map<std::string, GLint> O3DModel::loadModelFromFile(std::string name_file) {
	//TODO : implement model loading from given .wobj file.
	//this function
	//1. parses .wobj
	//2. put the vertex data into VBO (according to group. Separately.)
	//3. returns map from GROUP NAME(specified in .wobj) to VBO index
	//IT IS A STATIC FUNCTION!!!! IT CANNOT USE "this"
	//USED ONLY FROM CLASS DIRECTLY
}

void O3DModel::draw(mat4 MVMatrix) {
	//TODO : implement drawing the 3d model
}