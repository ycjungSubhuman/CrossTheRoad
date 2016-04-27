#include "GModel.h"

GModel::GModel(std::tuple<GLuint, double, double, double, int> data_models)
{
	this->data_model = data_models;
}

GLuint GModel::getModelID()
{
	return std::get<0>(data_model);
}

double GModel::getBoundboxX()
{
	return std::get<1>(data_model);
}

double GModel::getBoundboxY()
{
	return std::get<2>(data_model);
}

double GModel::getBoundboxZ()
{
	return std::get<3>(data_model);
}

int GModel::getVertexSize()
{
	return std::get<4>(data_model);
}


