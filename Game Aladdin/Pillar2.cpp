#include "Pillar2.h"


Pillar2::Pillar2(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2, y + height));
	this->width = width;
	this->height = height;
}

void Pillar2::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE PILLAR2 = new Texture(L"PILLAR2.png", D3DCOLOR_XRGB(163, 73, 164), d3dd9);
	//cột trụ xích
	LPSPRITE sprite = new Sprite(0, 0, 2240, 1152, PILLAR2->LPDIRECT3DTEXTURE());
	Animation* pillar2 = new Animation();
	pillar2->AddFrame(sprite, 0);
	this->animations->AddAnimation(pillar2, 0);
	this->animations->Start(0);
}

void Pillar2::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
}

void Pillar2::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	this->animations->Render(*BottomPosition(), camera, spriteHandler);
}
