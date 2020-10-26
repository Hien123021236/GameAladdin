#include "Leash.h"

Leash::Leash(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::leash);

}

void Leash::Update(DWORD dt)
{
	
}

void Leash::Init(LPDIRECT3DDEVICE9 d3dd9)
{
}
