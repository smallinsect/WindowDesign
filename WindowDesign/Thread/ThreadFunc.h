
#ifndef _THREADFUNC_H_
#define _THREADFUNC_H_

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <windows.h>

//���̵߳�����
void fun1();

//���ߵ�˳��
void fun2();

//_beginthreadex���̺߳���
void fun3();

//_beginthread���̺߳���
void fun4(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow);

//�๤ģ�����
void fun5(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow);

#endif