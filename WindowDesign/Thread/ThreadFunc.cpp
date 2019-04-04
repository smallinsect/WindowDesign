
#include "ThreadFunc.h"

DWORD WINAPI ThreadFunc(LPVOID n){
	printf("thread %d running\n", (DWORD)n);
	Sleep((DWORD)n * 1000 * 2);
	return (DWORD)n * 10;
}

void fun1(){
	HANDLE hThread1;
	HANDLE hThread2;
	DWORD exitCode1 = 0;
	DWORD exitCode2 = 0;
	DWORD threadId;
	hThread1 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)1, 0, &threadId);
	if (hThread1){
		puts("Thread 1 launched");
	}
	hThread2 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)2, 0, &threadId);
	if (hThread2){
		puts("Thread 2 launched");
	}

	for (;;){
		puts("Press any key to exit...");
		_getch();

		GetExitCodeThread(hThread1, &exitCode1);
		GetExitCodeThread(hThread2, &exitCode2);

		if (exitCode1 == STILL_ACTIVE){
			puts("Thread 1 is still running");
		}
		if (exitCode2 == STILL_ACTIVE){
			puts("Thread 2 is still running");
		}
		if (exitCode1 != STILL_ACTIVE && exitCode2 != STILL_ACTIVE){
			break;
		}
	}

	CloseHandle(hThread1);
	CloseHandle(hThread2);

	printf("Thread 1 return %d\n", exitCode1);
	printf("Thread 2 return %d\n", exitCode2);

}



DWORD WINAPI ThreadFunc2(LPVOID n){
	for (int i = 0; i < 10; ++i){
		printf("%d%d%d%d\n", (int)n, (int)n, (int)n, i);
	}
	return 0;
}

void fun2(){
	HANDLE hThread;
	DWORD threadId;

	for (int i = 0; i < 5; ++i){
		hThread = CreateThread(NULL, 0, ThreadFunc2, (LPVOID)i, 0, &threadId);
		if (hThread){
			printf("Thread launched %d\n", i);
			CloseHandle(hThread);
		}
	}

	//Wait for the threads to complete
	Sleep(2000);
}

unsigned int Counter;
unsigned int __stdcall SecondThreadFunc(void *pArguments){
	printf("In second thread...\n");
	while (Counter < 1000000){
		Counter++;
	}
	_endthreadex(0);
	return 0;
}

void fun3(){

	HANDLE hThread;
	unsigned int threadID;

	printf("Creating second thread...\n");
	//Create the second thread.
	hThread = (HANDLE)_beginthreadex(NULL, 0, SecondThreadFunc, NULL, 0, &threadID);

	WaitForSingleObject(hThread, INFINITE);
	printf("Counter should be 1000000; it is->%d\n", Counter);

	CloseHandle(hThread);
}

HWND g_hwnd;
int cxClient, cyClient;
void ThreadProc(PVOID pParam){
	HBRUSH hBrush;
	HDC hdc;
	int xLeft, xRight, yTop, yBottom, iRed, iGreen, iBlue;
	while (TRUE){
		if (cxClient != 0 || cyClient != 0){
			xLeft = rand() % cxClient;
			xRight = rand() % cxClient;
			yTop = rand() % cyClient;
			yBottom = rand() % cyClient;
			iRed = rand() % 255;
			iGreen = rand() % 255;
			iBlue = rand() % 255;

			hdc = GetDC(g_hwnd);

			hBrush = CreateSolidBrush(RGB(iRed, iGreen, iBlue));
			hBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Rectangle(hdc, min(xLeft, xRight), max(xLeft, xRight), min(yTop, yBottom), max(yTop, yBottom));

			hBrush = (HBRUSH)SelectObject(hdc, hBrush);
			DeleteObject(hBrush);

			ReleaseDC(g_hwnd, hdc);

			Sleep(100);
		}
	}

	_endthread();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	PAINTSTRUCT ps;
	//RECT rect;
	TCHAR szStr[512];

	switch (Msg) {
	case WM_CREATE:
		g_hwnd = hWnd;
		srand((unsigned int)time(NULL));
		_beginthread(ThreadProc, 0, NULL);
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		wsprintf(szStr, TEXT("%d %d"), cxClient, cyClient);
		TextOut(hdc, 0, 0, szStr, lstrlen(szStr));

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void fun4(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow){
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
		return ;
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
}

typedef struct {
	HWND hwnd;
	int cxClient;
	int cyClient;
	int cyChar;
	BOOL bKill;
} PARAMS, *PPARAMS;

int CheckBottom(HWND hwnd, int cyClient, int cyChar, int iLine) {
	if (iLine * cyChar + cyChar > cyClient) {
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		iLine = 0;
	}
	return iLine;
}

void Thread1(PVOID pvoid) {
	HDC hdc;
	int iNum = 0, iLine = 0;
	PPARAMS pparams = (PPARAMS)pvoid;
	TCHAR szBuffer[16];

	while (!pparams->bKill) {
		if (iNum < 0) {
			iNum = 0;
		}
		iLine = CheckBottom(pparams->hwnd, pparams->cyClient, pparams->cyChar, iLine);

		hdc = GetDC(pparams->hwnd);

		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer, 
			wsprintf(szBuffer, TEXT("%d"), iNum++));

		ReleaseDC(pparams->hwnd, hdc);

		iLine++;
		Sleep(100);
	}
	_endthread();
}

LRESULT CALLBACK WndProc1(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	static PARAMS params;
	switch (message) {
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread1, 0, (void*)&params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void Thread2(PVOID pvoid) {

	_endthread();
}

LRESULT CALLBACK WndProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	static PARAMS params;
	switch (message) {
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread2, 0, (void*)&params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void Thread3(PVOID pvoid) {

	_endthread();
}

LRESULT CALLBACK WndProc3(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	static PARAMS params;
	switch (message) {
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread3, 0, (void*)&params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void Thread4(PVOID pvoid) {

	_endthread();
}

LRESULT CALLBACK WndProc4(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	static PARAMS params;
	switch (message) {
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyClient = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread4, 0, (void*)&params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}



LRESULT CALLBACK WndProc0(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	static HWND hwndChild[4];
	static TCHAR *szChildClass[] = {
		TEXT("Child1"), TEXT("Child2"), TEXT("Child3"), TEXT("Child4")
	};
	static WNDPROC ChildProc[] = {
		WndProc1, WndProc2, WndProc3, WndProc4
	};
	HINSTANCE hInstance;
	int i, cxClient, cyClient;
	WNDCLASS wndclass;

	switch (Msg) {
	case WM_CREATE:
		hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hInstance = hInstance;
		wndclass.lpszMenuName = NULL;
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		for (i = 0; i < 4; ++i){
			wndclass.lpfnWndProc = ChildProc[i];
			wndclass.lpszClassName = szChildClass[i];

			RegisterClass(&wndclass);

			hwndChild[i] = CreateWindow( szChildClass[i],
				NULL, 
				WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE,
				0, 0, 0, 0,
				hWnd, (HMENU)i, hInstance, NULL);
		}
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		for (i = 0; i < 4; ++i){
			MoveWindow(hwndChild[i], 
				(i%2)*cxClient/2, (i>1)*cyClient/2,
				cxClient/2, cyClient/2, TRUE);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam){
		case VK_ESCAPE:
			for (i = 0; i < 4; ++i){
				DestroyWindow(hwndChild[i]);
			}
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_PAINT:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void fun5(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow){

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
	wc.lpfnWndProc = WndProc0;
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szClassName, MB_OK);
		return;
	}

	hWnd = CreateWindow(szClassName,
		TEXT("four child windows"),
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
}