#include "global.h"
int sj_Timer = 0;
void SunBoom_SJ(HDC hDC, Boom* boom)
{
	HBRUSH hBrush;  //색깔
	boom->leftBottom.x = 200;
	boom->leftBottom.y = 200;
	boom->width = 100;
	boom->boomShape = MyCircle;
	int x = boom->leftBottom.x;
	int y = boom->leftBottom.y;
	int width = boom->width;
	switch (boom->boomShape) {
	case MyCircle:
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		(HBRUSH)SelectObject(hDC, hBrush);
		if (sj_Timer%10==9) {
			Ellipse(hDC, x + width / 4, y - width / 4, x + (width*0.75), y + width / 4); //원상단에 그리기 테스트용임
		}
		else
			Ellipse(hDC, x, y, x + width, y + width);

		DeleteObject(hBrush);
	}

}