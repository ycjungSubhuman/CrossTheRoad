#pragma once
#include <map>
#include <tuple>
#include <string>
#include <GL/glew.h>
/* loads 3d Models and stores. */
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
	int getVertexNumber();
};
