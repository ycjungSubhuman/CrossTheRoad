#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
private:
	bool isAllocated;
	GLsizei width, height;
	unsigned char* texture;
public:
	Texture();
	Texture(std::string name_file);
	void* toArray();
	GLsizei getWidth();
	GLsizei getHeight();
	bool isValid();
	~Texture();
};