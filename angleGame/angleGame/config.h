#ifndef CONFIG
#define CONFIG
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
#include <windows.h>
#include <atlstr.h>
using namespace std;

struct CUSTOMVETIX{
	FLOAT x,y,z,rhw;
	DWORD color;
};
struct SPEED{
	FLOAT x,y,z;
};

extern CUSTOMVETIX angles[3];
extern CUSTOMVETIX demons[4];
extern CUSTOMVETIX elfs[4];
extern SPEED aSpeed;
extern SPEED dSpeed;
extern SPEED eSpeed;

string WChar2Ansi(LPCWSTR pwszSrc);
string CString2string(CString cs);
CString getAppPath();
bool gameConfig(string& szFileName);
SPEED generateRandomSpeed();

#endif