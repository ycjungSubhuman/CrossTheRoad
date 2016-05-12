#include "GModel.h"

GModel::GModel() {
}
GModel::GModel(std::tuple<GLuint, vec3, vec3, int> data_models)
{
	this->data_model = data_models;
}

GLuint GModel::getModelID()
{
	return std::get<0>(data_model);
}
GLuint GModel::getTextureID()
{
	return index_texturebuffer;
}
vec3 GModel::getPos() {
	return std::get<1>(data_model);
}

double GModel::getBoundboxX()
{
	return std::get<2>(data_model).x;
}

double GModel::getBoundboxY()
{
	return std::get<2>(data_model).y;
}

double GModel::getBoundboxZ()
{
	return std::get<2>(data_model).z;
}

int GModel::getVertexSize()
{
	return std::get<3>(data_model);
}

void GModel::setTexture(std::string filename)
{
	glGenTextures(1, &index_texturebuffer);
	glBindTexture(GL_TEXTURE_2D, index_texturebuffer);
	texture = Texture(filename);
	glTexImage2D(GL_TEXTURE_2D, 0, 
		GL_RGB, texture.getWidth(), texture.getHeight(), 
		0, GL_RGB, GL_FLOAT, texture.toArray());

}

GModel::~GModel()
{
	if (texture.isValid()) {
		glDeleteTextures(1, &index_texturebuffer);
	}
}



