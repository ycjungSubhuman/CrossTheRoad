#include "Texture.h"
#include "SOIL.h"
#pragma comment (lib, "SOIL.lib")

Texture::Texture() {
	isAllocated = false;
}
Texture::Texture(std::string name_file) {
	isAllocated = true;
	texture = SOIL_load_image(name_file.c_str(),
		&width, &height, 0, SOIL_LOAD_RGB);
}

void* Texture::toArray() {
	return (void*)texture;
}

GLsizei Texture::getWidth() {
	return width;
}

GLsizei Texture::getHeight() {
	return height;
}
bool Texture::isValid() {
	return isAllocated;
}

Texture::~Texture() {
	if (isAllocated)
		SOIL_free_image_data(texture);
}
