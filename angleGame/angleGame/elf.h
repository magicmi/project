#pragma once
#include "actor.h"

class elf :
	public actor
{
public:

	elf(void)
	{
		this->index=new WORD[6];
		WORD tindex[]={0,2,1,0,1,3};
		memcpy(this->index,tindex,6*sizeof(WORD));
		this->indexNum=6;
		this->vertexNum=4;
		this->triNum=2;
		this->a=new CUSTOMVETIX[this->vertexNum];
		this->b=new CUSTOMVETIX[this->vertexNum];
		this->isLive=true;
	}

	virtual ~elf(void)
	{
	}
};
