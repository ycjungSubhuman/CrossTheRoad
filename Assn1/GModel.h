#pragma once
#include <map>
#include <tuple>
#include <string>
#include <GL/glew.h>

/* representation of 3d model in the gpu */

class GModel {
private:
	std::tuple<GLuint, double, double, double, int> data_models;
public:
	GModel() = default;
	GModel(std::tuple<GLuint, double, double, double, int> data_models);
	GLuint getModelID();
	double getBoundboxX();
	double getBoundboxY();
	double getBoundboxZ();
	int getVertexSize();
};
