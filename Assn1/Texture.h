#pragma once
#include <GL/glew.h>
#include <string>

/* class representation of texture data(or bumpmap, normal)
 * convertes any jpg, png, bmp to array of uchar
 * stores width, height information
 * use the instance of this class to use gl2DImageTex */
class Texture {
private:
	//checks if allocated
	bool isAllocated;
	GLsizei width, height;
	unsigned char* texture;
public:
	Texture();
	Texture(std::string name_file);//load from file
	void* toArray(); //returns array of uchar(to pass to gl2DTexImage2D)
	GLsizei getWidth();
	GLsizei getHeight();
	bool isValid(); //checks if the texture is allocated
	~Texture();
};