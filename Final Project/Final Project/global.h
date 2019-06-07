#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#include "SoundManager.h"
#include "resource.h"
extern int sj_Timer;
extern RECT Player_1;
extern RECT WindowSize;
enum ETURNN {
	turn0 = 0,
	turn1, turn2, turn3, turn4, turn5
};
enum EShape {
	MyCircle = 0,
	MyRectangle,
	MyTriangle
};
enum EBoomStatus {
	noExplosion = 0,
	Explosion   //폭발 상태일 때 충돌 체크 할 꺼임
};
struct Boom
{
	EShape boomShape=MyCircle;
	POINT leftTop;
	POINT rightBottom;
	int boomAnimaition = 0;
	int width;
	int height;

};
void InitBoom(Boom& boom, int lX, int lY, int rX, int rY); //폭탄 초기화 함수
bool Crush(RECT*, int LX, int LY, int RX, int RY); //충돌!!LY는 LeftY의 준말 plyaer하고 폭탄의 범위랑 충돌처리할꺼임  //충돌하면 true리턴
void DrawDie(RECT*);
void Doughnut(HDC hDC,HINSTANCE hInstance);
void SunBoom_SJ(HDC hDC, Boom boom);
void CircleBoom(HDC hDC, Boom boom);
void LaserBoom(HDC hDC, Boom boom);
