
#include "ClockFunc.h"

int scale = 200;//����
int cScale = 0;
int cxClient, cyClient;//���ڿ�Ⱥ͸߶�
int xx, yy;//��Ļ���ĵ�����
double PI = 3.14159726;
SYSTEMTIME stPrevious;

void wm_create() {
	GetLocalTime(&stPrevious);
}

void setClient(int cx, int cy) {
	cxClient = cx;
	cyClient = cy;
	xx = cxClient / 2;
	yy = cyClient / 2;
	cScale = min(cxClient, cyClient) / scale;
}

void DrawClockPlate(HDC hdc) {

	Ellipse(hdc, 
		cxClient / 2 - cScale, cyClient / 2 - cScale,
		cxClient / 2 + cScale, cyClient / 2 + cScale);
	int x, y;
	for (int angle = 0; angle < 360; angle += 6) {
		x = 100 * cScale*sin(angle*PI/180);
		y = 100 * cScale*cos(angle*PI/180);
		x = xx + x;
		y = yy - y;
		HBRUSH hBrush = CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255));
		HBRUSH oldBush = (HBRUSH)SelectObject(hdc, hBrush);
		if (angle % 30 == 0) {
			Ellipse(hdc,
				x-5*cScale, y-5*cScale,
				x+5*cScale, y+5*cScale);
		} else {
			Ellipse(hdc,
				x - 1 * cScale, y - 1 * cScale,
				x + 1 * cScale, y + 1 * cScale);
		}
		hBrush = (HBRUSH)SelectObject(hdc, oldBush);
		DeleteObject(hBrush);
	}

}

POINT hourHand[5] = {0, 70, 10, 0, 0, -10, -10, 0, 0, 70};
POINT minuteHand[5] = {0, 90, 5, 0, 0, -20, -5, 0, 0, 90};

void DrawHand(HDC hdc) {
	POINT p, cMinuteHand[5], cHourHand[5];
	double angle;
	//������ʱ��
	SelectObject(hdc, GetStockObject(WHITE_PEN));
	//����������
	angle = stPrevious.wSecond*PI/30;
	p.x = 95 * cScale*sin(angle);
	p.y = 95 * cScale*cos(angle);
	MoveToEx(hdc, xx, yy, NULL);
	LineTo(hdc, xx + p.x, yy - p.y);
	//�����ɷ���
	angle = stPrevious.wMinute*PI / 30 + angle / 60;
	for (int i = 0; i < 5; ++i) {
		cMinuteHand[i].x = xx + (minuteHand[i].x*cScale*cos(angle) + minuteHand[i].y*cScale*sin(angle));
		cMinuteHand[i].y = yy - (minuteHand[i].y*cScale*cos(angle) - minuteHand[i].x*cScale*sin(angle));
	}
	Polyline(hdc, cMinuteHand, 5);
	//������ʱ��
	angle = stPrevious.wHour*PI / 6 + angle / 12;
	for (int i = 0; i < 5; ++i) {
		cHourHand[i].x = xx + (hourHand[i].x*cScale*cos(angle) + hourHand[i].y*cScale*sin(angle));
		cHourHand[i].y = yy - (hourHand[i].y*cScale*cos(angle) - hourHand[i].x*cScale*sin(angle));
	}
	Polyline(hdc, cHourHand, 5);

	SYSTEMTIME st;
	TCHAR szStr[1024];

	GetLocalTime(&st);

	wsprintf(szStr, TEXT("%d��%d��%d�� ��%d %02d:%02d:%02d:%d"),
		st.wYear, st.wMonth, st.wDay, st.wDayOfWeek,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	TextOut(hdc, 0, 0, szStr, lstrlen(szStr));

	//����ʱ��
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	//��������
	angle = st.wSecond*PI/30;
	p.x = 95 * cScale*sin(angle);
	p.y = 95 * cScale*cos(angle);
	MoveToEx(hdc, xx, yy, NULL);
	LineTo(hdc, xx + p.x, yy - p.y);
	//���·���
	angle = st.wMinute*PI/30 + angle/60;
	for (int i = 0; i < 5; ++i) {
		cMinuteHand[i].x = xx + (minuteHand[i].x*cScale*cos(angle) + minuteHand[i].y*cScale*sin(angle));
		cMinuteHand[i].y = yy - (minuteHand[i].y*cScale*cos(angle) - minuteHand[i].x*cScale*sin(angle));
	}
	Polyline(hdc, cMinuteHand, 5);
	//����ʱ��
	angle = st.wHour*PI/6 + angle/12;
	for (int i = 0; i < 5; ++i) {
		cHourHand[i].x = xx + (hourHand[i].x*cScale*cos(angle) + hourHand[i].y*cScale*sin(angle));
		cHourHand[i].y = yy - (hourHand[i].y*cScale*cos(angle) - hourHand[i].x*cScale*sin(angle));
	}
	Polyline(hdc, cHourHand, 5);

	Ellipse(hdc,
		cxClient / 2 - cScale, cyClient / 2 - cScale,
		cxClient / 2 + cScale, cyClient / 2 + cScale);
	stPrevious = st;
}