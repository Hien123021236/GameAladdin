#pragma once
#include"Object.h"
class BackGround2:public Object
{
public:
	BackGround2(float x, float y, float width, float height);
	void init(LPDIRECT3DDEVICE9 d3dd9);
	void update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
};

