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

	//윈도우 클래스 구조체 값 설정
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
	//윈도우 클래스 등록
	RegisterClassEx(&WndClass);

	//윈도우 생성
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 800, NULL, (HMENU)NULL, hInstance, NULL);

	//윈도우 출력
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);

	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char buffer[1000]; //초세는 타이머
	static HDC hDC, MemDC;
	static HBITMAP BackBit, oldBackBit, hBit[10];
	static RECT bufferRT;
	PAINTSTRUCT ps;
	static Boom* head;
	static Boom* bullet_head;

	//int boomCount = 0;  //폭탄 카운트는 0;

	//메시지 처리하기
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
		addBoom(head, Boom_Circle, 550, 550, 700, 700);
		addBoom(head, Boom_RightLaser, -100, 400, 1300, 450);
		addBoom(head, Boom_UpLaser, 600, -100, 650, 900);
		addBoom(head, Boom_LeftLaser, -100, 600, 1300, 650);
		addBoom(head, Boom_DownLaser, 450, -100, 500, 900);


		soundSetup(); //사운드 셋업
		effSoundSetup();//이펙트 셋업
		SetTimer(hWnd, 0, 10, NULL);
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
		
		playSound(Perion);//페리온 재생
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
		case 1:  //0.1초 단위로 생성됨
			sj_Timer++;
			if (sj_Timer == 10)  //1초
			{
				SunBoom_SJ(hDC, bullet_head, 300, 300);
			
			}
			if (sj_Timer == 20)
			{
				SunBoom_SJ(hDC, bullet_head, 400, 400);
			}
			if (sj_Timer == 30) {
				SunBoom_SJ(hDC, bullet_head, 500, 500);
			}
			if (sj_Timer == 40) {
				SunBoom_SJ(hDC, bullet_head, 700, 700);
			}
			if (sj_Timer == 45) {
				SunBoom_SJ(hDC, bullet_head, 500, 500);
			}
			if (sj_Timer == 50) {
				SunBoom_SJ(hDC, bullet_head, 200, 200);
			}
			if (sj_Timer == 55) {
				SunBoom_SJ(hDC, bullet_head, 200, 300);
			}
			if (sj_Timer == 60) {
				SunBoom_SJ(hDC, bullet_head, 200, 300);
			}
			if (sj_Timer == 70) {
				SunBoom_SJ(hDC, bullet_head, 200, 400);
			}
			if (sj_Timer == 78) {
				SunBoom_SJ(hDC, bullet_head, 200, 500);
			}
			if (sj_Timer == 79) {
				SunBoom_SJ(hDC, bullet_head, 200, 600);
			}
			if (sj_Timer == 100) {
				SunBoom_SJ(hDC, bullet_head, 700, 100);
			}
			if (sj_Timer == 230) {
				Doughnut(hDC, bullet_head,WindowSize.right / 2, WindowSize.bottom / 2,100); //윈도우 중앙에서
			}
			break;
		case 2: //1초 단위로
			setAnimation(head);
			setBoomPosition(head);
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);

	case WM_KEYDOWN:
		if (wParam == 'E')
		{
			effPlaySound(jump);
			
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

		sprintf(buffer, "시간: %d", sj_Timer);
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
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

