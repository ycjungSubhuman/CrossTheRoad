#include "shaderutil.h"
#include <iostream>
#include <stdlib.h>

char* readShaderSource(const char* shaderFile) {
	/* reads glsl file and returns string of the source code */
	FILE* fp;
	fopen_s(&fp, shaderFile, "r");
	char* buf;
	long size;

	if (fp == NULL) return NULL;
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buf = (char*)malloc((size + 1) * sizeof(char));
	fread(buf, 1, size, fp);
	buf[size] = '\0';
	fclose(fp);
	return buf;
}
void checkError(GLint status, const char* msg) {
	if (status != GL_TRUE) {
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
}
void loadShadersFromFile(const char* vShaderFile, const char* fShaderFile) {
	GLcharARB *vSource, *fSource;

	vSource = readShaderSource(vShaderFile);
	if (vSource == NULL) {
		std::cout << "failed to read default vertex shader" << std::endl;
		exit(EXIT_FAILURE);
	}
	fSource = readShaderSource(fShaderFile);
	if (fSource == NULL) {
		std::cout << "failed to read default fragment shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	GLuint program;
	program = glCreateProgram();

	GLuint vShader, fShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	glShaderSource(vShader, 1, (const GLcharARB**)&vSource, NULL);
	glShaderSource(fShader, 1, (const GLcharARB**)&fSource, NULL);

	glCompileShader(vShader);
	glCompileShader(fShader);

	GLint status;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);
	checkError(status, "Failed to compile the vertex shader.");
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &status);
	checkError(status, "Failed to compile the fragment shader.");

	glLinkProgram(program);
	glUseProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	checkError(status, "Failed to link the shader program object.");
	std::cout << "Successfully Loaded " << vShaderFile << " " << fShaderFile << std::endl;
}