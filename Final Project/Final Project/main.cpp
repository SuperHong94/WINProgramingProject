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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//������ Ŭ���� ���
	RegisterClassEx(&WndClass);

	//������ ����
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

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
	static HDC hDC, MemDC;
	static HBITMAP BackBit, oldBackBit, hBit[10];
	static RECT bufferRT;
	PAINTSTRUCT ps;

	static Boom* boom;
	static Boom circleboom;
	static Boom laserboom;

	//int boomCount = 0;  //��ź ī��Ʈ�� 0;

	static RECT Player_1;

	//�޽��� ó���ϱ�
	switch (uMsg) {
	case WM_CREATE:
		Player_1.top = 380;
		Player_1.bottom = 430;
		Player_1.left = 380;
		Player_1.right = 430;

		circleboom.boomAnimaition = 0;
		circleboom.leftTop.x = 50;
		circleboom.leftTop.y = 50;
		circleboom.rightBottom.x = 150;
		circleboom.rightBottom.y = 150;

		laserboom.boomAnimaition = 0;
		laserboom.leftTop.x = 0;
		laserboom.leftTop.y = 150;
		laserboom.rightBottom.x = 800;
		laserboom.rightBottom.y = 50;


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
			break;
		case 1:
			sj_Timer++;
			if (sj_Timer == 10) {
				boom = new Boom[0];

			}
			if (sj_Timer >= 130) {
				SunBoom_SJ(hDC, boom);
				boom->rightBottom.x += 10;
				boom->rightBottom.y += 10;
			}
			else if (sj_Timer >= 200) {
				delete boom;
				boom = NULL;
			}
			break;
		case 2:
			++circleboom.boomAnimaition;
			circleboom.boomAnimaition %= 5;

			if (circleboom.boomAnimaition == 0)
			{
				circleboom.leftTop.x = 50;
				circleboom.leftTop.y = 50;
				circleboom.rightBottom.x = 150;
				circleboom.rightBottom.y = 150;
			}

			else if (circleboom.boomAnimaition == 1)
			{
				circleboom.leftTop.x -= 25;
				circleboom.leftTop.y -= 25;
				circleboom.rightBottom.x += 25;
				circleboom.rightBottom.y += 25;
			}

			else if (circleboom.boomAnimaition == 3)
			{
				circleboom.leftTop.x += 50;
				circleboom.leftTop.y += 50;

				circleboom.rightBottom.x -= 50;
				circleboom.rightBottom.y -= 50;
			}

			
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		Rectangle(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);
		CircleBoom(hDC, circleboom);

		GetClientRect(hWnd, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


