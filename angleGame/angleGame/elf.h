#pragma once
#include "actor.h"

class elf :
	public actor
{
	IDirect3DIndexBuffer9* indexBuffer;
	CUSTOMVETIX a[4];
	SPEED s;
public:

	elf(void)
	{
	}

	virtual ~elf(void)
	{
	}

	void init(CUSTOMVETIX a[],SPEED s);
	void Render(LPDIRECT3DDEVICE9 d3ddev);
	void Update();
	void createBuffer(LPDIRECT3DDEVICE9 d3ddev);
	void move(float elapsedTime);
};
