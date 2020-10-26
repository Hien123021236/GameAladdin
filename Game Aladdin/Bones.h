#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
class Bones:public Object
{
public:
	Bones();
	Bones(float x, float y, float width, float height);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Bones::Update(DWORD dt);
	void Fly(D3DXVECTOR2 V);
	~Bones();
};
typedef Bones* LPBONE;
