#pragma once
#include <Windows.h>
#include <iostream>
#include "SoundManager.h"

extern int sj_Timer;
enum EShape {
	MyCircle=0,
	MyRectangle,
	MyTriangle,
	Boom_Circle,
	Boom_Laser
};
enum EBoomStatus {
	noExplosion=0,
	Explosion   //폭발 상태일 때 충돌 체크 할 꺼임
};

struct Boom
{
	EShape boomShape;
	POINT leftTop;
	POINT rightBottom;
	Boom* nextBoom;

	int boomAnimaition;
	int width;

	void setPosition();
};

void addBoom(Boom* head, EShape tmp_boomShape, int tmpLeftTop_x, int tmpLeftTop_y, int tmpRightBottom_x, int tmpRightBottom_y);
void deleteBoom(Boom* target);
void setBoomPosition(Boom* head);
void setAnimation(Boom* head);
void SunBoom_SJ(HDC hDC,Boom* boom);
void CircleBoom(HDC hDC, Boom* boom);
void LaserBoom(HDC hDC, Boom* boom);
void printBoomAnimation(HDC hDC, Boom* head);
void Animation(HDC hDC);