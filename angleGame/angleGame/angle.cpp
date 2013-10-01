#include "angle.h"
angle::angle()
{

}

angle::~angle(void)
{
}

void angle::init(CUSTOMVETIX a[])
{
	for(int i=0;i<3;i++)
	{
		(this->a[i]).x=a[i].x;
		(this->a[i]).y=a[i].y;
		(this->a[i]).z=a[i].z;
		(this->a[i]).color=a[i].color;
	}
}

void angle::createBuffer(LPDIRECT3DDEVICE9 d3ddev){
	d3ddev->CreateVertexBuffer(3*sizeof(CUSTOMVETIX),0,CUSTOMFVF,D3DPOOL_MANAGED,&buffer,NULL);
	VOID** pVoid;
	buffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,a,sizeof(a));
	buffer->Unlock();
}

void angle::Render(LPDIRECT3DDEVICE9 d3ddev)
{
	d3ddev->SetStreamSource(0,buffer,0,sizeof(CUSTOMVETIX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);
}

void angle::Update()
{
	VOID** pVoid;
	buffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,a,sizeof(a));
	buffer->Unlock();
}

void angle::rightMove(float elapsedTime){
	if(a[2].x<=(-XSCOPE)){
		return;
	}
	if((a[2].x-ANGLESPEED*elapsedTime)<(-XSCOPE)){
		a[2].x=-XSCOPE;
		a[1].x=-XSCOPE+6;
		a[0].x=-XSCOPE+6;
		return;
	}
	for(int i=0;i<3;i++)
	{
          a[i].x-=ANGLESPEED*elapsedTime;
	}
}

void angle::leftMove(float elapsedTime){
	if(a[0].x>=XSCOPE)
	{
		return;
	}
	if((a[0].x+ANGLESPEED*elapsedTime)>XSCOPE){
		a[0].x=XSCOPE;
		a[1].x=XSCOPE;
		a[2].x=XSCOPE-6;
		return;
	}
	for(int i=0;i<3;i++)
	{
		a[i].x+=ANGLESPEED*elapsedTime;
	}
}

void angle::upMove(float elapsedTime){
	if(a[1].y>=YSCOPE)
	{
       return;
	}
	if((a[1].y+ANGLESPEED*elapsedTime)>YSCOPE){
		a[1].y=YSCOPE;
		a[0].y=YSCOPE-6;
		a[2].y=YSCOPE-3;
		return;
	}
	for(int i=0;i<3;i++)
	{
		a[i].y+=ANGLESPEED*elapsedTime;
	}
}

void angle::downMove(float elapsedTime){
	if(a[0].y<=(-YSCOPE))
	{
		return;
	}
	if((a[0].y-ANGLESPEED*elapsedTime)<(-YSCOPE)){
		a[0].y=-YSCOPE;
		a[1].y=-YSCOPE+6;
		a[2].y=-YSCOPE+3;
		return;
	}
	for(int i=0;i<3;i++)
	{
		a[i].y-=ANGLESPEED*elapsedTime;
	}
}
