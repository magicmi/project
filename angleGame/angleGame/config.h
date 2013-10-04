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

string WChar2Ansi(LPCWSTR pwszSrc);
string CString2string(CString cs);
CString getAppPath();
bool gameConfig(string& szFileName,angle* angle1,demon* demons[],elf* elfs[]);
SPEED generateRandomSpeed();
POSITION generatePosition(TiXmlElement *vertex);
#endif