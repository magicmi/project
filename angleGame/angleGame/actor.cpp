#include "actor.h"
#include <math.h>
actor::actor(void)
{	
}
actor::~actor(void)
{
}
void actor::init(SPEED s,CUSTOMVETIX a[],int length,POSITION p,float radius){
	memcpy(this->a,a,length*sizeof(CUSTOMVETIX));
	this->position=p;
	this->s=s;
	this->radius=radius;
}

void actor::createBuffer(LPDIRECT3DDEVICE9 d3ddev){
	for(int i=0;i<vertexNum;i++){
		this->b[i].x=position.x+a[i].x;
		this->b[i].y=position.y+a[i].y;
		this->b[i].z=position.z+a[i].z;
		this->b[i].color=a[i].color;
	}
	VOID** pVoid2;
	d3ddev->CreateVertexBuffer(vertexNum*sizeof(CUSTOMVETIX),0,CUSTOMFVF,D3DPOOL_MANAGED,&buffer,NULL);
	buffer->Lock(0,0,(void**)&pVoid2,0);
	//memcpy(pVoid2,b,sizeof(b));
	/*
	do not make a pointer be a identify for a size of memory
	*/
	memcpy(pVoid2,b,vertexNum*sizeof(CUSTOMVETIX));
	buffer->Unlock();

	d3ddev->CreateIndexBuffer(indexNum*sizeof(WORD),0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&indexBuffer,NULL);
	VOID** elfIndices;
	indexBuffer->Lock(0,sizeof(index),(void**)&elfIndices,0);
	memcpy(elfIndices,index,indexNum*sizeof(WORD));
	indexBuffer->Unlock();
}

void actor::Render(LPDIRECT3DDEVICE9 d3ddev){
	if(this->isLive==true){
		d3ddev->SetStreamSource(0,buffer,0,sizeof(CUSTOMVETIX));
		d3ddev->SetIndices(indexBuffer);
		d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,vertexNum,0,triNum);
	}
}

void actor::Update(){
	if(this->isLive==true){
		for(int i=0;i<vertexNum;i++){
			this->b[i].x=position.x+a[i].x;
			this->b[i].y=position.y+a[i].y;
			this->b[i].z=position.z+a[i].z;
			this->b[i].color=a[i].color;
		}
		VOID** pVoid;
		buffer->Lock(0,0,(void**)&pVoid,0);
		memcpy(pVoid,b,vertexNum*sizeof(CUSTOMVETIX));
		buffer->Unlock();
	}
}

int actor::getVertexNum(){
	return this->vertexNum;
}

void actor::move(float elapsedTime){
	if(this->isLive==true){
		float temp;
		this->position.x+=s.x*elapsedTime;
		this->position.y+=s.y*elapsedTime;
		if(this->position.y+radius>=YSCOPE){
			temp=s.y;
			s.y=-temp;
			this->position.y=YSCOPE-radius;
		}
		if(this->position.y-radius<=(-YSCOPE)){
			temp=s.y;
			s.y=-temp;
			this->position.y=-YSCOPE+radius;
		}
		if(this->position.x+radius>=XSCOPE){
			temp=s.x;
			s.x=-temp;
			this->position.x=XSCOPE-radius;
		}
		if(this->position.x-radius<=(-XSCOPE)){
			temp=s.x;
			s.x=-temp;
			this->position.x=-XSCOPE+radius;
		}
	}
}

bool actor::isCollided(actor* otherActor){
	bool flag=false;
	float distance;
	distance=pow(pow((this->position.x-otherActor->position.x),2)+pow((this->position.y-otherActor->position.y),2),0.5f);
	if(this->radius+otherActor->radius>=distance){
		flag=true;
	}
	return flag;
}

void actor::setDeath(){
	this->isLive=false;
}

bool actor::getLiveInfo(){
	return this->isLive;
}