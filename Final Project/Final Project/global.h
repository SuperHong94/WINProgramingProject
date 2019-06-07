#pragma once
#include <Windows.h>
#include <iostream>
#include "SoundManager.h"
extern int sj_Timer;
enum EShape {
	MyCircle=0,
	MyRectangle,
	MyTriangle
};
enum EBoomStatus {
	noExplosion=0,
	Explosion   //���� ������ �� �浹 üũ �� ����
};
struct Boom
{
	EShape boomShape;
	POINT rightTop;
	POINT leftBottom;
	int boomAnimaition;
	int width;

};
void SunBoom_SJ(HDC hDC,Boom* boom);
void CircleBoom(HDC hDC, Boom boom);
void LaserBoom(HDC hDC, Boom boom);