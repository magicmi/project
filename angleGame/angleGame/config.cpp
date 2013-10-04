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

bool gameConfig(string &szFileName,angle* angle1,demon* demons[],elf* elfs[])
{
	const char *xAttribute;
	const char *yAttribute;
	const char *zAttribute;
	const char *rAttribute;
	const char *gAttribute;
	const char *bAttribute;
    CUSTOMVETIX a[3];
	CUSTOMVETIX d[4];
	CUSTOMVETIX e[4];
	float x,y,z;
	int r,g,b;	
	float radius;
	POSITION p;
	try{
		string seperator="\\";
		//string fullPath = getAppPath().GetBuffer(0)+seperator+szFileName;
		string fullPath = CString2string(getAppPath())+seperator+szFileName;
		//create a object for TiXmlDocument
		TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
		myDocument->LoadFile();
		TiXmlElement *RootElement = myDocument->RootElement();
		TiXmlElement *anglep = RootElement->FirstChildElement();
		radius=(float)atof(anglep->Attribute("radius"));
		TiXmlElement *vertex = anglep->FirstChildElement();
		p=generatePosition(vertex);
		vertex=vertex->NextSiblingElement();
		//config the coordinates and color for angle
		for(int i=0;i<=2;i++)
		{
			xAttribute=vertex->Attribute("x");
			yAttribute=vertex->Attribute("y");
			zAttribute=vertex->Attribute("z");
			rAttribute=vertex->Attribute("r");
			gAttribute=vertex->Attribute("g");
			bAttribute=vertex->Attribute("b");
			x=(float)atof(xAttribute);
			y=(float)atof(yAttribute);
			z=(float)atof(zAttribute);
			r=atoi(rAttribute);
			g=atoi(gAttribute);
			b=atoi(bAttribute);
			a[i].x=x;a[i].y=y;a[i].z=z;
			a[i].color=D3DCOLOR_XRGB(r,g,b);
			vertex=vertex->NextSiblingElement();
		}
		//angle tangle();
		angle1->init(generateRandomSpeed(),a,angle1->getVertexNum(),p,radius);
		//config the coordinates and color for demon
		TiXmlElement *demonp=anglep->NextSiblingElement();
		radius=(float)atof(demonp->Attribute("radius"));
		vertex=demonp->FirstChildElement();
        p=generatePosition(vertex);
		vertex=vertex->NextSiblingElement();
		for(int i=0;i<=3;i++)
		{
			xAttribute=vertex->Attribute("x");
			yAttribute=vertex->Attribute("y");
			zAttribute=vertex->Attribute("z");
			rAttribute=vertex->Attribute("r");
			gAttribute=vertex->Attribute("g");
			bAttribute=vertex->Attribute("b");
			x=(float)atof(xAttribute);
			y=(float)atof(yAttribute);
			z=(float)atof(zAttribute);
			r=atoi(rAttribute);
			g=atoi(gAttribute);
			b=atoi(bAttribute);
			d[i].x=x;d[i].y=y;d[i].z=z;
			d[i].color=D3DCOLOR_XRGB(r,g,b);	
			vertex=vertex->NextSiblingElement();
		}
		for(int i=0;i<NUM;i++){
			demons[i]->init(generateRandomSpeed(),d,demons[i]->getVertexNum(),p,radius);
			//demons[i].init(d,generateRandomSpeed());
		}
		//dSpeed=generateRandomSpeed();
		//config the coordinates and color for elf
		TiXmlElement *elfp=demonp->NextSiblingElement();
		radius=(float)atof(elfp->Attribute("radius"));
		vertex=elfp->FirstChildElement();
		p=generatePosition(vertex);
		vertex=vertex->NextSiblingElement();
		for(int i=0;i<=3;i++)
		{
			xAttribute=vertex->Attribute("x");
			yAttribute=vertex->Attribute("y");
			zAttribute=vertex->Attribute("z");
			rAttribute=vertex->Attribute("r");
			gAttribute=vertex->Attribute("g");
			bAttribute=vertex->Attribute("b");
			x=(float)atof(xAttribute);
			y=(float)atof(yAttribute);
			z=(float)atof(zAttribute);
			r=atoi(rAttribute);
			g=atoi(gAttribute);
			b=atoi(bAttribute);	
			e[i].x=x;e[i].y=y;e[i].z=z;
			e[i].color=D3DCOLOR_XRGB(r,g,b);
			vertex=vertex->NextSiblingElement();
		}
		for(int i=0;i<ELFNUM;i++){
			elfs[i]->init(generateRandomSpeed(),e,elfs[i]->getVertexNum(),p,radius);
		}

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
	//make the seed subtle by hardware precision counter
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);
	//srand(time(NULL));
	float x,y;
	float i=-1;
	x=(float)(rand()%10)/SPEEDPRECION*pow(i,rand()%2+1);
	y=(float)(rand()%10)/SPEEDPRECION*pow(i,rand()%2+1);
	speed.x=x;speed.y=y;
	return speed;
}

POSITION generatePosition(TiXmlElement *vertex){
    POSITION p;
	p.x=(float)atof(vertex->Attribute("x"));
	p.y=(float)atof(vertex->Attribute("y"));
	p.z=(float)atof(vertex->Attribute("z"));
	return p;
}