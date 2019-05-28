#include "global.h"
int sj_Timer = 0;
void SunBoom_SJ(HDC hDC, Boom boom)
{
	HBRUSH hBrush;
	int x = boom.leftBottom.x;
	int y = boom.leftBottom.y;
	int width = boom.width;
	switch (boom.boomShape) {
	case MyCircle:
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		(HBRUSH)SelectObject(hDC, hBrush);
		if (sj_Timer % 10 == 3) {
			Ellipse(hDC, x + width / 4, y - width / 4, x + (width*0.75), y + width / 4); //원상단에 그리기 테스트용임
			Sleep(1000);
		}
		else
			Ellipse(hDC, x, y, x + width, y + width);

		DeleteObject(hBrush);
	}

}