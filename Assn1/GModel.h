#pragma once
#include <map>
#include <tuple>
#include <string>
#include <GL/glew.h>
#include "mat.h"
#include "Texture.h"

/* representation of 3d model in the gpu */

class GModel {
private:
	std::tuple<GLuint, vec3, vec3, int> data_model;
	GLuint index_texturebuffer;
	Texture texture;
public:
	GModel();
	GModel(std::tuple<GLuint, vec3, vec3, int> data_models);
	GLuint getModelID();
	GLuint getTextureID();
	vec3 getPos();
	double getBoundboxX();
	double getBoundboxY();
	double getBoundboxZ();
	int getVertexSize();
	void setTexture(std::string filename);
	~GModel();
};
