#pragma once
#include <GL/glew.h>
#include <stdio.h>

static char* readShaderSource(const char* shaderFile);
static void checkError(GLint status, const char* msg);
static void validateShader(GLint shader);
void loadShadersFromFile(const char* vShaderFile, const char* fShaderFile);
