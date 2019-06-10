#include "global.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	//������ Ŭ���� ����ü �� ����
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(RGB(0,255,0));
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//������ Ŭ���� ���
	RegisterClassEx(&WndClass);

	//������ ����
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 800, NULL, (HMENU)NULL, hInstance, NULL);

	//������ ���
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//�̺�Ʈ ���� ó��
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);

	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char buffer[1000]; //�ʼ��� Ÿ�̸�
	static HDC hDC, MemDC;
	static HBITMAP BackBit, oldBackBit, hBit[10];
	static RECT bufferRT;
	PAINTSTRUCT ps;
	static Boom* head;
	static Boom* bullet_head;
	static bool Tp;
	static RECT tmp;
	//int boomCount = 0;  //��ź ī��Ʈ�� 0;

	//�޽��� ó���ϱ�
	switch (uMsg) {
	case WM_CREATE:
		head = new Boom;
		bullet_head = new Boom;
		bullet_head->nextBoom = NULL;
		head->nextBoom = NULL;
		GetClientRect(hWnd, &WindowSize);
		GetClientRect(hWnd, &Energybar);
		Player_1.top = 380;
		Player_1.bottom = 405;
		Player_1.left = 380;
		Player_1.right = 405;
		Laser_Boom = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_LASERBOOM));
		Circle_Boom = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_CIRCLEBOOM));
		Tp = FALSE;

		soundSetup(); //���� �¾�
		effSoundSetup();//����Ʈ �¾�
		SetTimer(hWnd, 0, 10, NULL);
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
		
		playSound(STAGE2);//�丮�� ���
		break;
	case WM_TIMER:
		switch (wParam) {
		case 0:
			if (GetAsyncKeyState('A') < 0)
			{
				Player_1.left -= 3;
				Player_1.right -= 3;
			}

			if (GetAsyncKeyState('W') < 0)
			{
				Player_1.top -= 3;
				Player_1.bottom -= 3;
			}

			if (GetAsyncKeyState('S') < 0)
			{
				Player_1.top += 3;
				Player_1.bottom += 3;
			}

			if (GetAsyncKeyState('D') < 0)
			{
				Player_1.left += 3;
				Player_1.right += 3;
			}
			CheckBullet(bullet_head);
			CheckBoom(head);
			setBoomPosition(bullet_head);
			setAnimation(head);
			setBoomPosition(head);
			CheckBulletCrush(bullet_head);
			CheckBoomCrush(head);
			break;
		case 1:  //0.1�� ������ ������
			sj_Timer++;
			switch (sj_Timer)
			{
			case 10:
				addBoom(head, Boom_Circle, 100, 80, 500, 480);
				break;
			case 11:
				addBoom(head, Boom_Circle, 100, 350, 500, 750);
				break;
			case 12:
				addBoom(head, Boom_Circle, 500, 350, 800, 650);
				break;
			case 13:
				addBoom(head, Boom_Circle, 500, 80, 800, 380);
				break;
			case 40:
				addBoom(head, Boom_Circle, 450, 80, 1050, 680);
				break;
			case 41:
				addBoom(head, Boom_Circle, 50, 50, 350, 350);
				break;
			case 42:
				addBoom(head, Boom_Circle, 300, 300, 600, 600);
				break;
			case 110:
				addBoom(head, Boom_Laser, -100, 50, 1300, 100);
				break;
			case 111:
				addBoom(head, Boom_Laser, -100, 150, 1300, 200);
				break;
			case 112:
				addBoom(head, Boom_Laser, -100, 250, 1300, 300);
				break;
			case 113:
				addBoom(head, Boom_Laser, -100, 350, 1300, 400);
				break;
			case 114:
				addBoom(head, Boom_Laser, -100, 450, 1300, 500);
				break;
			case 115:
				addBoom(head, Boom_Laser, -100, 550, 1300, 600);
				break;
			case 116:
				addBoom(head, Boom_Laser, -100, 650, 1300, 700);
				break;
			case 117:
				addBoom(head, Boom_Laser, -100, 750, 1300, 800);
				break;
			case 160:
				addBoom(head, Boom_Laser, -100, 650, 1300, 700);
				break;
			case 161:
				addBoom(head, Boom_Laser, -100, 550, 1300, 600);
				break;
			case 162:
				addBoom(head, Boom_Laser, -100, 450, 1300, 500);
				break;
			case 163:
				addBoom(head, Boom_Laser, -100, 350, 1300, 400);
				break;
			case 164:
				addBoom(head, Boom_Laser, -100, 250, 1300, 300);
				break;
			case 165:
				addBoom(head, Boom_Laser, -100, 150, 1300, 200);
				break;
			case 166:
				addBoom(head, Boom_Laser, -100, 50, 1300, 100);
				break;
			case 203:
				SunBoom_SJ(hDC, bullet_head, 540, 380);
				break;
			case 208:
				SunBoom_SJ(hDC, bullet_head, 150, 200);
				break;
			case 209:
				SunBoom_SJ(hDC, bullet_head, 250, 300);
				break;
			case 210:
				SunBoom_SJ(hDC, bullet_head, 550, 300);
				break;
			case 240:
				addBoom(head, Boom_Rectangle, -100, 0, 550, 650);
				addBoom(head, Boom_Rectangle, 450, 150, 1050, 750);
				SunBoom_SJ(hDC, bullet_head, 750, 300);
				break;
			case 241:
				SunBoom_SJ(hDC, bullet_head, 650, 450);
				break;
			case 242:
				SunBoom_SJ(hDC, bullet_head, 730, 380);
				break;
			case 296:
				Doughnut(hDC, head, 520, 380, 50);
				break;
			case 297:
				SunBoom_SJ(hDC, bullet_head, 100, 100);
				SunBoom_SJ(hDC, bullet_head, 1100, 100);
				SunBoom_SJ(hDC, bullet_head, 100, 700);
				SunBoom_SJ(hDC, bullet_head, 1100, 700);
				break;
			case 310:
				addBoom(head, Boom_LeftLaser, -100, 340, 1300, 390);
				addBoom(head, Boom_RightLaser, -100, 340, 1300, 390);
				addBoom(head, Boom_UpLaser, 540, -100, 590, 900);
				addBoom(head, Boom_DownLaser, 540, -100, 590, 900);
				addBoom(head, Boom_Laser2, 50, -100, 100, 900);
				addBoom(head, Boom_Laser2, 1130, -100, 1180, 900);
				SunBoom_SJ(hDC, bullet_head, 850, 650);
				break;
			case 315:
				addBoom(head, Boom_Laser2, 900, -100, 950, 900);
				break;
			case 320:
				SunBoom_SJ(hDC, bullet_head, 250, 650);
				addBoom(head, Boom_Laser, -100, 200, 1300, 250);
				break;
			case 325:
				addBoom(head, Boom_Laser, -100, 600, 1300, 650);
				break;
			case 390:
				SunBoom_SJ(hDC, bullet_head, 124, 350);
				SunBoom_SJ(hDC, bullet_head, 842, 420);
				break;
			case 393:
				SunBoom_SJ(hDC, bullet_head, 640, 150);
				SunBoom_SJ(hDC, bullet_head, 4, 560);
				break;
			default:
				break;
			}
			break;
		case 2: //1�� ������
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);

	case WM_KEYDOWN:
		if (wParam == 'E')
		{
			effPlaySound(jump);
			
			if (GetAsyncKeyState('A') < 0)
			{
				Player_1.left -= 100;
				Player_1.right -= 100;
			}

			if (GetAsyncKeyState('W') < 0)
			{
				Player_1.top -= 100;
				Player_1.bottom -= 100;
			}

			if (GetAsyncKeyState('S') < 0)
			{
				Player_1.top += 100;
				Player_1.bottom += 100;
			}

			if (GetAsyncKeyState('D') < 0)
			{
				Player_1.left += 100;
				Player_1.right += 100;
			}
		}
		else if (wParam == 'R')
		{
			if (Tp)
			{
				Player_1.bottom = tmp.bottom;
				Player_1.left = tmp.left;
				Player_1.right = tmp.right;
				Player_1.top = tmp.top;
				Tp = FALSE;
			}
			else
			{
				tmp.bottom = Player_1.bottom;
				tmp.left = Player_1.left;
				tmp.right = Player_1.right;
				tmp.top = Player_1.top;
				Tp = TRUE;
			}
		}

		switch (wParam) {
		case VK_BACK:
			sj_Timer -= 10;
			break;
		}
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		//GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, WindowSize.right, WindowSize.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, WindowSize.right, WindowSize.bottom, BLACKNESS);

		sprintf(buffer, "�ð�: %d", sj_Timer);
		TextOutA(hDC, 500, 10, buffer, 10);
		Animation(hDC, g_hInst, head, bullet_head);
		DrawEnergybar(hDC);

		GetClientRect(hWnd, &WindowSize);

		BitBlt(MemDC, 0, 0, WindowSize.right, WindowSize.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		free(head);
		DeleteObject(Circle_Boom);
		DeleteObject(Laser_Boom);
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

