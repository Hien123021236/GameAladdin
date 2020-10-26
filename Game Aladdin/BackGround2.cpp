#include "BackGround2.h"

BackGround2::BackGround2(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2+200, y + height+10));

	this->width = width;
	this->height = height;
	this->SetDirection(false, false, false, false);
	
}

void BackGround2::init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE BG = new Texture(L"background2.png", D3DCOLOR_XRGB(186, 254, 202), d3dd9);
	//sao
	LPSPRITE background = new Sprite(0, 0,1500 , 580, BG->LPDIRECT3DTEXTURE());
	Animation* BackG = new Animation();
	BackG->AddFrame(background, 0);
	this->animations->AddAnimation(BackG, 0);
	this->animations->Start(0);
}

void BackGround2::update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
}

void BackGround2::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	this->animations->Render(*BottomPosition(), camera, spriteHandler);
}
