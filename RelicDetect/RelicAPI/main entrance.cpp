// RelicAPI.cpp : �������̨Ӧ�ó������ڵ㡣
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

