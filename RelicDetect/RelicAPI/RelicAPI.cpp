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
	vector<RelicObj> objs(3);
	for (int i = 0;i < objs.size();i++)
	{
		scene.Match_an_Obj(objs[i]);
	}
	return "";
}