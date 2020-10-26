#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
class Rock :public Object
{
private:
	int delaytime=0;
	int time;
	
public:
	Rock(int x, int y, int wight, int hight,int delay);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Update(DWORD dt);

};

