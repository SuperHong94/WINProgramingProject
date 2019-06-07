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

	//¿©µµøÏ ≈¨∑°Ω∫ ±∏¡∂√º ∞™ º≥¡§
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
	//¿©µµøÏ ≈¨∑°Ω∫ µÓ∑œ
	RegisterClassEx(&WndClass);

	//¿©µµøÏ ª˝º∫
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 800, NULL, (HMENU)NULL, hInstance, NULL);

	//¿©µµøÏ √‚∑¬
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//¿Ã∫•∆Æ ∑Á«¡ √≥∏Æ
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
<<<<<<< HEAD
	static Boom* head;
	static Boom Sunboom1;
	//int boomCount = 0;  //∆¯≈∫ ƒ´øÓ∆Æ¥¬ 0;

=======

	static Boom* boom;
	static Boom circleboom;
	static Boom laserboom;

	//int boomCount = 0;  //∆¯≈∫ ƒ´øÓ∆Æ¥¬ 0;

>>>>>>> parent of b1bc396... ÏßÑÏßú Î≠êÍ∞ÄÎ¨∏Ï†úÎÉê
	static RECT Player_1;

	//∏ﬁΩ√¡ˆ √≥∏Æ«œ±‚
	switch (uMsg) {
	case WM_CREATE:
<<<<<<< HEAD
		head = new Boom;
		head->nextBoom = NULL;
		GetClientRect(hWnd, &WindowSize);
		Player_1.top = 380;
		Player_1.bottom = 405;
		Player_1.left = 380;
		Player_1.right = 405;
		
		addBoom(head, Boom_Circle, 50, 50, 150, 150);
		addBoom(head, Boom_Laser, 0, 400, 1200, 450);
		InitBoom(Sunboom1, 100, 100, 200, 200);
=======
		Player_1.top = 380;
		Player_1.bottom = 430;
		Player_1.left = 380;
		Player_1.right = 430;

		circleboom.boomAnimaition = 0;
		circleboom.leftBottom.x = 50;
		circleboom.leftBottom.y = 150;
		circleboom.rightTop.x = 150;
		circleboom.rightTop.y = 50;


>>>>>>> parent of b1bc396... ÏßÑÏßú Î≠êÍ∞ÄÎ¨∏Ï†úÎÉê
		soundSetup(); //ªÁøÓµÂ º¬æ˜
		SetTimer(hWnd, 0, 10, NULL);
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 1000, NULL);

		playSound(Perion);//∆‰∏Æø¬ ¿Áª˝
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
<<<<<<< HEAD

			break;
		case 2:
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
=======
			if (sj_Timer == 10) {
				boom = new Boom[0];

			}
			if (sj_Timer >= 130) {
				SunBoom_SJ(hDC, boom);
				boom->rightTop.x += 10;
				boom->rightTop.y += 10;
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
				circleboom.leftBottom.x = 50;
				circleboom.leftBottom.y = 150;
				circleboom.rightTop.x = 150;
				circleboom.rightTop.y = 50;
>>>>>>> parent of b1bc396... ÏßÑÏßú Î≠êÍ∞ÄÎ¨∏Ï†úÎÉê
			}

			if (GetAsyncKeyState('W') < 0)
			{
<<<<<<< HEAD
				Player_1.top -= 50;
				Player_1.bottom -= 50;
=======
				circleboom.leftBottom.x -= 25;
				circleboom.rightTop.y -= 25;
				circleboom.rightTop.x += 25;
				circleboom.leftBottom.y += 25;
>>>>>>> parent of b1bc396... ÏßÑÏßú Î≠êÍ∞ÄÎ¨∏Ï†úÎÉê
			}

			if (GetAsyncKeyState('S') < 0)
			{
<<<<<<< HEAD
				Player_1.top += 50;
				Player_1.bottom += 50;
			}

			if (GetAsyncKeyState('D') < 0)
			{
				Player_1.left += 50;
				Player_1.right += 50;
			}
=======
				circleboom.leftBottom.x += 50;
				circleboom.rightTop.y += 50;
				circleboom.rightTop.x -= 50;
				circleboom.leftBottom.y -= 50;
			}

			
			break;
>>>>>>> parent of b1bc396... ÏßÑÏßú Î≠êÍ∞ÄÎ¨∏Ï†úÎÉê
		}
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, BLACKNESS);
		sprintf(buffer, "Ω√∞£: %d", sj_Timer);
		TextOutA(hDC, 500, 10, buffer, 10);

		Rectangle(hDC, Player_1.left, Player_1.top, Player_1.right, Player_1.bottom);
<<<<<<< HEAD
		Doughnut(hDC, g_hInst);  //µµ≥” ∆¯≈∫
		SunBoom_SJ(hDC, Sunboom1);
		printBoomAnimation(hDC, head);
=======
		CircleBoom(hDC, circleboom);
>>>>>>> parent of b1bc396... ÏßÑÏßú Î≠êÍ∞ÄÎ¨∏Ï†úÎÉê

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


