
#ifndef _CALCULATIONFUNC_H_
#define _CALCULATIONFUNC_H_

#include <stdio.h>
#include <windows.h>

void WMCreate(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void DrawPanel(HDC hdc);
void WMCommand(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

#endif