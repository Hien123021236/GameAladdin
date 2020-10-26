#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
class ItemApple :public Object
{
public:
	ItemApple(int x, int y, int wight, int hight);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
};

