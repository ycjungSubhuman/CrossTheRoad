#pragma once
#include "GModel.h"
#include <map>
#include <tuple>
#include <string>
#include <GL/glew.h>
/* loads 3d Models and stores. */
class ModelManager {
private:
	std::map<std::string,GModel*> data_models;
public:
	void loadModelFromFile(std::string name_file);
	void loadTextureFromFile(std::string name_group, GModel::TextureType type, std::string name_file);
	GModel* getModel(std::string name_group);
	vec3 getGlobalPos(std::string name_group);
	vec3 getRelativePos(std::string child, std::string parent);
	~ModelManager();
};