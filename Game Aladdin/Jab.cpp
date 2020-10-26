#include "Jab.h"

Jab::Jab(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::jab);
}

void Jab::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Jab = new Texture(L"pendulum.png", D3DCOLOR_XRGB(163, 73, 164), d3dd9);
	LPSPRITE sprite1 = new Sprite(11, 153, 60, 188, Jab->LPDIRECT3DTEXTURE());
	LPSPRITE sprite2 = new Sprite(65, 153, 114, 188, Jab->LPDIRECT3DTEXTURE());
	LPSPRITE sprite3 = new Sprite(123, 153, 172, 188, Jab->LPDIRECT3DTEXTURE());
	LPSPRITE sprite4 = new Sprite(184, 153, 233, 188, Jab->LPDIRECT3DTEXTURE());
	LPSPRITE sprite5 = new Sprite(241, 153, 290, 188, Jab->LPDIRECT3DTEXTURE());
	LPSPRITE sprite6 = new Sprite(298, 153, 347, 188, Jab->LPDIRECT3DTEXTURE());

	Animation* ani_jab = new Animation();
	ani_jab->AddFrame(sprite1, 1000);
	ani_jab->AddFrame(sprite2, 50);
	ani_jab->AddFrame(sprite3, 50);
	ani_jab->AddFrame(sprite4, 50);
	ani_jab->AddFrame(sprite5, 50);
	ani_jab->AddFrame(sprite6, 1000);
	ani_jab->SetRepeat(true);
	this->GetAnimations()->AddAnimation(ani_jab, 0);

	this->animations->Start(0);
}

void Jab::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
}
