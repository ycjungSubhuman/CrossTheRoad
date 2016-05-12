#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
private:
	unsigned char* texture;
	bool isAllocated;
	GLsizei width, height;
public:
	Texture();
	Texture(std::string name_file);
	void* toArray();
	int getWidth();
	int getHeight();
	bool isValid();
	~Texture();
};