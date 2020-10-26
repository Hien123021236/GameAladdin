#include "NewScreen.h"

NewScreen::NewScreen(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight+21));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::newscreen);
}

void NewScreen::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
}

void NewScreen::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE screen = new Texture(L"map.png", D3DCOLOR_XRGB(163, 73, 164), d3dd9);
	//Animation Enemy1 Idle
	LPSPRITE sprite = new Sprite(2193, 1145, 2271, 1352, screen->LPDIRECT3DTEXTURE());
	Animation* next  = new Animation();
	next->AddFrame(sprite, 200);
	this->GetAnimations()->AddAnimation(next,0);
	this->animations->Start(0);
}
