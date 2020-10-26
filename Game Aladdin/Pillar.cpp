#include "Pillar.h"


Pillar::Pillar(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2, y + height));
	this->width = width;
	this->height = height;
}

void Pillar::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE PILLAR = new Texture(L"PILLAR.png", D3DCOLOR_XRGB(255, 255, 255), d3dd9);
	//cột trụ
	LPSPRITE sprite = new Sprite(0, 0, 2240, 1152, PILLAR->LPDIRECT3DTEXTURE());
	Animation* pillar = new Animation();
	pillar->AddFrame(sprite, 0);
	this->animations->AddAnimation(pillar, 0);
	this->animations->Start(0);
}

void Pillar::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
}

void Pillar::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	this->animations->Render(*BottomPosition(), camera, spriteHandler);
}
