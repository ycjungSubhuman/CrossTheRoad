#pragma once
#include "GObject.h"
#include <map>

/* O3DModel : Any 3D Model on the screen. It has static method 
to load model from .wobj files. Its field represents the index of the
model stored in VBO(positions) draw call of the instance of this class
draws the wireframe of the model. */

class O3DModel : public GObject {
private:
	GLint index_vbo;
public:
	enum RotPoint {
		LLL, LLM, LLR,
		LML, LMM, LMR,
		LRL, LRM, LRR,

		MLL, MLM, MLR,
		MML, MMM, MMR,
		MRL, MRM, MRR,

		RLL, RLM, RLR,
		RML, RMM, RMR,
		RRL, RRM, RRR,
	};

	O3DModel(double x, double y, double z, double width, double height, RotPoint rotcnt, double rotx, double roty, std::string type, GLint index_vbo);
	static std::map<std::string, GLint> loadModelFromFile(std::string name_file);
	virtual void draw(mat4 MVMatrix);
};