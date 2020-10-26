#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
class Leash:public Object
{
public:
	Leash(int x, int y, int wight, int hight);
	void Update(DWORD dt);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
};

