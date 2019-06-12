#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#include "SoundManager.h"
#include "resource.h"

extern int sj_Timer;
extern int PLAYER1_HIT;
extern int PLAYER2_HIT;
extern RECT Player_1;
extern RECT Player_2;
extern RECT WindowSize;
extern RECT Energybar;
extern HBITMAP Laser_Boom;
extern HBITMAP Circle_Boom;
extern HBITMAP Teleport;
extern HBITMAP Teleport2;
extern HBITMAP PLAYER_1;
extern HBITMAP PLAYER_2;
extern bool Tp;
extern bool Tp_2;
extern bool POWEROVERWHELMING;
extern RECT tmp;
extern RECT tmp2;
extern int score;

enum PLAYERDIRECTION {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UPRIGHT,
	UPLEFT,
	DOWNRIGHT,
	DOWNLEFT,
	STOP
};

extern PLAYERDIRECTION PLAYER1DR;
extern PLAYERDIRECTION PLAYER2DR;


enum EROUND {
	Round1,
	MAIN,
	HELP,
	Select,
	Round2,
	YouDie,
	YouWin
};
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
	Boom_Rectangle,
	Boom_Laser,
	Bullet_Up,
	Bullet_Down,
	Bullet_Right,
	Bullet_Left,
	Bullet_UpRight,
	Bullet_DownRight,
	Bullet_DownLeft,
	Bullet_UpLeft,
	Boom_LeftLaser,
	Boom_RightLaser,
	Boom_DownLaser,
	Boom_UpLaser,
	Boom_Laser2,
	Boom_Meet
};
enum EBoomStatus {
	noExplosion = 0,
	Explosion   //���� ������ �� �浹 üũ �� ����
};

struct Boom
{
	EShape boomShape;
	POINT leftTop{ 0 };
	POINT rightBottom{ 0 };
	Boom* nextBoom;

	int boomAnimaition;
	int width = 100;
	int height;

	void setPosition();
};

bool IsPointInCircle(int CenterX, int CenterY, int Radius, int X, int Y);
bool CircleCrush(RECT* player, int LX, int LY, int RX, int RY);
void SunBoom_SJ(HDC hDC, Boom* head, int x, int y);
void CheckBullet(Boom* head);
void CheckBoom(Boom* head);
void addBoom(Boom* head, EShape tmp_boomShape, int tmpLeftTop_x, int tmpLeftTop_y, int tmpRightBottom_x, int tmpRightBottom_y);
void deleteBoom(Boom* target);
void setBoomPosition(Boom* head);
void setAnimation(Boom* head);
void CircleBoom(HDC hDC, HINSTANCE g_hInst, Boom* boom);
void LaserBoom(HDC hDC, HINSTANCE g_hInst, Boom* boom);
void NormalBullet(HDC hDC, Boom* boom);
void printBoomAnimation(HDC hDC, HINSTANCE g_hInst, Boom* head);
void Animation(HDC hDC, HINSTANCE g_hInst, Boom* head, Boom* bullet_head);
void InitBoom(Boom& boom, int lX, int lY, int rX, int rY); //��ź �ʱ�ȭ �Լ�
bool Crush(RECT*, int LX, int LY, int RX, int RY); //�浹!!LY�� LeftY�� �ظ� plyaer�ϰ� ��ź�� ������ �浹ó���Ҳ���  //�浹�ϸ� true����
void DrawDie(RECT*);
void Doughnut(HDC hDC, Boom* head, int x, int y, int width);
bool OutOfRange(Boom* boom);
void DrawEnergybar(HDC hDC, HINSTANCE hInstance, EROUND&);
void CheckBulletCrush(Boom* head);
void CheckBoomCrush(Boom* head);
int DrawMenu(HDC hDC, EROUND& eRound, HINSTANCE hInst);
void ClickRange(LPARAM, EROUND&);
void MeetBoom(HDC, Boom*);
void SetUp(Boom* head, Boom* bullet_head);

