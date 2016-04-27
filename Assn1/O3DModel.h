#pragma once
#include "GObject.h"
#include <map>
#include <tuple>

/* O3DModel : Any 3D Model on the screen. It has static method 
to load model from .wobj files. Its field represents the index of the
model stored in VBO(positions) draw call of the instance of this class
draws the wireframe of the model. */

class O3DModel : public GObject {
private:
	GLint index_vbo;
public:
	enum RotPoint {
		AAA, BAA, CAA,
		ABA, BBA, CBA,
		ACA, BCA, CCA,

		AAB, BAB, CAB,
		ABB, BBB, CBB,
		ACB, BCB, CCB,

		AAC, BAC, CAC,
		ABC, BBC, CBC,
		ACC, BCC, CCC
	};

	O3DModel(double x, double y, double z, 
		RotPoint rotcnt, double rotx, double roty, 
		std::string type, 
		std::tuple<GLuint,double,double,double,int> data_model);
	static std::map<std::string, std::tuple<GLuint, double, double, double, int>> loadModelFromFile(std::string name_file);
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
};