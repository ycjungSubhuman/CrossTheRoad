#pragma once
#include <GL/glew.h>
#include <stdio.h>

char* readShaderSource(const char* shaderFile);
void checkError(GLint status, const char* msg);
void loadShadersFromFile(const char* vShaderFile, const char* fShaderFile);
