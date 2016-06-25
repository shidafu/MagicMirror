// RelicAPI.cpp : 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "RelicAPI.h"

int main()
{
	Mat img = cv::imread("test.jpg");
	RelicAPI::detect(img);
    return 0;
}

