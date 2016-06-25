#pragma once
#include "RelicObj.hpp"
#include "RelicScn.hpp"
struct ObjInfo
{
	string info;
	string name;
	string year;
};
class RelicAPI
{
public:
	RelicAPI();
	~RelicAPI();
	static string detect(Mat img);
	static	string Convert_info_to_Json(ObjInfo obj_info, std::vector<Point2f>corners);
};

