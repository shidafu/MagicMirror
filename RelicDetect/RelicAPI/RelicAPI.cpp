#pragma once
#include "RelicAPI.h"
RelicAPI::RelicAPI()
{
}

RelicAPI::~RelicAPI()
{
}
string RelicAPI::detect(Mat img,vector<pair<RelicObj, ObjInfo>>& objs)
{
	RelicScn scene;
	scene.Load_Img(img);
	pair<RelicObj, ObjInfo> test;
	//vector<pair<RelicObj, ObjInfo>> objs(3);//get obj from mysql
	for (int i = 0;i < objs.size();i++)
	{
		std::vector<Point2f> corners;
		scene.Calc_Keypoints_and_Descriptors();
		bool matched = scene.Match_an_Obj(objs[i].first,corners);
		if (matched)
		{
			return Convert_info_to_Json(objs[i].second,corners);
		}
	}
	Json::Value root;

	root["detect"] = false;
	Json::FastWriter writer;
	return writer.write(root);
}
string RelicAPI::Convert_info_to_Json(ObjInfo obj_info, std::vector<Point2f>corners)
{
	Json::Value root;
	//set size node////////////////////////////////////////////////////////////////////////
	root["info"] = obj_info.info;
	root["name"] = obj_info.name;
	root["year"] = obj_info.year;
	root["detect"] = true;
	Json::Value A, B, C, D;
	//set corners
	A["x"] = corners[0].x;
	A["y"] = corners[0].y;
	B["x"] = corners[1].x;
	B["y"] = corners[1].y;
	C["x"] = corners[2].x;
	C["y"] = corners[2].y;
	D["x"] = corners[3].x;
	D["y"] = corners[3].y;
	Json::Value coordinates;
	coordinates["A"] = A;
	coordinates["B"] = B;
	coordinates["C"] = C;
	coordinates["D"] = D;
	root["coordinates"] = coordinates;
	//root.toStyledString();
	std::string out = root.toStyledString();
	std::cout << out << std::endl;
	Json::FastWriter writer;
	return writer.write(root);
}