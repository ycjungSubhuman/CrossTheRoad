#include "TextureCube.h"
#include "Texture.h"
#include <algorithm>

TextureCube::TextureCube(std::string px, std::string nx, std::string py, std::string ny, std::string pz, std::string nz)
{
	//load from file
	tex.push_front(std::make_pair(new Texture(nz), 
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z));
	tex.push_front(std::make_pair(new Texture(pz),
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z));
	tex.push_front(std::make_pair(new Texture(ny),
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y));
	tex.push_front(std::make_pair(new Texture(py),
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y));
	tex.push_front(std::make_pair(new Texture(nx),
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X));
	tex.push_front(std::make_pair(new Texture(px),
		GL_TEXTURE_CUBE_MAP_POSITIVE_X));
	
	//get buffer
	glGenTextures(1, &buffer);
	glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);
	GLint error = glGetError();

	std::for_each(tex.begin(), tex.end(), [=] (std::pair<Texture*,GLenum> f_data) {
		glTexImage2D(f_data.second, 0,
			GL_RGB, f_data.first->getWidth(), f_data.first->getHeight(), 0,
			GL_RGB, GL_UNSIGNED_BYTE, 
			f_data.first->toArray());
	});
	error = glGetError();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
GLuint TextureCube::getID() {
	return buffer;
}
