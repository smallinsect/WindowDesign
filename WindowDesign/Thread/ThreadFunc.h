
#ifndef _THREADFUNC_H_
#define _THREADFUNC_H_

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <windows.h>

//多线程的运行
void fun1();

//多线的顺序
void fun2();

//_beginthreadex多线程函数
void fun3();

//_beginthread多线程函数
void fun4(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow);

//多工模拟程序
void fun5(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow);

#endif