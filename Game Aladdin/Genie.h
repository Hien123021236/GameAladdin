#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
class Genie :public Object
{
public:
	enum ANIMATIONS {
	idle,
	die
	};
	Genie(int x, int y, int wight, int hight);
	void Update(DWORD dt);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Die();
};

