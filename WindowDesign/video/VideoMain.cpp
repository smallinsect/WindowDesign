#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc1(HWND, UINT, WPARAM, LPARAM);

int iCurrentColor = IDC_RED,
	iCurrentFigure = IDC_RECTANGLE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{

	static TCHAR szAppName[] = TEXT("About2");
	HWND                                                        hwnd;
	MSG                                                         msg;
	WNDCLASS                                             wndclass;

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 125, 125));

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hbrBackground = hBrush;
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))

	{

		MessageBox(NULL, TEXT("This program requires Windows NT!"),

			szAppName, MB_ICONERROR);

		return 0;

	}



	hwnd = CreateWindow(szAppName, TEXT("MetaFile Demonstration"),

		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT,

		CW_USEDEFAULT, CW_USEDEFAULT,

		NULL, NULL, hInstance, NULL);



	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);



	while (GetMessage(&msg, NULL, 0, 0))

	{

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.wParam;

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 0;
	switch (message)
	{
	case   WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		return 0;
	case WM_COMMAND:
		hdc = GetDC(hwnd);
		switch (LOWORD(wParam)){
		case ID_HELP_ABOUTABOUT1:
			DialogBox(hInstance, TEXT("AboutBox"), hwnd, AboutDlgProc);
			break;
		case ID_HELP_ABOUTABOUT2:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc1);
			//InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		ReleaseDC(hwnd, hdc);
		break;
	case   WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Ellipse(hdc, x, x, x + 100, x + 100);
		x += 100;
		EndPaint(hwnd, &ps);
		return 0;
	case   WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}



BOOL CALLBACK AboutDlgProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	static HWND hCtrlBlock;
	static int iColor, iFigure;
	static int cxClient, cyClient;
	TCHAR szStr[1024];
	HDC hdc;
	RECT rect;
	HBRUSH hBrush, hOldBrush;
	switch (message){
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		case IDC_BLACK:
		case IDC_GREEN:
		case IDC_BLUE:
		case IDC_CYAN:
		case IDC_RED:
		case IDC_YELLOW:
		case IDC_WHITE:
			hdc = GetDC(hDlg);
			GetClientRect(hDlg, &rect);

			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, rect.right / 2 + 50, rect.bottom / 2 - 100, rect.right / 2 + 150, rect.bottom / 2);
			Rectangle(hdc, rect.right / 2 + 50, rect.bottom / 2 - 100, rect.right / 2 + 150, rect.bottom / 2);
			hBrush = (HBRUSH)SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush);

			//cxClient = ((LPCREATESTRUCT)lParam)->cx;
			//cyClient = ((LPCREATESTRUCT)lParam)->cy;
			//wsprintf(szStr, TEXT("%d %d"), cxClient, cyClient);
			//TextOut(hdc, 0, 0, szStr, lstrlen(szStr));


			ReleaseDC(hDlg, hdc);
			break;
		case IDC_RECTANGLE:
		case IDC_ELLIPSE:
			
			break;
		}
		break;
	}
	return FALSE;
}