#include "global.h"

int sj_Timer = 0;

void SunBoom_SJ(HDC hDC, Boom* boom)
{
	HBRUSH hBrush;  //색깔
	boom->leftTop.x = 200;
	boom->leftTop.y = 200;
	boom->width = 100;
	boom->boomShape = MyCircle;
	int x = boom->leftTop.x;
	int y = boom->leftTop.y;
	int width = boom->width;
	switch (boom->boomShape) {
	case MyCircle:
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		(HBRUSH)SelectObject(hDC, hBrush);
		if (sj_Timer%10==9) {
			Ellipse(hDC, x + width / 4, y - width / 4, x + (width*0.75), y + width / 4); //원상단에 그리기 테스트용임
		}
		else
			Ellipse(hDC, x, y, x + width, y + width);

		DeleteObject(hBrush);
	}
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
		Ellipse(hDC, boom.leftTop.x, boom.rightBottom.y, boom.rightBottom.x, boom.leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		break;
	case 1:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.leftTop.x, boom.rightBottom.y, boom.rightBottom.x, boom.leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 2:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.leftTop.x, boom.rightBottom.y, boom.rightBottom.x, boom.leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 3:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.leftTop.x, boom.rightBottom.y, boom.rightBottom.x, boom.leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 4:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.leftTop.x, boom.rightBottom.y, boom.rightBottom.x, boom.leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	default:

		break;
	}
}

void LaserBoom_Horizontal(HDC hDC, Boom boom)
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
		Rectangle(hDC, boom.leftTop.x, boom.rightBottom.y, boom.rightBottom.x, boom.leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		break;
	case 1:
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom.leftTop.x, boom.rightBottom.y + 10, boom.rightBottom.x, boom.leftTop.y - 10);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		break;
	case 2:
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom.leftTop.x, boom.rightBottom.y + 10, boom.rightBottom.x, boom.leftTop.y - 10);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		break;
	case 3:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.leftTop.x, boom.rightBottom.y - 15, boom.rightBottom.x, boom.leftTop.y + 15);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 4:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom.leftTop.x, boom.rightBottom.y - 15, boom.rightBottom.x, boom.leftTop.y + 15);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	default:

		break;
	}
}