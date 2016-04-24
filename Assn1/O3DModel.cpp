#include "O3DModel.h"

O3DModel::O3DModel(double x, double y, double z, RotPoint rotcnt, double rotx, double roty, std::string type, std::tuple<GLint,double,double> data_model)
	:GObject(.......);//fill in this initiallizer list, too.
{
	//inits model... just as ORect
}

std::map<std::string, std::tuple<GLint,double,double>> O3DModel::loadModelFromFile(std::string name_file) { 
	//TODO : implement model loading from given .wobj file.  
	//this function
	//1. parses .wobj
	//2. put the vertex data into VBO (according to group. Separately.)
	//3. finds the best boundbox according to vertices
	//4. returns map from GROUP NAME(specified in .wobj) to (VBO index, boundbox_width, boudbox_height)
	//		string -> (GLint, double, double)
	//IT IS A STATIC FUNCTION!!!! IT CANNOT USE "this"
	//USED ONLY FROM CLASS DIRECTLY
}

void O3DModel::draw(mat4 MVMatrix) {
	//TODO : implement drawing the 3d model
}
