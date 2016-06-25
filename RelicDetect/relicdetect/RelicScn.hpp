#pragma once
#ifndef RELIC
#define RELIC
#endif 
#include "RelicDetect.hpp"
#include "RelicObj.hpp"
class RelicScn :public RelicDetect
{
public:
	//************************************
	// Method:    Match_an_Obj
	// Returns:   bool
	// Parameter: RelicObj obj	待匹配的对象，需要经过
	// 说明:		  匹配一个目标
	//************************************
	bool RelicScn::Match_an_Obj(RelicObj obj);
	//************************************
	// Method:    Match_an_Obj
	// Returns:   bool
	// Parameter: RelicObj obj
	// Parameter: std::vector<Point2f> & corners
	// 说明:		  匹配的同时返回角标
	//************************************
	bool Match_an_Obj(RelicObj obj, std::vector<Point2f> & corners);
	//************************************
	// Method:    Draw_Obj
	// Returns:   void
	// 说明:		  绘制匹配成功的目标对象
	//************************************
	void RelicScn::Draw_Obj();
private:
	std::vector<Point2f> corners;
};

