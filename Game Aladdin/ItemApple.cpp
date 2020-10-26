#include "ItemApple.h"

ItemApple::ItemApple(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::apple);
	
}

void ItemApple::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Apple = new Texture(L"Item.png", D3DCOLOR_XRGB(248, 0, 248), d3dd9);
	LPSPRITE Idle = new Sprite(341, 17, 352, 29, Apple->LPDIRECT3DTEXTURE());
	Animation* Apple1 = new Animation();
	Apple1->AddFrame(Idle, 200);
	Apple1->SetRepeat(true);
	this->GetAnimations()->AddAnimation(Apple1, 0);
	this->GetAnimations()->Start(0);
}
