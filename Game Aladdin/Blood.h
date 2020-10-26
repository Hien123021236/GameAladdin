#pragma once
#include"Object.h"
class Blood : public Object
{
public:
	Blood();
	~Blood();
	Blood(float x, float y, float width, float height);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Update(DWORD dt);
	void Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler);
	void BloodBar1();
	void BloodBar2();
	void BloodBar3();
	void BloodBar4();
	void BloodBar5();
	void BloodBar6();
};

