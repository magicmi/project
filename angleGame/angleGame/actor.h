#pragma once
#include "dataStructure.h"
class actor
{
protected:
	LPDIRECT3DVERTEXBUFFER9 buffer;
	IDirect3DIndexBuffer9* indexBuffer;
    POSITION position;
	SPEED s;
	CUSTOMVETIX *a;
	CUSTOMVETIX *b;
	WORD *index;
    float radius;
	int vertexNum;
	int indexNum;
	int triNum;
	bool isLive;
public:
	actor(void);
    ~actor(void);
	void init(SPEED s,CUSTOMVETIX a[],int length,POSITION p,float radius);
	void Render(LPDIRECT3DDEVICE9 d3ddev);
    void Update();
	void createBuffer(LPDIRECT3DDEVICE9 d3ddev);
	int getVertexNum();
	void move(float elapsedTime);
	bool isCollided(actor* otherActor);
	void setDeath();
	bool getLiveInfo();
};
