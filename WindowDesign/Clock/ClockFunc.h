#pragma once

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ID_TIMER1 1

void wm_create();

void setClient(int cx, int cy);
//������
void DrawClockPlate(HDC hdc);

//������
void DrawHand(HDC hdc);
