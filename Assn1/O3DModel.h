#pragma once
#include "GObject.h"
#include "GModel.h"
#include <map>
#include <tuple>
#include "GModel.h"

/* O3DModel : Any 3D Model on the screen. It has static method 
to load model from .wobj files. Its field represents the index of the
model stored in VBO(positions) draw call of the instance of this class
draws the wireframe of the model. */

class O3DModel : public GObject {
private:
	GModel model;
	double r, g, b;
public:
	enum RotPoint {
		AAA, BAA, CAA,
		ABA, BBA, CBA,
		ACA, BCA, CCA,

		AAB, BAB, CAB,
		ABB, BBB, CBB,
		ACB, BCB, CCB,

		CENTER, ORIGIN,

		AAC, BAC, CAC,
		ABC, BBC, CBC,
		ACC, BCC, CCC
	};

	O3DModel(vec3 pos, 
		RotPoint rotcnt, double rotx, double roty, 
		std::string type, GModel* data_model);
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
	void setColor(int r, int g, int b);
	void setModel(GModel* model);
};