#include "GModel.h"

GModel::GModel(std::tuple<GLuint, double, double, double, int> data_models)
{
	this->data_models = data_models;
}

GLuint GModel::getModelID()
{
	return std::get<0>(data_models);
}

double GModel::getBoundboxX()
{
	return std::get<1>(data_models);
}

double GModel::getBoundboxY()
{
	return std::get<2>(data_models);
}

double GModel::getBoundboxZ()
{
	return std::get<3>(data_models);
}

int GModel::getVertexNumber()
{
	return std::get<4>(data_models);
}


