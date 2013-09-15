#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include <d3dx9.h>
#include<string>
#include <atlstr.h>
#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include "config.h"
using namespace std;
//include the Direct3D library file
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
//screen resolution
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CUSTOMFVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define ANGLESPEED 2.0f

//the pointer to our Direct3D interface
LPDIRECT3D9 d3d;
//the pointer to the device class
LPDIRECT3DDEVICE9 d3ddev;
LPDIRECT3DVERTEXBUFFER9 angleBuffer;//the buffer to save vertex of angle
LPDIRECT3DVERTEXBUFFER9 demonBuffer;//the buffer to save vertex of demon
IDirect3DIndexBuffer9* demonIndexBuffer;//the buffer to save index of demon's vertex
LPDIRECT3DVERTEXBUFFER9 elfBuffer;
IDirect3DIndexBuffer9* elfIndexBuffer;
SPEED dSpeed;
SPEED eSpeed;

CUSTOMVETIX angles[3];
CUSTOMVETIX demons[4];
CUSTOMVETIX elfs[4];
CUSTOMVETIX demonList[10][4];
CUSTOMVETIX elfList[10][4];
void initData(void);//initialize the data for game
void initGraphics(void);//initialize the primitive to be drawn
void initD3d(HWND hWnd);//setup and initializes Direct3D
void renderFrame(void);//render a single frame
void cleanD3d(void);//close Direct3D and release memory
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,LPARAM lParam);
void rightMove(void);//angle go to right
void leftMove(void);//angle go to left
void upMove(void);//angle go to up
void downMove(void);//angle go to down
void downMoveForElf(CUSTOMVETIX elft[]);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;
	ZeroMemory(&wc,sizeof(WNDCLASSEX));
	wc.cbSize=sizeof(WNDCLASSEX);
	wc.style=CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc=WindowProc;
	wc.hInstance=hInstance;
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wc.lpszClassName=L"WindowClass";
	RegisterClassEx(&wc);
	hWnd=CreateWindowEx(NULL,L"WindowClass",L"My First Direct3D program",
		WS_OVERLAPPEDWINDOW,300,100,SCREEN_WIDTH,SCREEN_HEIGHT,NULL,NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	initD3d(hWnd);
	MSG msg;
	while(TRUE)
	{
		while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(msg.message==WM_QUIT)
		{
			break;
		}
		renderFrame();
	}
	cleanD3d();
	return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_RIGHT: 
				{
					rightMove();
				}
				break;
			case VK_LEFT: 
				{
					leftMove();
				}
				break;
			case VK_UP: 
				{
					upMove();
				}
				break;
			case VK_DOWN: 
				{
					downMove();
				}
				break;
			}
		}
		break;
	}
	return DefWindowProc(hWnd,message,wParam,lParam);//process the other message
}

void initD3d(HWND hWnd)
{
	d3d=Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));//clear out the struct for use
	d3dpp.Windowed=TRUE;
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;//discard the old frame
	d3dpp.BackBufferFormat=D3DFMT_X8R8G8B8;//
	d3dpp.BackBufferWidth=SCREEN_WIDTH;//
	d3dpp.BackBufferHeight=SCREEN_HEIGHT;//
	d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);
	initData();
	initGraphics();
	d3ddev->SetRenderState(D3DRS_LIGHTING,FALSE);
}
//initialize the primitive to be drawn
void initGraphics()
{
	//init angle
	d3ddev->CreateVertexBuffer(3*sizeof(CUSTOMVETIX),0,CUSTOMFVF,D3DPOOL_MANAGED,&angleBuffer,NULL);
	VOID** pVoid;
	angleBuffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,angles,sizeof(angles));
	angleBuffer->Unlock();
	//init demon
	VOID** pVoid1;
	d3ddev->CreateVertexBuffer(4*sizeof(CUSTOMVETIX),0,CUSTOMFVF,D3DPOOL_MANAGED,&demonBuffer,NULL);
	demonBuffer->Lock(0,0,(void**)&pVoid1,0);
	memcpy(pVoid1,demons,sizeof(demons));
	demonBuffer->Unlock();

	WORD demonIndex[]={0,2,1,0,1,3};
	d3ddev->CreateIndexBuffer(6*sizeof(WORD),0,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&demonIndexBuffer,NULL);
	VOID** demonIndices;
	demonIndexBuffer->Lock(0,sizeof(demonIndex),(void**)&demonIndices,0);
	memcpy(demonIndices,demonIndex,sizeof(demonIndex));
	demonIndexBuffer->Unlock();
	//init elf
	VOID** pVoid2;
	d3ddev->CreateVertexBuffer(4*sizeof(CUSTOMVETIX),0,CUSTOMFVF,D3DPOOL_MANAGED,&elfBuffer,NULL);
	elfBuffer->Lock(0,0,(void**)&pVoid2,0);
	memcpy(pVoid2,elfs,sizeof(elfs));
	elfBuffer->Unlock();

	WORD elfIndex[]={0,2,1,0,1,3};
	d3ddev->CreateIndexBuffer(6*sizeof(WORD),0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&elfIndexBuffer,NULL);
	VOID** elfIndices;
	elfIndexBuffer->Lock(0,sizeof(elfIndex),(void**)&elfIndices,0);
	memcpy(elfIndices,elfIndex,sizeof(elfIndex));
	elfIndexBuffer->Unlock();
}

