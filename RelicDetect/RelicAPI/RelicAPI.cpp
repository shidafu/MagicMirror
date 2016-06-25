#pragma once
#include "RelicAPI.h"
RelicAPI::RelicAPI()
{
}

RelicAPI::~RelicAPI()
{
}
string RelicAPI::detect(Mat img)
{
	RelicScn scene;
	scene.Load_Img(img);

	return "";
}