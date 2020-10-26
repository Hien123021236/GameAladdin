#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
#include"Bones.h"
class Skeleton:public Object
{
private:

public:
	LPBONE bones[8];
	Skeleton(int x, int y, int wight, int hight);
	
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Die();
	void Update(DWORD dt);
	void Render( LPCAMERA camera, LPD3DXSPRITE sprite);
	void Explode();
	vector<LPBONE> GetBones();
};

