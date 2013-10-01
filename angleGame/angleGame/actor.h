#pragma once
#include "dataStructure.h"
class actor
{
protected:
	LPDIRECT3DVERTEXBUFFER9 buffer;

public:
	actor(void);
    ~actor(void);
	virtual void init(CUSTOMVETIX a[]){}
	virtual void Render(LPDIRECT3DDEVICE9 d3ddev){}
	virtual void Update(){}
	virtual void createBuffer(LPDIRECT3DDEVICE9 d3ddev){}
};
