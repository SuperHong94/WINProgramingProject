#include "global.h"

int sj_Timer = 0;
RECT Player_1;
RECT WindowSize;
RECT Energybar;
HBITMAP Laser_Boom;
HBITMAP Circle_Boom;

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
bool OutOfRange(Boom* boom)
{
	if (boom == NULL)
		return FALSE;

	if (boom->leftTop.x < WindowSize.right && boom->rightBottom.x > WindowSize.left &&
		boom->leftTop.y < WindowSize.bottom && boom->rightBottom.y > WindowSize.top)
		return FALSE;

	else
		return TRUE;
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
	head->nextBoom = p;
}

void SunBoom_SJ(HDC hDC, Boom* head, int x, int y)
{
	addBoom(head, Bullet_Down, x - 10, y - 10, x + 10, y + 10);
	addBoom(head, Bullet_Right, x - 10, y - 10, x + 10, y + 10);
	addBoom(head, Bullet_Left, x - 10, y - 10, x + 10, y + 10);
	addBoom(head, Bullet_Up, x - 10, y - 10, x + 10, y + 10);
	addBoom(head, Bullet_UpRight, x - 10, y - 10, x + 10, y + 10);
	addBoom(head, Bullet_UpLeft, x - 10, y - 10, x + 10, y + 10);
	addBoom(head, Bullet_DownLeft, x - 10, y - 10, x + 10, y + 10);
	addBoom(head, Bullet_DownRight, x - 10, y - 10, x + 10, y + 10);
}

void Doughnut(HDC hDC, Boom* head, int x, int y, int width)
{

	addBoom(head, MyDoughnut1, x, y, x + width, y + 20);
	addBoom(head, MyDoughnut2, x, y, x + 20, y + width);
	addBoom(head, MyDoughnut3, x, y + width - 20, x + width, y + width);
	addBoom(head, MyDoughnut4, x + width - 20, y, x + width, y + width);
}

void NormalBullet(HDC hDC, Boom* boom)
{
	if (boom == NULL)
		return;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hDC, hPen);
	switch (boom->boomShape) {
		//case Boom_Sun:
		//	Ellipse(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x, boom->rightBottom.y);
		//	break;
	case MyDoughnut1:
	case MyDoughnut2:
	case MyDoughnut3:
	case MyDoughnut4:
		Rectangle(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x, boom->rightBottom.y);
		
		break;
	case Bullet_Up:
		Ellipse(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x, boom->rightBottom.y);
		break;
	case Bullet_Down:
	case Bullet_Right:
	case Bullet_Left:
	case Bullet_UpRight:
	case Bullet_UpLeft:
	case Bullet_DownRight:
	case Bullet_DownLeft:
		Ellipse(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x, boom->rightBottom.y);
		
		break;
	}
	(HPEN)SelectObject(hDC, oldPen);
	DeleteObject(hPen);
	(HBRUSH)SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
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
		if (p->nextBoom->boomAnimaition != -1)
			p->nextBoom->boomAnimaition++;
	}
}

void Boom::setPosition()
{
	switch (boomShape)
	{
	case Boom_Sun:

		break;
	case MyDoughnut1:
		leftTop.x--;
		leftTop.y--;
		rightBottom.x++;
		rightBottom.y--;
		break;
	case MyDoughnut2:
		leftTop.x--;
		leftTop.y--;
		rightBottom.x--;
		rightBottom.y++;
		break;
	case MyDoughnut3:
		leftTop.x--;
		leftTop.y++;
		rightBottom.x++;
		rightBottom.y++;
		break;
	case MyDoughnut4:
		leftTop.x++;
		leftTop.y--;
		rightBottom.x++;
		rightBottom.y++;
		break;

	case MyRectangle:

		break;
	case MyTriangle:

		break;
	case Boom_Circle:
		if (boomAnimaition == 100)
		{
			leftTop.x -= 25;
			leftTop.y -= 25;
			rightBottom.x += 25;
			rightBottom.y += 25;
		}

		else if (boomAnimaition > 100)
		{
			leftTop.x += 10;
			leftTop.y += 10;
			rightBottom.x -= 10;
			rightBottom.y -= 10;
			if (leftTop.x >= rightBottom.x)
				boomAnimaition = -1;
		}
		break;
	case Boom_Laser:
		if (boomAnimaition == 100)
		{
			leftTop.y -= 25;
			rightBottom.y += 25;
		}
		else if (boomAnimaition > 100)
		{
			leftTop.y += 2;
			rightBottom.y -= 2;
			if (leftTop.y >= rightBottom.y)
				boomAnimaition = -1;
		}
		break;
	case Bullet_Up:
		leftTop.y -= 3;
		rightBottom.y -= 3;
		break;
	case Bullet_Down:
		leftTop.y += 3;
		rightBottom.y += 3;
		break;
	case Bullet_Right:
		leftTop.x += 3;
		rightBottom.x += 3;
		break;
	case Bullet_Left:
		leftTop.x -= 3;
		rightBottom.x -= 3;
		break;
	case Bullet_UpRight:
		leftTop.y -= 3;
		leftTop.x += 3;
		rightBottom.x += 3;
		rightBottom.y -= 3;
		break;
	case Bullet_UpLeft:
		leftTop.y -= 3;
		rightBottom.y -= 3;
		leftTop.x -= 3;
		rightBottom.x -= 3;
		break;
	case Bullet_DownRight:
		leftTop.y += 3;
		rightBottom.y += 3;
		leftTop.x += 3;
		rightBottom.x += 3;
		break;
	case Bullet_DownLeft:
		leftTop.y += 3;
		rightBottom.y += 3;
		leftTop.x -= 3;
		rightBottom.x -= 3;
		break;
	case Boom_Laser2:
		if (boomAnimaition == 100)
		{
			leftTop.x -= 25;
			rightBottom.x += 25;
		}
		else if (boomAnimaition > 100)
		{
			leftTop.x += 2;
			rightBottom.x -= 2;
			if (leftTop.x >= rightBottom.x)
				boomAnimaition = -1;
		}
		break;
	default:

		break;
	}
}


