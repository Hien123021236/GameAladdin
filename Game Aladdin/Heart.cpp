#include "Heart.h"
Heart::Heart(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::heart);
}

void Heart::Update(DWORD dt)
{
	if (this->exist == true) {
		if (animations != nullptr) {
			animations->Update(dt);
		}
	}
}

void Heart::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Heart = new Texture(L"Item.png", D3DCOLOR_XRGB(248, 0, 248), d3dd9);
	LPSPRITE Idle1 = new Sprite(343, 171, 362, 195, Heart->LPDIRECT3DTEXTURE());
	LPSPRITE Idle2 = new Sprite(366, 173, 383, 196, Heart->LPDIRECT3DTEXTURE());
	LPSPRITE Idle3 = new Sprite(387, 175, 403, 196, Heart->LPDIRECT3DTEXTURE());
	LPSPRITE Idle4 = new Sprite(406, 175, 423, 196, Heart->LPDIRECT3DTEXTURE());
	LPSPRITE Idle5 = new Sprite(426, 173, 445, 196, Heart->LPDIRECT3DTEXTURE());
	LPSPRITE Idle6 = new Sprite(448, 174, 465, 196, Heart->LPDIRECT3DTEXTURE());
	LPSPRITE Idle7 = new Sprite(467, 176, 483, 197, Heart->LPDIRECT3DTEXTURE());
	LPSPRITE Idle8 = new Sprite(486, 176, 503, 197, Heart->LPDIRECT3DTEXTURE());

	Animation * Heart_idle = new Animation();
	Heart_idle->AddFrame(Idle1, 100);
	Heart_idle->AddFrame(Idle2, 100);
	Heart_idle->AddFrame(Idle3, 100);
	Heart_idle->AddFrame(Idle4, 100);
	Heart_idle->AddFrame(Idle5, 100);
	Heart_idle->AddFrame(Idle6, 100);
	Heart_idle->AddFrame(Idle7, 100);
	Heart_idle->AddFrame(Idle8, 100);

	Heart_idle->SetRepeat(true);
	this->GetAnimations()->AddAnimation(Heart_idle, 0);
	this->GetAnimations()->Start(0);
}

