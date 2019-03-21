#define _CRT_SECURE_NO_WARNINGS

#include "CalculationFunc.h"

enum symbol{
	NUM0, NUM1, NUM2, NUM3,
	NUM4, NUM5, NUM6, NUM7,
	NUM8, NUM9, PLUS, SUBT,
	MULT, DIVI,	EQUAL, SIGN
};

struct {
	int iStyle;
	TCHAR *szText;
	symbol sb;
} button[] = {
	BS_PUSHBUTTON, TEXT("%"), SIGN,
	BS_PUSHBUTTON, TEXT("√"), SIGN,
	BS_PUSHBUTTON, TEXT("x^2"), SIGN,
	BS_PUSHBUTTON, TEXT("1/x"), SIGN,
	BS_PUSHBUTTON, TEXT("CE"), SIGN,
	BS_PUSHBUTTON, TEXT("C"), SIGN,
	BS_PUSHBUTTON, TEXT("del"), SIGN,
	BS_PUSHBUTTON, TEXT("/"), DIVI,
	BS_PUSHBUTTON, TEXT("7"), NUM7,
	BS_PUSHBUTTON, TEXT("8"), NUM8,
	BS_PUSHBUTTON, TEXT("9"), NUM9,
	BS_PUSHBUTTON, TEXT("*"), MULT,
	BS_PUSHBUTTON, TEXT("4"), NUM4,
	BS_PUSHBUTTON, TEXT("5"), NUM5,
	BS_PUSHBUTTON, TEXT("6"), NUM6,
	BS_PUSHBUTTON, TEXT("-"), SUBT,
	BS_PUSHBUTTON, TEXT("1"), NUM1,
	BS_PUSHBUTTON, TEXT("2"), NUM2,
	BS_PUSHBUTTON, TEXT("3"), NUM3,
	BS_PUSHBUTTON, TEXT("+"), PLUS,
	BS_PUSHBUTTON, TEXT("negate"), SIGN,
	BS_PUSHBUTTON, TEXT("0"), NUM0,
	BS_PUSHBUTTON, TEXT("."), SIGN,
	BS_PUSHBUTTON, TEXT("="), EQUAL,
};

const int NUM = sizeof(button) / sizeof(button[0]);

#define WIDTH 4
#define HEIGHT 6

HWND hwndButton[NUM];
int cxChar, cyChar;//文字宽度和高度

