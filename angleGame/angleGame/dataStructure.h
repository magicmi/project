#ifndef DATASTRUCTURE
#define DATASTRUCTURE
#define CUSTOMFVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define NUM 14
#define ELFNUM 20
#define YSCOPE 57
#define XSCOPE 76
#define SPEEDPRECION 80.0f
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
#include <windows.h>
#include <atlstr.h>
#include<d3d9.h>
#include <d3dx9.h>
using namespace std;
struct CUSTOMVETIX{
	FLOAT x,y,z;
	DWORD color;
};
struct SPEED{
	FLOAT x,y;
};
struct POSITION {
	FLOAT x,y,z;
};
#endif