#pragma once
#include <Windows.h>
#include <iostream>
<<<<<<< HEAD
#include "SoundManager.h"
=======
>>>>>>> parent of b1bc396... 진짜 뭐가문제냐
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
	Explosion   //���� ������ �� �浹 üũ �� ����
};

struct Boom
{
	EShape boomShape;
<<<<<<< HEAD
	POINT leftTop;
	POINT rightBottom;
	Boom* nextBoom;

=======
	POINT rightTop;
	POINT leftBottom;
>>>>>>> parent of b1bc396... 진짜 뭐가문제냐
	int boomAnimaition;
	int width;

	void setPosition();
};
<<<<<<< HEAD

void addBoom(Boom* head, EShape tmp_boomShape, int tmpLeftTop_x, int tmpLeftTop_y, int tmpRightBottom_x, int tmpRightBottom_y);
void deleteBoom(Boom* target);
void setBoomPosition(Boom* head);
void setAnimation(Boom* head);
void CircleBoom(HDC hDC, Boom* boom);
void LaserBoom(HDC hDC, Boom* boom);
void printBoomAnimation(HDC hDC, Boom* head);
void Animation(HDC hDC);
void InitBoom(Boom& boom, int lX, int lY, int rX, int rY); //��ź �ʱ�ȭ �Լ�
bool Crush(RECT*, int LX, int LY, int RX, int RY); //�浹!!LY�� LeftY�� �ظ� plyaer�ϰ� ��ź�� ������ �浹ó���Ҳ���  //�浹�ϸ� true����
void DrawDie(RECT*);
void Doughnut(HDC hDC, HINSTANCE hInstance);
void SunBoom_SJ(HDC hDC, Boom boom);
=======
void SunBoom_SJ(HDC hDC,Boom* boom);
void CircleBoom(HDC hDC, Boom boom);
void LaserBoom(HDC hDC, Boom boom);
>>>>>>> parent of b1bc396... 진짜 뭐가문제냐
