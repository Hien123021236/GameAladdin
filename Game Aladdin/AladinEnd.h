#pragma once
#include"Object.h"
class AladinEnd : public Object
{
public:
	AladinEnd(float x, float y, float width, float height);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Update(DWORD dt);
	void Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler);
	void Win();
	D3DXVECTOR2 GetPos(){
		D3DXVECTOR2 pos;
		pos.x = this->BottomPosition()->x;
		pos.y = this->BottomPosition()->y;
		return pos;
	}
};

