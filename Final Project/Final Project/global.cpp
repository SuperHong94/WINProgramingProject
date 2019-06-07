#include "global.h"

int sj_Timer = 0;

void addBoom(Boom* head, EShape tmp_boomShape, int tmpLeftTop_x, int tmpLeftTop_y, int tmpRightBottom_x, int tmpRightBottom_y)
{
	Boom* p = new Boom;
	p->nextBoom = head->nextBoom;
	p->boomShape = tmp_boomShape;
	p->leftTop.x = tmpLeftTop_x;
	p->leftTop.y = tmpLeftTop_y;
	p->rightBottom.x = tmpRightBottom_x;
	p->rightBottom.y = tmpRightBottom_y;
	p->boomAnimaition = 0;
	p->width = p->rightBottom.x - p->leftTop.x;
	head->nextBoom = p;
}

void deleteBoom(Boom* target)
{
	Boom* Delete = target->nextBoom;

	target->nextBoom = Delete->nextBoom;

	free(Delete);
}

void setBoomPosition(Boom* head)
{
	Boom* p;

	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{
		p->nextBoom->setPosition();
	}
}

void setAnimation(Boom* head)
{
	Boom* p;

	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{
		p->nextBoom->boomAnimaition++;
		p->nextBoom->boomAnimaition %= 5;
	}
}

void Boom::setPosition()
{
	{
		switch (boomShape)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:
			if (boomAnimaition == 0)
			{
				leftTop.x = 50;
				leftTop.y = 50;
				rightBottom.x = 150;
				rightBottom.y = 150;
			}

			else if (boomAnimaition == 1)
			{
				leftTop.x -= 25;
				leftTop.y -= 25;
				rightBottom.x += 25;
				rightBottom.y += 25;
			}

			else if (boomAnimaition == 3)
			{
				leftTop.x += 50;
				leftTop.y += 50;
				rightBottom.x -= 50;
				rightBottom.y -= 50;
			}
			break;
		case 4:
			if (boomAnimaition == 0)
			{
				leftTop.x = 0;
				leftTop.y = 400;
				rightBottom.x = 1200;
				rightBottom.y = 450;
			}

			else if (boomAnimaition == 1)
			{
				leftTop.y -= 10;
				rightBottom.y += 10;
			}
			else if (boomAnimaition == 3)
			{
				leftTop.y += 15;
				rightBottom.y -= 15;
			}
			break;
		default:

			break;
		}
	}
}

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

void CircleBoom(HDC hDC, Boom* boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	switch (boom->boomAnimaition % 5)
	{
	case 0:
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		break;
	case 1:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 2:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 3:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 4:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	default:

		break;
	}
}

void LaserBoom(HDC hDC, Boom* boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	switch (boom->boomAnimaition % 5)
	{
	case 0:
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		break;
	case 1:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 2:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 3:
		hBrush = CreateSolidBrush(RGB(255, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	case 4:
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		break;
	default:

		break;
	}
}

void printBoomAnimation(HDC hDC, Boom* head)
{
	Boom* p;

	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{
		switch (p->nextBoom->boomShape)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:
			CircleBoom(hDC, p->nextBoom);
			break;
		case 4:
			LaserBoom(hDC, p->nextBoom);
			break;
		default:
			break;
		}
	}
}

void Animation(HDC hDC)
{

}
