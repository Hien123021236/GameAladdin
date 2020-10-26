#include "Genie.h"

Genie::Genie(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::genie);
	
}

void Genie::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::die && this->animations->GetCurrentAnimation()->GetCurrentFrameID() == 11)
	{
		this->SetExist(false);
	}
}

void Genie::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Genie_idle = new Texture(L"Item.png", D3DCOLOR_XRGB(248,0,248), d3dd9);
	LPSPRITE Idle = new Sprite(335, 45, 373, 95, Genie_idle->LPDIRECT3DTEXTURE());
	LPTEXTURE Genie = new Texture(L"no.png", D3DCOLOR_XRGB(186, 254, 202), d3dd9);
	LPSPRITE Die1 = new Sprite(8, 175, 52, 233, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die2 = new Sprite(64, 67, 106, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die3 = new Sprite(120, 69, 163, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die4 = new Sprite(176, 71, 219, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die5 = new Sprite(232, 71, 274, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die6 = new Sprite(288, 64, 331, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die7 = new Sprite(344, 73, 385, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die8 = new Sprite(392, 84, 433, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die9 = new Sprite(440, 84, 479, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die10 = new Sprite(488, 88, 514, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die11 = new Sprite(528, 89, 548, 108, Genie->LPDIRECT3DTEXTURE());
	LPSPRITE Die12 = new Sprite(566, 84, 576, 107, Genie->LPDIRECT3DTEXTURE());

	Animation* ani_idle = new Animation();
	ani_idle->AddFrame(Idle, 200);
	Animation* ani_die = new Animation();
	ani_die->AddFrame(Die1, 200);
	ani_die->AddFrame(Die2, 200);
	ani_die->AddFrame(Die3, 200);
	ani_die->AddFrame(Die4, 200);
	ani_die->AddFrame(Die5, 200);
	ani_die->AddFrame(Die6, 200);
	ani_die->AddFrame(Die7, 200);
	ani_die->AddFrame(Die8, 200);
	ani_die->AddFrame(Die9, 200);
	ani_die->AddFrame(Die10, 200);
	ani_die->AddFrame(Die11, 200);
	ani_die->AddFrame(Die12, 200);
	ani_die->SetRepeat(true);
	ani_idle->SetRepeat(true);
	this->GetAnimations()->AddAnimation(ani_idle, ANIMATIONS::idle);
	this->GetAnimations()->AddAnimation(ani_die, ANIMATIONS::die);
	this->GetAnimations()->Start(idle);
}

void Genie::Die()
{
	this->GetAnimations()->Start(ANIMATIONS::die);
}
