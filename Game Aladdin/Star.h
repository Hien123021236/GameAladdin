#pragma once
#include "Object.h"

#define Star_FLY_SPEED 0.3f
class Star : public Object
{
private:
	D3DXVECTOR2* targetPos;
	int status=-1;
	bool isLeft = true;

public:
	int id=-1;
	enum STATUS
	{
		fly,
		explode
	};
	Star(float x, float y, float width, float height);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
	void Start();
	void Explode();
	int Getstatus() { return this->status; }
	void Dive(D3DXVECTOR2* posAladdin);
	
	void SetIsLeft(bool a) { this->isLeft = a; }
	bool GetIsLeft() { return this->isLeft; }
};
typedef Star* LPSTAR;
