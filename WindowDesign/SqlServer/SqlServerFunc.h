
#pragma once

//#include <sql.h>
//#include <sqlext.h>
//#include <sqltypes.h>
//#define INITGUID
//#import "c:\program files\common files\system\ado\msado15.dll" \
//	named_guids \
//	rename_namespace("ADOCG") \
//	rename("EOF", "EndOfFile") \
//	rename("BOF","FirstOfFile") \
//	rename("EOF","adoEOF")
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","adoEOF")  
//using namespace ADOCG;

//#include <afx.h>
//#include <afxwin.h>
#include <icrsint.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <winsock2.h>
using namespace std;


void func1();

void func2();