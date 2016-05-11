#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
private:
	unsigned char* texture;
	GLsizei width, height;
public:
	Texture(std::string name_file);
	void* toArray();
	int getWidth();
	int getHeight();
	~Texture();
};