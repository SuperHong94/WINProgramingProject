#pragma once
#include <Windows.h>
#include <iostream>
#include "SoundManager.h"
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

	Boom_Sun = 0,
	MyDoughnut1,
	MyDoughnut2,
	MyDoughnut3,
	MyDoughnut4,
	MyRectangle,
	MyTriangle,
	Boom_Circle,
	Boom_Laser,
	Bullet_Up,
	Bullet_Down,
	Bullet_Right,
	Bullet_Left,
	Bullet_UpRight,
	Bullet_DownRight,
	Bullet_DownLeft,
	Bullet_UpLeft
};
enum EBoomStatus {
	noExplosion = 0,
	Explosion   //���� ������ �� �浹 üũ �� ����
};

struct Boom
{
	EShape boomShape;
	POINT leftTop;
	POINT rightBottom;
	Boom* nextBoom;

	int boomAnimaition;
	int width=100;
	int height;

	void setPosition();
};

void SunBoom_SJ(HDC hDC, Boom* head, int x, int y);
void CheckBullet(Boom* head);
void addBoom(Boom* head, EShape tmp_boomShape, int tmpLeftTop_x, int tmpLeftTop_y, int tmpRightBottom_x, int tmpRightBottom_y);
void deleteBoom(Boom* target);
void setBoomPosition(Boom* head);
void setAnimation(Boom* head);
void CircleBoom(HDC hDC, Boom* boom);
void LaserBoom(HDC hDC, Boom* boom);
void NormalBullet(HDC hDC, Boom* boom);
void printBoomAnimation(HDC hDC, Boom* head);
void Animation(HDC hDC);
void InitBoom(Boom& boom, int lX, int lY, int rX, int rY); //��ź �ʱ�ȭ �Լ�
bool Crush(RECT*, int LX, int LY, int RX, int RY); //�浹!!LY�� LeftY�� �ظ� plyaer�ϰ� ��ź�� ������ �浹ó���Ҳ���  //�浹�ϸ� true����
void DrawDie(RECT*);
void Doughnut(HDC hDC, Boom* head, int x, int y,int width);
bool OutOfRange(Boom* boom);

