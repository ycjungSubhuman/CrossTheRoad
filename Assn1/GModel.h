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
	std::tuple<GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,vec3,vec3,int> data_model;
	bool isTexture;
	bool isNormal;
	GLuint index_texturebuffer;
	GLuint index_normalmapbuffer;
public:
	//types of texture. diffuse for image mapping(ex: banana peel)
	//normal for surface normal mapping
	enum TextureType { TEXTURE_DIFFUSE, TEXTURE_NORMAL };
	GModel();
	GModel(std::tuple<GLuint,GLuint,GLuint,GLuint,GLuint,GLuint,vec3,vec3,int> data_models);
	GLuint getModelID();
	GLuint getUVID();
	GLuint getVNormalID();
	GLuint getFNormalID();
	GLuint getTangentID();
	GLuint getBiTangentID();
	//returns the buffer id of given texture type
	GLuint getTextureID(TextureType type); 
	vec3 getPos();
	double getBoundboxX();
	double getBoundboxY();
	double getBoundboxZ();
	int getVertexSize();
	//set specified texture for this model with given file.
	void setTexture(TextureType type, std::string filename);
	bool isTextureSet(TextureType type); //returns if the specified texture is set
	~GModel();
};
