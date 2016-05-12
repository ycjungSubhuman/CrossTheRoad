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
GLuint GModel::getTextureID(TextureType type)
{
	switch (type) {
	case TEXTURE_DIFFUSE:
		return index_texturebuffer;
	case TEXTURE_NORMAL:
		return index_normalmapbuffer;
	default:
		return -1; //non existing
	}
	
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

void GModel::setTexture(TextureType type, std::string filename)
{
	Texture* current;
	GLuint* pindex;
	if (type == TEXTURE_DIFFUSE) {
		current = &texture;
		pindex = &index_texturebuffer;
	}
	else {
		current = &normalmap;
		pindex = &index_normalmapbuffer;
	}

	glGenTextures(1, pindex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *pindex);
	*current = Texture(filename);
	glTexImage2D(GL_TEXTURE_2D, 0, 
		GL_RGB, current->getWidth(), current->getHeight(), 
		0, GL_RGB, GL_FLOAT, current->toArray());
}

bool GModel::isTextureSet(TextureType type)
{
	switch (type) {
	case TEXTURE_DIFFUSE:
		return texture.isValid();
	case TEXTURE_NORMAL:
		return normalmap.isValid();
	default:
		return false;
	}
}


GModel::~GModel()
{
	if (texture.isValid()) {
		glDeleteTextures(1, &index_texturebuffer);
	}
}



