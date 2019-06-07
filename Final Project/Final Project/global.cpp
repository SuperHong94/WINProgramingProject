#include "global.h"
int sj_Timer = 0;
RECT Player_1;
RECT WindowSize;
bool Crush(RECT* player, int LX, int LY, int RX, int RY) //충돌!!LY는 LeftY의 준말 plyaer하고 폭탄의 범위랑 충돌처리할꺼임  //충돌하면 true리턴
{
	int playerWidth = (player->bottom - player->top) / 2;  //높이구해서 2로 나눔 player중점좌표구할려고하는거임
	int playerX = player->left + playerWidth; //player의 중점X좌표
	int playerY = player->top + playerWidth;      //plyaer의 중점 Y좌표
	int boomLX = LX - playerWidth;
	int boomLY = LY - playerWidth;
	int boomRX = playerWidth + RX;
	int boomRY = RY + playerWidth;
	if ((playerX >= boomLX && playerX <= boomRX) && (playerY >= boomLY && playerY <= boomRY))
		return true;
	else
		return false;

}
void InitBoom(Boom& boom, int lX, int lY, int rX, int rY)
{
	boom.leftTop.x = lX;
	boom.leftTop.y = lY;
	boom.rightBottom.x = rX;
	boom.rightBottom.y = rY;
}
void SunBoom_SJ(HDC hDC, Boom boom)
{

	HBRUSH hBrush;  //색깔
	static bool ff = true;  //배열 한번만 값입력 받을려고 넣었음 함수끝날때쯤에 flas로 바뀜
	boom.width = 10;
	boom.boomShape = MyCircle;
	static int x[8];
	static int y[8];
	if (ff)
		for (int i = 0; i < 8; i++) {
			x[i] = boom.leftTop.x;
			y[i] = boom.leftTop.y;

		}
	if (y[2] >= 1000)  //안그리는 조건  //y2는 남쪽으로 방향 총알임
		return;
	static int width = boom.width;

	switch (boom.boomShape) {
	case MyCircle:
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		(HBRUSH)SelectObject(hDC, hBrush);
		for (int i = 0; i < 8; i++) {
			Ellipse(hDC, x[i], y[i], x[i] + width, y[i] + width);
		}


		for (int i = 0; i < 8; i++) {
			if (Crush(&Player_1, x[i], y[i], x[i] + width, y[i] + width))
				Ellipse(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);
		}
		DeleteObject(hBrush);
		break;
	}
	ff = false;
	x[0]++; y[0] = y[0];  //동쪽
	x[1]--; y[1] = y[1];  //서쪽
	x[2] = x[2]; y[2]++; //남
	x[3] = x[3]; y[3]--; //북
	x[4]++; y[4]--;  //북동
	x[5]--; y[5]--;  //북서
	x[6]--; y[6]++;  //남서
	x[7]++; y[7]++;//남동
}

void CircleBoom(HDC hDC, Boom boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	switch (boom.boomAnimaition % 5)
	{
	case 0:
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.rightBottom.x, boom.leftTop.y, boom.leftTop.x, boom.rightBottom.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		break;
	case 1:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.rightBottom.x, boom.leftTop.y, boom.leftTop.x, boom.rightBottom.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 2:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.rightBottom.x, boom.leftTop.y, boom.leftTop.x, boom.rightBottom.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 3:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.rightBottom.x, boom.leftTop.y, boom.leftTop.x, boom.rightBottom.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 4:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.rightBottom.x, boom.leftTop.y, boom.leftTop.x, boom.rightBottom.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	default:

		break;
	}
}

void LaserBoom(HDC hDC, Boom boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

}

void Doughnut(HDC hDC, HINSTANCE hInstance)
{
	HDC mDC;
	HBRUSH hBrush, oldBrush;
	HBITMAP hBitmap;
	hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	mDC = CreateCompatibleDC(hDC);
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	static int x = (int)WindowSize.right / 2;
	static int y = (int)WindowSize.bottom / 2;

	static int width = 100;

	if (width + x >= 1000)
		return;
	Rectangle(hDC, x, y, x + width, y + 20);
	Rectangle(hDC, x, y, x + 20, y + width);
	Rectangle(hDC, x, y + width - 20, x + width, y + width);
	Rectangle(hDC, x + width - 20, y, x + width, y + width);
	(HBRUSH)SelectObject(hDC, oldBrush);
	if (Crush(&Player_1, x, y, x + width, y + 20)) {
		Ellipse(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);
	}
	if (Crush(&Player_1, x, y, x + 20, y + width))
		Ellipse(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);
	if (Crush(&Player_1, x, y + width - 20, x + width, y + width))
		Ellipse(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);
	if (Crush(&Player_1, x + width - 20, y, x + width, y + width))
		Ellipse(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);

	x--;
	y--;
	width += 2;
	DeleteObject(hBrush);
}