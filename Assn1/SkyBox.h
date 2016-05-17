#pragma once
#include <GL/glew.h>
#include <string>
#include "mat.h"
#include "GObject.h"

class SkyBox : public GObject {
private:
	GLuint buffer_tex;
public:
	SkyBox(
		std::string px,
		std::string nx,
		std::string py,
		std::string ny,
		std::string pz,
		std::string nz
	);
	virtual void draw(mat4 MVMatrix);
	virtual void frameAction();
};