void CircleBoom(HDC hDC, HINSTANCE g_hInst,Boom* boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	HDC memDC;

	if (boom->boomAnimaition < 100)
	{
		memDC = CreateCompatibleDC(hDC);
		(HBITMAP)SelectObject(memDC, Circle_Boom);
		TransparentBlt(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x - boom->leftTop.x, boom->rightBottom.y - boom->leftTop.y, memDC, 0, 0, 1024, 1024, RGB(0, 0, 0));
		DeleteDC(memDC);
	}

	else
	{
		switch (boom->boomAnimaition % 2)
		{
		case 0:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		}
	}
}

void LaserBoom(HDC hDC, HINSTANCE g_hInst, Boom* boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	HDC memDC;


	if (boom->boomAnimaition < 100)
	{
		memDC = CreateCompatibleDC(hDC);
		(HBITMAP)SelectObject(memDC, Laser_Boom);
		TransparentBlt(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x - boom->leftTop.x, boom->rightBottom.y - boom->leftTop.y, memDC, 0, 0, 1024, 1024, RGB(0, 0, 0));
		DeleteDC(memDC);
	}
	else
	{
		switch (boom->boomAnimaition % 2)
		{
		case 0:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Rectangle(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x, boom->rightBottom.y);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Rectangle(hDC, boom->leftTop.x, boom->leftTop.y, boom->rightBottom.x, boom->rightBottom.y);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		}
	}
}

void printBoomAnimation(HDC hDC, HINSTANCE g_hInst, Boom* head)
{
	Boom* p;

	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{
		switch (p->nextBoom->boomShape)
		{
		case 0:
			break;
		case MyDoughnut1:
		case MyDoughnut2:
		case MyDoughnut3:
		case MyDoughnut4:
			NormalBullet(hDC, p->nextBoom);
			break;
		case Boom_Circle:
			CircleBoom(hDC, g_hInst, p->nextBoom);
			break;
		case Bullet_Up:
		case Bullet_Down:
		case Bullet_Right:
		case Bullet_Left:
		case Bullet_UpRight:
		case Bullet_DownRight:
		case Bullet_DownLeft:
		case Bullet_UpLeft:
			NormalBullet(hDC, p->nextBoom);
			break;
		case Boom_Laser:
		case Boom_Laser2:
			LaserBoom(hDC, g_hInst, p->nextBoom);
			break;
		default:
			break;
		}
	}
}

void CheckBullet(Boom* head)
{
	Boom* p;
	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{
		
		while (OutOfRange(p->nextBoom))
		{
			deleteBoom(p);
			if (p->nextBoom == NULL)
				break;
		}
		if (p->nextBoom == NULL)
			break;
	}
}

void CheckBoom(Boom* head)
{
	Boom* p;

	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{

		if (p->nextBoom->boomShape >= 1 && p->nextBoom->boomShape <= 4)
		{
			while (OutOfRange(p->nextBoom))
			{
				deleteBoom(p);
				if (p->nextBoom == NULL)
					break;
			}
		}
		else
		{
			while (p->nextBoom->boomAnimaition == -1)
			{
				deleteBoom(p);
				if (p->nextBoom == NULL)
					break;
			}
		}


		if (p->nextBoom == NULL)
			break;
	}
}

void Animation(HDC hDC, HINSTANCE g_hInst, Boom* head, Boom* bullet_head)
{
	HDC memDC;
	HBITMAP Character;

	Character = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_PLAYER));

	printBoomAnimation(hDC, g_hInst, head);
	printBoomAnimation(hDC, g_hInst, bullet_head);

	memDC = CreateCompatibleDC(hDC);
	(HBITMAP)SelectObject(memDC, Character);
	StretchBlt(hDC, Player_1.left, Player_1.top, Player_1.right - Player_1.left, Player_1.bottom - Player_1.top, memDC, 0, 0, 50, 50, SRCCOPY);
	DeleteObject(Character);
	DeleteDC(memDC);
}

void DrawEnergybar(HDC hDC)
{
	HBRUSH hBrush, hBrush1;
	hBrush = CreateSolidBrush(RGB(100, 100, 100));
	hBrush1 = CreateSolidBrush(RGB(0, 0, 100));
	(HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, WindowSize.left, WindowSize.bottom - 20, WindowSize.right, WindowSize.bottom);
	(HBRUSH)SelectObject(hDC, hBrush1);
	Rectangle(hDC, Energybar.left, Energybar.bottom - 20, Energybar.right, Energybar.bottom);
	DeleteObject(hBrush);
	DeleteObject(hBrush1);
}

void CheckBulletCrush(Boom* head)
{
	Boom* p;

	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{
		if (Crush(&Player_1, p->nextBoom->leftTop.x, p->nextBoom->leftTop.y, p->nextBoom->rightBottom.x, p->nextBoom->rightBottom.y))
			Energybar.right -= 10;
	}
}

void CheckBoomCrush(Boom* head)
{
	Boom* p;

	for (p = head; p->nextBoom != NULL; p = p->nextBoom)
	{
		if ((p->nextBoom->boomAnimaition >= 100) && Crush(&Player_1, p->nextBoom->leftTop.x, p->nextBoom->leftTop.y, p->nextBoom->rightBottom.x, p->nextBoom->rightBottom.y))
			Energybar.right -= 10;
	}
}