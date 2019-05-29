#pragma once
#include <Windows.h>
#include <iostream>
extern int sj_Timer;
enum EShape {
	MyCircle=0,
	MyRectangle,
	MyTriangle
};
struct Boom
{
	EShape boomShape;
	POINT rightTop;
	POINT leftBottom;
	int width;

};
void SunBoom_SJ(HDC hDC,Boom* boom);