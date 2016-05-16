#include "GModel.h"

GModel::GModel() {
}
GModel::GModel(std::tuple<GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,vec3,vec3,int> data_models)
{
	this->data_model = data_models;
	isTexture = false;
	isNormal = false;
}

GLuint GModel::getModelID()
{
	return std::get<0>(data_model);
}
GLuint GModel::getUVID() {
	return std::get<1>(data_model);
}
GLuint GModel::getVNormalID() {
	return std::get<2>(data_model);
}
GLuint GModel::getFNormalID() {
	return std::get<3>(data_model);
}
GLuint GModel::getTangentID() {
	return std::get<4>(data_model);
}
GLuint GModel::getBiTangentID() {
	return std::get<5>(data_model);
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
	return std::get<6>(data_model);
}

double GModel::getBoundboxX()
{
	return std::get<7>(data_model).x;
}

double GModel::getBoundboxY()
{
	return std::get<7>(data_model).y;
}

double GModel::getBoundboxZ()
{
	return std::get<7>(data_model).z;
}

int GModel::getVertexSize()
{
	return std::get<8>(data_model);
}

void GModel::setTexture(TextureType type, std::string filename)
{
	GLuint* pindex;
	Texture loaded(filename);
	if (type == TEXTURE_DIFFUSE) {
		pindex = &index_texturebuffer;
		isTexture = true;
	}
	else {
		pindex = &index_normalmapbuffer;
		isNormal = true;
	}

	glGenTextures(1, pindex);
	glBindTexture(GL_TEXTURE_2D, *pindex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 
		GL_RGB, loaded.getWidth(), loaded.getHeight(), 
		0, GL_RGB, GL_UNSIGNED_BYTE, loaded.toArray());
}

bool GModel::isTextureSet(TextureType type)
{
	switch (type) {
	case TEXTURE_DIFFUSE:
		return isTexture;
	case TEXTURE_NORMAL:
		return isNormal;
	default:
		return false;
	}
}


GModel::~GModel()
{
	if (isTexture) {
		glDeleteTextures(1, &index_texturebuffer);
	}
	if (isNormal) {
		glDeleteTextures(1, &index_normalmapbuffer);
	}
}



