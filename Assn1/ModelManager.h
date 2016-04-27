#pragma once
#include <map>
#include <tuple>
#include <string>
#include <GL/glew.h>
/* loads 3d Models and stores. */
class ModelManager {
private:
	std::map<std::string, std::tuple<GLuint, double, double, double, int>> data_models;
public:
	static std::map<std::string, std::tuple<GLuint,double,double,double,int>> loadModelFromFile(std::string name_file);
};