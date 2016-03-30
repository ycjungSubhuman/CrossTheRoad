#include "shaderutil.h"
#include <stdlib.h>

static char* readShaderSource(const char* shaderFile) {
	/* reads glsl file and returns string of the source code */
	FILE* fp = fopen(shaderFile, "r");
	char* buf;
	long size;

	if (fp == NULL) return NULL;
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buf = (char*)malloc((size + 1) * sizeof(char));
	fread(buf, 1, size, fp);
	buf[size] = ' ';
	fclose(fp);
	return buf;
}