#include "shaderutil.h"
#include <iostream>
#include <stdlib.h>

#define BUFFER_OFFSET( offset ) ((GLvoid*)(offset))

GLuint program;
GLint u_Model, u_Projection, color_in;
GLuint rectbuffer;

static char* readShaderSource(const char* shaderFile) {
	/* reads glsl file and returns string of the source code */
	FILE* fp;
	fopen_s(&fp, shaderFile, "rb");
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
static void checkError(GLint status, const char* msg) {
	if (status != GL_TRUE) {
		std::cout << msg << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
}
static void validateShader(GLint shader) {
	/* Checks if the shader is successfully compiled */
	/* if not, print error messages */
	//get compilation results
	GLint status;
	GLint logSize = 0;
	GLchar* infoLog;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
	infoLog = (GLchar*)malloc(logSize*sizeof(GLchar));
	glGetShaderInfoLog(shader, 1024, &logSize, infoLog);
	printf("%s", infoLog);
	printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	free(infoLog);
	checkError(status, "Failed to compile the vertex shader.");
}
void loadShadersFromFile(const char* vShaderFile, const char* fShaderFile) {
	/* loads shader from given file name. */
	GLchar *vSource, *fSource;

	vSource = readShaderSource(vShaderFile);
	if (vSource == NULL) {
		std::cout << "failed to read default vertex shader" << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	fSource = readShaderSource(fShaderFile);
	if (fSource == NULL) {
		std::cout << "failed to read default fragment shader" << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	/*GLuint program;*/
	program = glCreateProgram();

	GLuint vShader, fShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	glShaderSource(vShader, 1, (const GLchar**)&vSource, NULL);
	glShaderSource(fShader, 1, (const GLchar**)&fSource, NULL);

	glCompileShader(vShader);
	glCompileShader(fShader);

	validateShader(vShader);
	validateShader(fShader); 

	glLinkProgram(program);
	glUseProgram(program);



	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, NULL);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, 0, 0, NULL);

	u_Model = glGetUniformLocation(program, "u_Model");
	u_Projection = glGetUniformLocation(program, "u_Projection");
	color_in = glGetUniformLocation(program, "color_in");

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	checkError(status, "Failed to link the shader program object.");
	std::cout << "Successfully Loaded " << vShaderFile << " " << fShaderFile << std::endl;
}
