#ifndef CONFIG
#define CONFIG
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
#include <windows.h>
#include <atlstr.h>
#include <math.h>
#include "angle.h"
#include "demon.h"
#include "elf.h"
#include "dataStructure.h"
using namespace std;

extern angle angle1;
extern demon demons[NUM];
extern elf elfs[ELFNUM];

string WChar2Ansi(LPCWSTR pwszSrc);
string CString2string(CString cs);
CString getAppPath();
bool gameConfig(string& szFileName);
SPEED generateRandomSpeed();

#endif