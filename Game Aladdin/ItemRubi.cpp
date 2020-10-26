#include "ItemRubi.h"

ItemRubi::ItemRubi(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::rubi);
	this->exist = true;
}

void ItemRubi::Update(DWORD dt)
{
	if (this->exist == true) {
		if (animations != nullptr) {
			animations->Update(dt);
		}
	}
}

void ItemRubi::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Rubi = new Texture(L"Item.png", D3DCOLOR_XRGB(248, 0, 248), d3dd9);
	LPSPRITE Idle1 = new Sprite(340, 111, 357, 127, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle2 = new Sprite(363, 111, 380, 127, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle3 = new Sprite(386, 111, 403, 127, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle4 = new Sprite(409, 111, 426, 127, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle5 = new Sprite(432, 110, 449, 127, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle6 = new Sprite(454, 105, 486, 130, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle7 = new Sprite(492, 108, 515, 128, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle8 = new Sprite(522, 112, 539, 128, Rubi->LPDIRECT3DTEXTURE());
	LPSPRITE Idle9 = new Sprite(545, 112, 562, 128, Rubi->LPDIRECT3DTEXTURE());


	Animation* Rubi_idle = new Animation();
	Rubi_idle->AddFrame(Idle1, 200);
	Rubi_idle->AddFrame(Idle2, 200);
	Rubi_idle->AddFrame(Idle3, 200);
	Rubi_idle->AddFrame(Idle4, 200);
	Rubi_idle->AddFrame(Idle5, 200);
	Rubi_idle->AddFrame(Idle6, 200);
	Rubi_idle->AddFrame(Idle7, 200);
	Rubi_idle->AddFrame(Idle8, 200);
	Rubi_idle->AddFrame(Idle9, 200);
	Rubi_idle->SetRepeat(true);
	this->GetAnimations()->AddAnimation(Rubi_idle, 0);
	this->GetAnimations()->Start(0);
}
