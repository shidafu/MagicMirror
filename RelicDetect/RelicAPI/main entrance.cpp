// RelicAPI.cpp : 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "RelicAPI.h"

int main()
{
	//Mat img = cv::imread("test.jpg");
	//RelicAPI::detect(img);
	RelicAPI tt;
	ObjInfo a;
	a.name = "code";
	a.info = "beauty";
	a.year = "2016";
	std::vector<Point2f>corners(4);
	corners[0].x = 123.4;
	corners[0].y = 245.5;
	corners[1].x = 123.4;
	corners[1].y = 245.5;
	corners[2].x = 123.4;
	corners[2].y = 245.5;
	corners[3].x = 123.4;
	corners[3].y = 245.5;
	
	auto b = tt.Convert_info_to_Json(a,corners);
    return 0;
}

