#include "RestartPoint.h"

RestartPoint::RestartPoint(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::restart);
}

void RestartPoint::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
	if (this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 8)
		attack = true;
	if (attack)
	{
		this->animations->Start(die);
	}
}

void RestartPoint::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE RestartPoint = new Texture(L"Item.png", D3DCOLOR_XRGB(248, 0, 248), d3dd9);
	LPSPRITE Idle = new Sprite(19, 424, 39, 457, RestartPoint->LPDIRECT3DTEXTURE());

	LPSPRITE Attacked1 = new Sprite(49, 428, 73, 457, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked2 = new Sprite(78, 437, 112, 457, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked3 = new Sprite(119, 425, 139, 459, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked4 = new Sprite(145, 425, 168, 459, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked5 = new Sprite(174, 426, 200, 459, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked6 = new Sprite(207, 426, 231, 460, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked7 = new Sprite(239, 427, 259, 461, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked8 = new Sprite(270, 428, 294, 461, RestartPoint->LPDIRECT3DTEXTURE());
	LPSPRITE Attacked9 = new Sprite(302, 429, 325, 462, RestartPoint->LPDIRECT3DTEXTURE());


	Animation* ani_idle = new Animation();
	ani_idle->AddFrame(Idle, 200);

	Animation* ani_attacked = new Animation();
	ani_attacked->AddFrame(Attacked2, 100);
	ani_attacked->AddFrame(Attacked3, 100);
	ani_attacked->AddFrame(Attacked4, 100);
	ani_attacked->AddFrame(Attacked5, 100);
	ani_attacked->AddFrame(Attacked6, 100);
	ani_attacked->AddFrame(Attacked7, 100);
	ani_attacked->AddFrame(Attacked8, 100);
	ani_attacked->AddFrame(Attacked9, 100);
	ani_attacked->AddFrame(Attacked5, 100);

	Animation* ani_die = new Animation();
	ani_die->AddFrame(Attacked5, 200);
	
	this->GetAnimations()->AddAnimation(ani_idle, ANIMATIONS::idle);
	this->GetAnimations()->AddAnimation(ani_attacked, ANIMATIONS::attacked);
	this->GetAnimations()->AddAnimation(ani_die, ANIMATIONS::die);
	if(!attack)
		this->animations->Start(idle);
	
}

void RestartPoint::Attacked()
{
	this->GetAnimations()->Start(ANIMATIONS::attacked);
	
}

void RestartPoint::Die()
{
	this->animations->Start(die);
}
