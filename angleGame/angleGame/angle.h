#pragma once
#include "actor.h"
#define ANGLESPEED 2.0f
class angle :
	public actor
{
	bool colorAble;
public:
	angle(void);
	~angle(void);
	void rightMove(float elapsedTime);
	void leftMove(float elapsedTime);
	void upMove(float elapsedTime);
	void downMove(float elapsedTime);
	void expand();//expand 3 times
	void changeColor();
	void changeColorAble(bool flag);
	bool getColorInfo();
};
