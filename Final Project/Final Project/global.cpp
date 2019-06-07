#include "global.h"

int sj_Timer = 0;
RECT Player_1;
RECT WindowSize;
bool Crush(RECT* player, int LX, int LY, int RX, int RY) //�浹!!LY�� LeftY�� �ظ� plyaer�ϰ� ��ź�� ������ �浹ó���Ҳ���  //�浹�ϸ� true����
{
	int playerWidth = (player->bottom - player->top) / 2;  //���̱��ؼ� 2�� ���� player������ǥ���ҷ����ϴ°���
	int playerX = player->left + playerWidth; //player�� ����X��ǥ
	int playerY = player->top + playerWidth;      //plyaer�� ���� Y��ǥ
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
void SunBoom_SJ(HDC hDC, Boom boom)
{

	HBRUSH hBrush;  //����
	static bool ff = true;  //�迭 �ѹ��� ���Է� �������� �־��� �Լ��������뿡 flas�� �ٲ�
	boom.width = 10;
	boom.boomShape = MyCircle;
	static int x[8];
	static int y[8];
	if (ff)
		for (int i = 0; i < 8; i++) {
			x[i] = boom.leftTop.x;
			y[i] = boom.leftTop.y;

		}
	if (y[2] >= 1000)  //�ȱ׸��� ����  //y2�� �������� ���� �Ѿ���
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
	x[0]++; y[0] = y[0];  //����
	x[1]--; y[1] = y[1];  //����
	x[2] = x[2]; y[2]++; //��
	x[3] = x[3]; y[3]--; //��
	x[4]++; y[4]--;  //�ϵ�
	x[5]--; y[5]--;  //�ϼ�
	x[6]--; y[6]++;  //����
	x[7]++; y[7]++;//����
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
