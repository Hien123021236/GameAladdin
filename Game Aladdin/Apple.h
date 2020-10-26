#pragma once
#include "Object.h"
#include"Collision.h"
class Apple : public Object
{
public:
	enum ANIMATIONS {
		idle,
		destroy
	};
	Apple();
	Apple(float x, float y, float width, float height,int type);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Apple::Update(DWORD dt, vector<LPOBJECT>*objs);
	void Destroy();
	~Apple();
};

typedef Apple* LPAPPLE;
