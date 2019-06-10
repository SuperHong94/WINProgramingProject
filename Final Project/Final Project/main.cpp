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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(RGB(0, 255, 0));
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
	static int synch = 0; //싱크 맞춘다.

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
		Laser_Boom = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_LASERBOOM));
		Circle_Boom = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_CIRCLEBOOM));


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
<<<<<<< HEAD
			if (sj_Timer + synch == 10)  //1초
			{
				SunBoom_SJ(hDC, bullet_head, 300, 300);

			}
			if (sj_Timer + synch == 20)
			{
				SunBoom_SJ(hDC, bullet_head, 400, 400);
			}
			if (sj_Timer + synch == 30) {
				SunBoom_SJ(hDC, bullet_head, 500, 500);
			}
			if (sj_Timer + synch == 40) {
				SunBoom_SJ(hDC, bullet_head, 700, 700);
			}
			if (sj_Timer + synch == 45) {
				SunBoom_SJ(hDC, bullet_head, 500, 500);
			}
			if (sj_Timer + synch == 50) {
				SunBoom_SJ(hDC, bullet_head, 200, 200);
			}
			if (sj_Timer + synch == 55) {
				SunBoom_SJ(hDC, bullet_head, 200, 300);
			}
			if (sj_Timer + synch == 60) {
				SunBoom_SJ(hDC, bullet_head, 200, 300);
			}
			if (sj_Timer + synch == 70) {
				SunBoom_SJ(hDC, bullet_head, 200, 400);
			}
			if (sj_Timer + synch == 75) {
				SunBoom_SJ(hDC, bullet_head, 200, 500);
			}
			if (sj_Timer + synch == 76) {
				SunBoom_SJ(hDC, bullet_head, 200, 600);
			}
			if (sj_Timer + synch == 100) {
				SunBoom_SJ(hDC, bullet_head, 700, 100);
			}
			if (sj_Timer + synch == 125) {
				SunBoom_SJ(hDC, bullet_head, 700, 200);
			}
			if (sj_Timer + synch == 130) {
				SunBoom_SJ(hDC, bullet_head, 700, 200);
			}
			if (sj_Timer + synch == 140) {
				SunBoom_SJ(hDC, bullet_head, 700, 300);
			}
			if (sj_Timer + synch == 160) {
				SunBoom_SJ(hDC, bullet_head, 700, 200);
			}
			if (sj_Timer + synch == 168) {
				SunBoom_SJ(hDC, bullet_head, 700, 300);
			}
			if (sj_Timer + synch == 170) {
				SunBoom_SJ(hDC, bullet_head, 700, 300);
			}
			if (sj_Timer + synch == 180) {
				SunBoom_SJ(hDC, bullet_head, 500, 500);
			}
			if (sj_Timer + synch == 190) {
				SunBoom_SJ(hDC, bullet_head, 300, 300);
				SunBoom_SJ(hDC, bullet_head, 700, 700);
				
			}
			if (sj_Timer + synch == 200) {
				SunBoom_SJ(hDC, bullet_head, 100, 100);
				SunBoom_SJ(hDC, bullet_head, 900, 900);

			}
			if (sj_Timer + synch == 230) {
				Doughnut(hDC, bullet_head, WindowSize.right / 2, WindowSize.bottom / 2, 100); //윈도우 중앙에서
			}
			if (sj_Timer + synch == 308) {
				addBoom(head, Boom_Circle, 550, 550, 700, 700);
			}
			if (sj_Timer + synch == 310) {
				addBoom(head, Boom_Circle, 400, 400, 500, 700);
			}
			if (sj_Timer + synch == 320) {
				addBoom(head, Boom_Circle, 600, 300, 700, 400);
			}

			
			if (sj_Timer + synch == 380) {
				addBoom(head, Boom_DownLaser, 450, -100, 500, 900);
				addBoom(head, Boom_DownLaser, 150, -100, 200, 900);
				addBoom(head, Boom_DownLaser, 650, -100, 700, 900);
			}
			if (sj_Timer + synch == 335) {
				SunBoom_SJ(hDC, bullet_head, 120, 400);
			}
			if (sj_Timer + synch == 337) {
				SunBoom_SJ(hDC, bullet_head, 360, 400);
			}
			if (sj_Timer + synch == 339) {
				SunBoom_SJ(hDC, bullet_head, 480, 400);
			}
			if (sj_Timer + synch == 341) {
				SunBoom_SJ(hDC, bullet_head, 600, 400);
			}
			if (sj_Timer + synch == 343) {
				SunBoom_SJ(hDC, bullet_head, 840, 400);
=======
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
				addBoom(head, Boom_Laser2, 200, -100, 250, 900);
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
			default:
				break;
>>>>>>> ABCDEFG
			}
			break;
		case 2: //1초 단위로
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case 'E':
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
			break;
		case VK_F1:
			synch++;
			break;
		case VK_F2:
			synch--;
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
		DeleteObject(Circle_Boom);
		DeleteObject(Laser_Boom);
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

