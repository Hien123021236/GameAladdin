#pragma once
#include"Object.h"
class Pillar :public Object
{
public:
	Pillar(float x, float y, float width, float height);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
};
