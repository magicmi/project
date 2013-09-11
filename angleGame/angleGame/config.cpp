#include "config.h"
#include <stdlib.h>
#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include <time.h>

string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen<= 0) 
	{
		return string("");
	}
	char* pszDst = new char[nLen];
	if (NULL == pszDst)
	{
		return string("");
	}
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	string strTemp(pszDst);
	delete [] pszDst;
	return strTemp;
}

string CString2string(CString cs)
{
	string str=WChar2Ansi(cs.GetBuffer(cs.GetLength()));
	return str;
}

CString getAppPath()
{
	TCHAR modulePath[MAX_PATH];
	GetModuleFileName(NULL,modulePath,MAX_PATH);
	CString strModulePath(modulePath);
	strModulePath=strModulePath.Left(strModulePath.ReverseFind(_T('\\')));
	return strModulePath;

}

bool gameConfig(string &szFileName)
{
	const char *xAttribute;
	const char *yAttribute;
	const char *zAttribute;
	const char *rhwAttribute;
	const char *rAttribute;
	const char *gAttribute;
	const char *bAttribute;
	float x,y,z,rhw;
	int r,g,b;	
	try{
		string seperator="\\";
		//string fullPath = getAppPath().GetBuffer(0)+seperator+szFileName;
		string fullPath = CString2string(getAppPath())+seperator+szFileName;
		//create a object for TiXmlDocument
		TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
		myDocument->LoadFile();
		TiXmlElement *RootElement = myDocument->RootElement();
		TiXmlElement *angle = RootElement->FirstChildElement();
		TiXmlElement *vertex = angle->FirstChildElement();
		//config the coordinates and color for angle
		for(int i=0;i<=2;i++)
		{
			xAttribute=vertex->Attribute("x");
			yAttribute=vertex->Attribute("y");
			zAttribute=vertex->Attribute("z");
			rhwAttribute=vertex->Attribute("rhw");
			rAttribute=vertex->Attribute("r");
			gAttribute=vertex->Attribute("g");
			bAttribute=vertex->Attribute("b");
			x=(float)atof(xAttribute);
			y=(float)atof(yAttribute);
			z=(float)atof(zAttribute);
			rhw=(float)atof(rhwAttribute);
			r=atoi(rAttribute);
			g=atoi(gAttribute);
			b=atoi(bAttribute);
			angles[i].x=x;angles[i].y=y;angles[i].z=z;angles[i].rhw=rhw;
			angles[i].color=D3DCOLOR_XRGB(r,g,b);	
			vertex=vertex->NextSiblingElement();
		}
aSpeed=generateRandomSpeed();
		//config the coordinates and color for demon
		TiXmlElement *demon=angle->NextSiblingElement();
		vertex=demon->FirstChildElement();
		for(int i=0;i<=3;i++)
		{
			xAttribute=vertex->Attribute("x");
			yAttribute=vertex->Attribute("y");
			zAttribute=vertex->Attribute("z");
			rhwAttribute=vertex->Attribute("rhw");
			rAttribute=vertex->Attribute("r");
			gAttribute=vertex->Attribute("g");
			bAttribute=vertex->Attribute("b");
			x=(float)atof(xAttribute);
			y=(float)atof(yAttribute);
			z=(float)atof(zAttribute);
			rhw=(float)atof(rhwAttribute);
			r=atoi(rAttribute);
			g=atoi(gAttribute);
			b=atoi(bAttribute);
			demons[i].x=x;demons[i].y=y;demons[i].z=z;demons[i].rhw=rhw;
			demons[i].color=D3DCOLOR_XRGB(r,g,b);	
			vertex=vertex->NextSiblingElement();
		}
		dSpeed=generateRandomSpeed();
		//config the coordinates and color for elf
		TiXmlElement *elf=demon->NextSiblingElement();
		vertex=elf->FirstChildElement();
		for(int i=0;i<=3;i++)
		{
			xAttribute=vertex->Attribute("x");
			yAttribute=vertex->Attribute("y");
			zAttribute=vertex->Attribute("z");
			rhwAttribute=vertex->Attribute("rhw");
			rAttribute=vertex->Attribute("r");
			gAttribute=vertex->Attribute("g");
			bAttribute=vertex->Attribute("b");
			x=(float)atof(xAttribute);
			y=(float)atof(yAttribute);
			z=(float)atof(zAttribute);
			rhw=(float)atof(rhwAttribute);
			r=atoi(rAttribute);
			g=atoi(gAttribute);
			b=atoi(bAttribute);
			elfs[i].x=x;elfs[i].y=y;elfs[i].z=z;elfs[i].rhw=rhw;
			elfs[i].color=D3DCOLOR_XRGB(r,g,b);
			vertex=vertex->NextSiblingElement();
		}
		eSpeed=generateRandomSpeed();
		
	}
	catch(string &e)
	{
		return false;
	}
	return true;
}

SPEED generateRandomSpeed()
{
	SPEED speed;
	srand(time(NULL));
	float x,y,z;
	x=(float)(rand()%10)/10.0f;
	y=(float)(rand()%10)/10.0f;
	z=0.5f;
	speed.x=x;speed.y=y;speed.z=z;
	return speed;
}