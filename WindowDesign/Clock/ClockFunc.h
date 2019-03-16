#pragma once

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ID_TIMER1 1

void wm_create();

void setClient(int cx, int cy);
//ª≠÷”≈Ã
void DrawClockPlate(HDC hdc);

//ª≠±Ì’Î
void DrawHand(HDC hdc);
