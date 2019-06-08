#include "global.h"

int sj_Timer = 0;
RECT Player_1;
RECT WindowSize;
RECT Energybar;
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
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
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
		if (boomAnimaition >= 0 && boomAnimaition < 100)
		{
			leftTop.x = 50;
			leftTop.y = 50;
			rightBottom.x = 150;
			rightBottom.y = 150;

		}

		else if (boomAnimaition == 100)
		{
			leftTop.x -= 25;
			leftTop.y -= 25;
			rightBottom.x += 25;
			rightBottom.y += 25;
		}

		else if (boomAnimaition > 100)
		{
			leftTop.x += 2;
			leftTop.y += 2;
			rightBottom.x -= 2;
			rightBottom.y -= 2;
			if (leftTop.x >= rightBottom.x)
				boomAnimaition = 0;
		}
		break;
	case Boom_Laser:
		if (boomAnimaition >= 0 && boomAnimaition < 100)
		{
			leftTop.x = 0;
			leftTop.y = 400;
			rightBottom.x = 1200;
			rightBottom.y = 450;
		}

		else if (boomAnimaition == 100)
		{
			leftTop.y -= 25;
			rightBottom.y += 25;
		}
		else if (boomAnimaition > 100)
		{
			leftTop.y += 2;
			rightBottom.y -= 2;
			if (leftTop.y >= rightBottom.y)
				boomAnimaition = 0;
		}
		break;
	case Bullet_Up:
		leftTop.y--;
		rightBottom.y--;
		break;
	case Bullet_Down:
		leftTop.y++;
		rightBottom.y++;
		break;
	case Bullet_Right:
		leftTop.x++;
		rightBottom.x++;
		break;
	case Bullet_Left:
		leftTop.x--;
		rightBottom.x--;
		break;
	case Bullet_UpRight:
		leftTop.y--;
		leftTop.x++;
		rightBottom.x++;
		rightBottom.y--;
		break;
	case Bullet_UpLeft:
		leftTop.y--;
		rightBottom.y--;
		leftTop.x--;
		rightBottom.x--;
		break;
	case Bullet_DownRight:
		leftTop.y++;
		rightBottom.y++;
		leftTop.x++;
		rightBottom.x++;
		break;
	case Bullet_DownLeft:
		leftTop.y++;
		rightBottom.y++;
		leftTop.x--;
		rightBottom.x--;

		break;
	default:

		break;
	}
	 if(Crush(&Player_1, leftTop.x, leftTop.y, rightBottom.x, rightBottom.y))
      Energybar.right -= 10;
}


void CircleBoom(HDC hDC, Boom* boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	if (boom->boomAnimaition < 100)
	{
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
	}

	else
	{
		switch (boom->boomAnimaition % 2)
		{
		case 0:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
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

void LaserBoom(HDC hDC, Boom* boom)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	if (boom->boomAnimaition < 100)
	{
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
	}
	else
	{
		switch (boom->boomAnimaition % 2)
		{
		case 0:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Rectangle(hDC, boom->leftTop.x, boom->rightBottom.y, boom->rightBottom.x, boom->leftTop.y);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			break;
		}
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
		case MyDoughnut1:
		case MyDoughnut2:
		case MyDoughnut3:
		case MyDoughnut4:
			NormalBullet(hDC, p->nextBoom);
			break;
		case Boom_Circle:
			CircleBoom(hDC, p->nextBoom);
			break;
		case Boom_Laser:
			LaserBoom(hDC, p->nextBoom);
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
		}
		if (p->nextBoom == NULL)
			break;
	}
}

void Animation(HDC hDC)
{

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