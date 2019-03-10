//#include <iostream>
//using namespace std;
//
//int main() {
//	cout << "¹þ¹þ¹þ¹þ" << endl;
//
//	system("pause");
//	return 0;
//}
#include "resource.h"

#include <windows.h>

HINSTANCE g_hInstace;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow) {
	g_hInstace = hInstance;
	//MessageBox(NULL, TEXT("°®°×²ËµÄÐ¡À¥³æ"), TEXT("À¥³æ"), MB_OK);
	TCHAR szClassName[] = TEXT("my window");

	MSG msg;
	HWND hWnd;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szClassName, MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName,
		TEXT("CLOCK"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rect;
	HINSTANCE hInstance;
	BITMAP bitmap;

	static HBITMAP hBitmap;
	static int cxSource, cySource, cxClient, cyClient;

	switch (Msg) {
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

		GetObject(hBitmap, sizeof(BITMAP), &bitmap);

		cxSource = bitmap.bmWidth;
		cySource = bitmap.bmHeight;

		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBitmap);

		BitBlt(hdc, 0, 0, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);

		DeleteDC(hdcMem);                                               

		Ellipse(hdc, 
			cxClient/2-50, cyClient/2-50, 
			cxClient/2+50, cyClient/2+50);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}