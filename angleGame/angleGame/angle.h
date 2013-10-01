#pragma once
#include "actor.h"
#define ANGLESPEED 2.0f
class angle :
	public actor
{
	CUSTOMVETIX a[3];
public:
	angle(void);
	~angle(void);
	void init(CUSTOMVETIX a[]);
	void Render(LPDIRECT3DDEVICE9 d3ddev);
	void Update();
	void createBuffer(LPDIRECT3DDEVICE9 d3ddev);
	void rightMove(float elapsedTime);
	void leftMove(float elapsedTime);
	void upMove(float elapsedTime);
	void downMove(float elapsedTime);
};
