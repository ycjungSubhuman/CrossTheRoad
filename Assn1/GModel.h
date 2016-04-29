#pragma once
#include <map>
#include <tuple>
#include <string>
#include <GL/glew.h>
#include "mat.h"

/* representation of 3d model in the gpu */

class GModel {
private:
	std::tuple<GLuint, vec3, vec3, int> data_model;
public:
	GModel() = default;
	GModel(std::tuple<GLuint, vec3, vec3, int> data_models);
	GLuint getModelID();
	vec3 getPos();
	double getBoundboxX();
	double getBoundboxY();
	double getBoundboxZ();
	int getVertexSize();
};