void renderFrame()
{
	//clear a buffer to a deep black,D3DCLEAR_TARGET: indicates that we should clear the back buffer
	d3ddev->Clear(0,NULL,D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0,0,0),1.0f,0);
	d3ddev->BeginScene();//do 3d rendering on the back buffer here
	d3ddev->SetFVF(CUSTOMFVF);
	//draw the angle
	d3ddev->SetStreamSource(0,angleBuffer,0,sizeof(CUSTOMVETIX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);
	//draw the demon
	D3DXMATRIX demonMatTranslate;
	static float demonx=0.0f;
	static float demony=0.0f;
	//demonx-=dSpeed.x;
	//demony-=dSpeed.y;
	D3DXMatrixTranslation(&demonMatTranslate,demonx,demony,0.0f);
	d3ddev->SetTransform(D3DTS_WORLD,&demonMatTranslate);
	D3DXMATRIX demonMatView;
	D3DXMatrixLookAtLH(&demonMatView,&D3DXVECTOR3(0.0f,0.0f,100.0f),
		&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,1.0f,0.0f));
	d3ddev->SetTransform(D3DTS_VIEW,&demonMatView);
	D3DXMATRIX demonMatProject;
	D3DXMatrixPerspectiveFovLH(&demonMatProject,D3DXToRadian(60),(FLOAT)SCREEN_WIDTH/(FLOAT)SCREEN_HEIGHT,1.0f,100.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION,&demonMatProject);//
	d3ddev->SetStreamSource(0,demonBuffer,0,sizeof(CUSTOMVETIX));
	d3ddev->SetIndices(demonIndexBuffer);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2);
	//draw the elf
	d3ddev->SetStreamSource(0,elfBuffer,0,sizeof(CUSTOMVETIX));
	d3ddev->SetIndices(elfIndexBuffer);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2);
	/*static int i=0;
	i++;
	for(int j=0;j<i;j++)
	{
	downMoveForElf(elfList[j]);
	d3ddev->SetStreamSource(0,elfBuffer,0,sizeof(CUSTOMVETIX));//use timer 
	d3ddev->SetIndices(elfIndexBuffer);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2);
	}*/
	d3ddev->EndScene();
	d3ddev->Present(NULL,NULL,NULL,NULL);//display the created frame on the screen
}

void cleanD3d()
{
	angleBuffer->Release();
	d3ddev->Release();
	d3d->Release();
}

void initData()
{
	string fileName("config2.xml");
	gameConfig(fileName);
}

void rightMove()
{
	for(int i=0;i<3;i++)
	{
		angles[i].x-=ANGLESPEED;
	}
	VOID** pVoid;
	angleBuffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,angles,sizeof(angles));
	angleBuffer->Unlock();
}

void leftMove()
{
	for(int i=0;i<3;i++)
	{
		angles[i].x+=ANGLESPEED;
	}
	VOID** pVoid;
	angleBuffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,angles,sizeof(angles));
	angleBuffer->Unlock();
}

void upMove()
{
	for(int i=0;i<3;i++)
	{
		angles[i].y+=ANGLESPEED;
	}
	VOID** pVoid;
	angleBuffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,angles,sizeof(angles));
	angleBuffer->Unlock();
}

void downMove()
{
	for(int i=0;i<3;i++)
	{
		angles[i].y-=ANGLESPEED;
	}
	VOID** pVoid;
	angleBuffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,angles,sizeof(angles));
	angleBuffer->Unlock();
}

void downMoveForElf(CUSTOMVETIX elft[])
{
	for(int i=0;i<3;i++)
	{
		elft[i].y-=ANGLESPEED;
	}
	VOID** pVoid;
	elfBuffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,elft,sizeof(elft));
	elfBuffer->Unlock();
}