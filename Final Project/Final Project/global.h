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
	Explosion   //���� ������ �� �浹 üũ �� ����
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
void InitBoom(Boom& boom, int lX, int lY, int rX, int rY); //��ź �ʱ�ȭ �Լ�
bool Crush(RECT*, int LX, int LY, int RX, int RY); //�浹!!LY�� LeftY�� �ظ� plyaer�ϰ� ��ź�� ������ �浹ó���Ҳ���  //�浹�ϸ� true����
void DrawDie(RECT*);
void Doughnut(HDC hDC,HINSTANCE hInstance);
void SunBoom_SJ(HDC hDC, Boom boom);
void CircleBoom(HDC hDC, Boom boom);
void LaserBoom(HDC hDC, Boom boom);
