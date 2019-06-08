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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	char buffer[10]; //�ʼ��� Ÿ�̸�
	static HDC hDC, MemDC;
	static HBITMAP BackBit, oldBackBit, hBit[10];
	static RECT bufferRT;
	PAINTSTRUCT ps;
	static Boom* head;
	static Boom* bullet_head;

	//int boomCount = 0;  //��ź ī��Ʈ�� 0;

	static RECT Player_1;

	//�޽��� ó���ϱ�
	switch (uMsg) {
	case WM_CREATE:
		head = new Boom;
		bullet_head = new Boom;

		bullet_head->nextBoom = NULL;
		head->nextBoom = NULL;
		GetClientRect(hWnd, &WindowSize);
		Player_1.top = 380;
		Player_1.bottom = 405;
		Player_1.left = 380;
		Player_1.right = 405;
		addBoom(head, Boom_Circle, 50, 50, 150, 150);
		addBoom(head, Boom_Laser, 0, 400, 1200, 450);

		soundSetup(); //���� �¾�
		SetTimer(hWnd, 0, 10, NULL);
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 1000, NULL);

		playSound(Perion);//�丮�� ���
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
			setBoomPosition(bullet_head);
			break;
		case 1:  //0.1�� ������ ������
			sj_Timer++;
			if (sj_Timer == 50)
			{
				
			}
			if (sj_Timer == 10)
			{
				SunBoom_SJ(hDC, bullet_head, 300, 300);
				Doughnut(hDC, bullet_head,500,500,100);
			}
			break;
		case 2: //1�� ������
			setAnimation(head);
			setBoomPosition(head);
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);

	case WM_KEYDOWN:
		if (wParam == 'E')
		{
			if (GetAsyncKeyState('A') < 0)
			{
				Player_1.left -= 50;
				Player_1.right -= 50;
			}

			if (GetAsyncKeyState('W') < 0)
			{
				Player_1.top -= 50;
				Player_1.bottom -= 50;
			}

			if (GetAsyncKeyState('S') < 0)
			{
				Player_1.top += 50;
				Player_1.bottom += 50;
			}

			if (GetAsyncKeyState('D') < 0)
			{
				Player_1.left += 50;
				Player_1.right += 50;
			}
		}
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, BLACKNESS);
		sprintf(buffer, "�ð�: %d", sj_Timer);
		TextOutA(hDC, 500, 10, buffer, 10);

		Rectangle(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);
		printBoomAnimation(hDC, head);
		printBoomAnimation(hDC, bullet_head);

		GetClientRect(hWnd, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
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
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

