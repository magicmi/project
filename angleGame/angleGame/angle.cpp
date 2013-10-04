#include "angle.h"

angle::angle(void)
{
	this->index=new WORD[3];
	WORD tindex[]={0,1,2};
	memcpy(this->index,tindex,3*sizeof(WORD));
	this->indexNum=3;
	this->vertexNum=3;
	this->triNum=1;
	this->a=new CUSTOMVETIX[vertexNum];
	this->b=new CUSTOMVETIX[vertexNum];
	this->isLive=true;
	colorAble=true;
}

angle::~angle(void)
{
}

void angle::rightMove(float elapsedTime){
	if(this->isLive==true){
		if(this->position.x-radius<=(-XSCOPE)){
			return;
		}
		if(this->position.x-radius-ANGLESPEED*elapsedTime<(-XSCOPE)){
			this->position.x=-XSCOPE+radius;
			return;
		}
		this->position.x-=ANGLESPEED*elapsedTime;
	}
}

void angle::leftMove(float elapsedTime){
	if(this->isLive==true){
		if(this->position.x+radius>=(XSCOPE)){
			return;
		}
		if(this->position.x+radius+ANGLESPEED*elapsedTime>XSCOPE){
			this->position.x=XSCOPE-radius;
			return;
		}
		this->position.x+=ANGLESPEED*elapsedTime;
	}
}

void angle::upMove(float elapsedTime){
	if(this->isLive==true){
		if(this->position.y+radius>=YSCOPE){
			return;
		}
		if(this->position.y+radius+ANGLESPEED*elapsedTime>YSCOPE){
			this->position.y=YSCOPE-radius;
			return;
		}
		this->position.y+=ANGLESPEED*elapsedTime;
	}
}

void angle::downMove(float elapsedTime){
	if(this->isLive==true){
		if(this->position.y-radius<=(-YSCOPE)){
			return;
		}
		if(this->position.y-radius-ANGLESPEED*elapsedTime<(-YSCOPE)){
			this->position.y=-YSCOPE+radius;
			return;
		}
		this->position.y-=ANGLESPEED*elapsedTime;
	}
}

void angle::expand(){
	for(int i=0;i<this->vertexNum;i++){
		this->a[i].x*=2.0f;
		this->a[i].y*=2.0f;
		this->a[i].z*=2.0f;
	}
}

void angle::changeColor(){
	if(colorAble==true){
		DWORD tempColor=(this->a[0].color);
		for(int i=0;i<this->vertexNum-1;i++){
			this->a[i].color=this->a[i+1].color;
		}
		this->a[2].color=tempColor;
	}
}

void angle::changeColorAble(bool flag){
	colorAble=flag;
}

bool angle::getColorInfo(){
	return colorAble;
}
