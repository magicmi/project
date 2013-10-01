#include "demon.h"

void demon::init(CUSTOMVETIX a[],SPEED s){
	for(int i=0;i<4;i++)
	{
		(this->a[i]).x=a[i].x;
		(this->a[i]).y=a[i].y;
		(this->a[i]).z=a[i].z;
		(this->a[i]).color=a[i].color;
	}
	this->s=s;
}

void demon::createBuffer(LPDIRECT3DDEVICE9 d3ddev){
	VOID** pVoid1;
	d3ddev->CreateVertexBuffer(4*sizeof(CUSTOMVETIX),0,CUSTOMFVF,D3DPOOL_MANAGED,&buffer,NULL);
	buffer->Lock(0,0,(void**)&pVoid1,0);
	memcpy(pVoid1,a,sizeof(a));
	buffer->Unlock();
	WORD demonIndex[]={0,2,1,0,1,3};
	d3ddev->CreateIndexBuffer(6*sizeof(WORD),0,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&indexBuffer,NULL);
	VOID** demonIndices;
    indexBuffer->Lock(0,sizeof(demonIndex),(void**)&demonIndices,0);
	memcpy(demonIndices,demonIndex,sizeof(demonIndex));
	indexBuffer->Unlock();
}

void demon::Render(LPDIRECT3DDEVICE9 d3ddev){
	d3ddev->SetStreamSource(0,buffer,0,sizeof(CUSTOMVETIX));
	d3ddev->SetIndices(indexBuffer);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2);
}

void demon::Update(){
	VOID** pVoid;
	buffer->Lock(0,0,(void**)&pVoid,0);
	memcpy(pVoid,a,sizeof(a));
	buffer->Unlock();
}

void demon::move(float elapsedTime){
	/*if(a[3].y>Y){
		return;
	}*/
	for(int i=0;i<4;i++){
		a[i].x+=s.x*elapsedTime;
		a[i].y+=s.y*elapsedTime;
	}
	if(a[3].y>=YSCOPE||a[2].y<=(-YSCOPE)){
		float temp=s.y;
		s.y=-temp;
	}
	if(a[1].x>=XSCOPE||a[0].x<=(-XSCOPE)){
		float temp=s.x;
		s.x=-temp;
	}
}