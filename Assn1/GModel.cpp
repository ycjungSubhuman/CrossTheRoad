#include "GModel.h"

GModel::GModel(std::tuple<GLuint, vec3, vec3, int> data_models)
{
	this->data_model = data_models;
}

GLuint GModel::getModelID()
{
	return std::get<0>(data_model);
}

double GModel::getMinX()
{
	return std::get<1>(data_model).x;
}

double GModel::getMinY()
{
	return std::get<1>(data_model).y;
}

double GModel::getMinZ()
{
	return std::get<1>(data_model).z;
}
double GModel::getBoundboxX()
{
	return std::get<2>(data_model).x;
}

double GModel::getBoundboxY()
{
	return std::get<2>(data_model).y;
}

double GModel::getBoundboxZ()
{
	return std::get<2>(data_model).z;
}

int GModel::getVertexSize()
{
	return std::get<3>(data_model);
}


