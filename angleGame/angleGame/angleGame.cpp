#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include <d3dx9.h>
#include<string>
#include <atlstr.h>
#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include <Mmsystem.h>
#include "config.h"
using namespace std;
//include the Direct3D library file
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
//screen resolution
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CUSTOMFVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
//the pointer to our Direct3D interface
LPDIRECT3D9 d3d;
//the pointer to the device class
LPDIRECT3DDEVICE9 d3ddev;

SPEED dSpeed;
SPEED eSpeed;
angle angle1;
float frameTime;
demon demons[NUM];
elf elfs[ELFNUM];

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
void updateFrame(float elapsedTime);
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
		static unsigned int updateTimer=timeGetTime();
		unsigned int curTime=timeGetTime();
		if(curTime<updateTimer+10){
			Sleep(0);
			continue;
		}
        frameTime=(curTime-updateTimer)*0.1f;
		updateTimer=curTime;
		updateFrame(frameTime);
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
	//case WM_KEYUP:

	case WM_KEYDOWN:
		{
			if(KEY_DOWN(VK_UP) && KEY_DOWN(VK_LEFT))
			{
				angle1.upMove(frameTime);
				angle1.leftMove(frameTime);
				angle1.Update();
				break;
			}
			if(KEY_DOWN(VK_UP) && KEY_DOWN(VK_RIGHT)){
				angle1.upMove(frameTime);
				angle1.rightMove(frameTime);
				angle1.Update();
				break;
			}
			if(KEY_DOWN(VK_DOWN) && KEY_DOWN(VK_RIGHT)){
				angle1.downMove(frameTime);
				angle1.rightMove(frameTime);
				angle1.Update();
				break;
			}
			if(KEY_DOWN(VK_DOWN) && KEY_DOWN(VK_LEFT)){
				angle1.downMove(frameTime);
				angle1.leftMove(frameTime);
				angle1.Update();
				break;
			}
			if(KEY_DOWN(VK_DOWN)){
				downMove();
				break;
			}
			if(KEY_DOWN(VK_UP)){
				upMove();
				break;
			}
			if(KEY_DOWN(VK_LEFT)){
				leftMove();
				break;
			}
			if(KEY_DOWN(VK_RIGHT)){
				rightMove();
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
	//init angle, demon, elf
	angle1.createBuffer(d3ddev);
	for(int i=0;i<NUM;i++){
		demons[i].createBuffer(d3ddev);
	}
	for(int i=0;i<ELFNUM;i++){
		elfs[i].createBuffer(d3ddev);
	}
}

void renderFrame()
{
	//clear a buffer to a deep black,D3DCLEAR_TARGET: indicates that we should clear the back buffer
	d3ddev->Clear(0,NULL,D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0,0,0),1.0f,0);
	d3ddev->BeginScene();//do 3d rendering on the back buffer here
	d3ddev->SetFVF(CUSTOMFVF);
	D3DXMATRIX matTranslate;
	static float demonx=0.0f;
	static float demony=0.0f;
	D3DXMatrixTranslation(&matTranslate,demonx,demony,0.0f);
	d3ddev->SetTransform(D3DTS_WORLD,&matTranslate);
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,&D3DXVECTOR3(0.0f,0.0f,100.0f),
		&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,1.0f,0.0f));
	d3ddev->SetTransform(D3DTS_VIEW,&matView);
	D3DXMATRIX matProject;
	D3DXMatrixPerspectiveFovLH(&matProject,D3DXToRadian(60),(FLOAT)SCREEN_WIDTH/(FLOAT)SCREEN_HEIGHT,1.0f,100.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION,&matProject);//

	angle1.Render(d3ddev);
	for(int i=0;i<NUM;i++){
		demons[i].Render(d3ddev);
	}
	for(int i=0;i<ELFNUM;i++){
		elfs[i].Render(d3ddev);
	}
	d3ddev->EndScene();
	d3ddev->Present(NULL,NULL,NULL,NULL);//display the created frame on the screen
}

void cleanD3d()
{
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
	angle1.rightMove(frameTime);
	angle1.Update();
}

void leftMove()
{
	angle1.leftMove(frameTime);
	angle1.Update();
}

void upMove()
{
	angle1.upMove(frameTime);
	angle1.Update();
}

void downMove()
{
	angle1.downMove(frameTime);
	angle1.Update();
}

void downMoveForElf(CUSTOMVETIX elft[])
{

}

void updateFrame(float elapsedTime){
	for(int i=0;i<NUM;i++){
		demons[i].move(elapsedTime);
		demons[i].Update();
	}
	for(int i=0;i<ELFNUM;i++){
		elfs[i].move(elapsedTime);
		elfs[i].Update();
	}
}