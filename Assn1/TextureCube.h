#pragma once
#include "Texture.h"
#include <GL/glew.h>
#include <string>
#include <list>
#include <tuple>

class TextureCube {
private:
	std::list<std::pair<Texture*,GLenum>> tex;
	GLuint buffer;
public:
	TextureCube(
		std::string px,
		std::string nx,
		std::string py,
		std::string ny,
		std::string pz,
		std::string nz
	);
	GLuint getID();
};