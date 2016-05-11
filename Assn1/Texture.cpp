#include "Texture.h"
#include "SOIL.h"
#pragma comment (lib, "SOIL.lib")

Texture::Texture(std::string name_file) {
	//TODO: parse texture file and store it as unsigned char array
	texture = SOIL_load_image(name_file.c_str(), 
		&width, &height, 0, SOIL_LOAD_RGB);
}

void* Texture::toArray() {
	return (void*)texture;
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

Texture::~Texture() {
	SOIL_free_image_data(texture);
}