void WMCreate(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam){

	HDC hdc = GetDC(hWnd);
	cxChar = LOWORD(GetDialogBaseUnits());
	cyChar = HIWORD(GetDialogBaseUnits());
	
	//SetBkColor(hdc, GetSysColor(COLOR_BTNTEXT));

	int cnt = 0;
	for (int height = 0; height < HEIGHT; ++height){
		for (int width = 0; width < WIDTH; ++width){
			cnt = height * WIDTH + width;
			hwndButton[cnt] = CreateWindow(TEXT("button"),
				button[cnt].szText,
				WS_CHILD | WS_VISIBLE | button[cnt].iStyle,
				width*cxChar*10, height*7*cyChar/4,
				cxChar * 10, 7*cyChar/4,
				hWnd, (HMENU)(cnt),
				((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}
	}

	ReleaseDC(hWnd, hdc);
}

void DrawPanel(HDC hdc){
}

double calc(double a, double b, symbol sb){
	double ret;
	switch (sb){
	case PLUS:
		ret = a + b;
		break;
	case SUBT:
		ret = a - b;
		break;
	case MULT:
		ret = a * b;
		break;
	case DIVI:
		ret = a / b;
		break;
	}
	return ret;
}

void WMCommand(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam){
	HDC hdc = GetDC(hWnd);
	TCHAR szBuffer[64];
	int btnID = LOWORD(wParam);

	SetTextAlign(hdc, TA_LEFT | TA_TOP);
	wsprintf(szBuffer, TEXT("%s %-8d %-8d %-8d %-8d"), 
		Msg == WM_DRAWITEM ? TEXT("WM_DRAWITEM") : TEXT("WM_COMMAND"),
		HIWORD(wParam), LOWORD(wParam),
		HIWORD(lParam), LOWORD(lParam));
	TextOut(hdc, cxChar*WIDTH * 10, 0, szBuffer, lstrlen(szBuffer));

	SetTextAlign(hdc, TA_RIGHT | TA_TOP);

	//GetWindowLong(hWnd, GWL_HINSTANCE);
	static TCHAR szExpression[64];
	TCHAR szNum[64] = "";
	static double num = 0;
	static double ans = 0;
	static symbol sb = NUM0;
	static int flag = 0;
	int len = lstrlen(szExpression);
	switch (button[btnID].sb){
	case NUM0:
		if (flag > 0){
			flag = 0;
			num = 0;
		} else{
			num = num * 10 + 0;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM1:
		if (flag > 0){
			flag = 0;
			num = 1;
		} else{
			num = num * 10 + 1;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM2:
		if (flag > 0){
			flag = 0;
			num = 2;
		} else{
			num = num * 10 + 2;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM3:
		if (flag > 0){
			flag = 0;
			num = 3;
		} else{
			num = num * 10 + 3;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM4:
		if (flag > 0){
			flag = 0;
			num = 4;
		} else{
			num = num * 10 + 4;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM5:
		if (flag > 0){
			flag = 0;
			num = 5;
		} else{
			num = num * 10 + 5;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM6:
		if (flag > 0){
			flag = 0;
			num = 6;
		} else{
			num = num * 10 + 6;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM7:
		if (flag > 0){
			flag = 0;
			num = 7;
		} else{
			num = num * 10 + 7;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM8:
		if (flag > 0){
			flag = 0;
			num = 8;
		} else{
			num = num * 10 + 8;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case NUM9:
		if (flag > 0){
			flag = 0;
			num = 9;
		} else{
			num = num * 10 + 9;
		}
		sprintf(szNum, TEXT("%.2lf"), num);
		break;
	case PLUS:
		if (sb != NUM0){
			ans = calc(ans, num, sb);
		} else{
			ans = num;
		}
		sprintf(szExpression, TEXT("%s%.2lf%s"), szExpression, num, "+");
		flag = 1;
		num = ans;
		sb = PLUS;
		break;
	case SUBT:
		if (sb != NUM0){
			ans = calc(ans, num, sb);
		} else{
			ans = num;
		}
		sprintf(szExpression, TEXT("%s%.2lf%s"), szExpression, num, "-");
		flag = 1;
		num = ans;
		sb = SUBT;
		break;
	case MULT:
		if (sb != NUM0){
			ans = calc(ans, num, sb);
		} else{
			ans = num;
		}
		sprintf(szExpression, TEXT("%s%.2lf%s"), szExpression, num, "*");
		flag = 1;
		num = ans;
		sb = MULT;
		break;
	case DIVI:
		if (sb != NUM0){
			ans = calc(ans, num, sb);
		} else{
			ans = num;
		}
		sprintf(szExpression, TEXT("%s%6.2lf%s"), szExpression, num, "/");
		flag = 1;
		num = ans;
		sb = DIVI;
		break;
	case EQUAL:
		ans = calc(ans, num, sb);
		num = ans;
		sprintf(szNum, TEXT("%.2lf"), num);
		num = 0;
		flag = 0;
		szExpression[0] = 0;
		ans = 0;
		sb = NUM0;
		break;
	}

	TextOut(hdc, cxChar*WIDTH * 10 + cxChar * 64, cyChar, szExpression, lstrlen(szExpression));
	TextOut(hdc, cxChar*WIDTH * 10 + cxChar * 64, cyChar * 2, szNum, lstrlen(szNum));

	ReleaseDC(hWnd, hdc);
}