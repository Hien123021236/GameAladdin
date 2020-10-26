#include "AladinEnd.h"

AladinEnd::AladinEnd(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2, y + height));

	this->width = width;
	this->height = height;
	this->SetDirection(false, false, false, false);
}

void AladinEnd::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE texture = new  Texture(L"Aladdin.png", D3DCOLOR_XRGB(255, 0, 255), d3dd9);
	LPSPRITE spritewin0 = new Sprite(1874, 2991, 1939, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin1 = new Sprite(1828, 2988, 1864, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin2 = new Sprite(1780, 2985, 1818, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin3 = new Sprite(1722, 2989, 1770, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin4 = new Sprite(1672, 2987, 1712, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin5 = new Sprite(1625, 2987, 1662, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin6 = new Sprite(1578, 2989, 1615, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin7 = new Sprite(1524, 2986, 1568, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin8 = new Sprite(1465, 2989, 1514, 3048, texture->LPDIRECT3DTEXTURE());
	LPSPRITE spritewin9 = new Sprite(1415, 2987, 1454, 3048, texture->LPDIRECT3DTEXTURE());

	Animation* ani_win = new Animation();
	ani_win->AddFrame(spritewin0, 100);
	ani_win->AddFrame(spritewin1, 100);
	ani_win->AddFrame(spritewin2, 100);
	ani_win->AddFrame(spritewin3, 100);
	ani_win->AddFrame(spritewin4, 100);
	ani_win->AddFrame(spritewin5, 100);
	ani_win->AddFrame(spritewin6, 100);
	ani_win->AddFrame(spritewin7, 100);
	ani_win->AddFrame(spritewin8, 100);
	ani_win->AddFrame(spritewin9, 100);
	ani_win->SetRepeat(true);
	this->GetAnimations()->AddAnimation(ani_win, 0);
	this->animations->Start(0);
}

void AladinEnd::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
		float x = this->BottomPosition()->x + this->wV.x * dt;
		float y = this->BottomPosition()->y + this->wV.y * dt;
		SetBottomPosition(D3DXVECTOR2(x, y));
	}
}

void AladinEnd::Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler)
{
	this->animations->Render(pos, spriteHandler);
}

void AladinEnd::Win()
{
	this->wV.x = -0.1f;
	this->wV.y = 0;

}
