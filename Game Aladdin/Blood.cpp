#include "Blood.h"



Blood::Blood()
{
}


Blood::~Blood()
{
}

Blood::Blood(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2, y + height));

	this->width = width;
	this->height = height;
	this->SetDirection(false, false, false, false);

}

void Blood::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE BloodBar = new Texture(L"BloodBar.png", D3DCOLOR_XRGB(255, 0, 255), d3dd9);

	//Ani BloodBar 1
	LPSPRITE blood1 = new Sprite(73, 20, 144, 36, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood2 = new Sprite(158,22,229,38, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood3 = new Sprite(246,22,317,38, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood4 = new Sprite(334,25,406,40, BloodBar->LPDIRECT3DTEXTURE());

	//Ani BloodBar 2
	LPSPRITE blood5 = new Sprite(10,63,73,79, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood6 = new Sprite(88,63,151,79, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood7 = new Sprite(168,63,232,79, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood8 = new Sprite(249,64,313,79, BloodBar->LPDIRECT3DTEXTURE());

	//Ani BloodBar 3
	LPSPRITE blood9 = new Sprite(10,113,65,129, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood10 = new Sprite(85,113,140,129, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood11 = new Sprite(168,113,224,129, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood12 = new Sprite(246,113,302,128, BloodBar->LPDIRECT3DTEXTURE());

	//Ani BloodBar 4
	LPSPRITE blood13 = new Sprite(10,155,58,170, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood14 = new Sprite(85,155,133,170, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood15 = new Sprite(168,155,215,170, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood16 = new Sprite(246,154,293,170, BloodBar->LPDIRECT3DTEXTURE());

	//Ani BloodBar 5
	LPSPRITE blood17 = new Sprite(10,200,49,216, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood18 = new Sprite(85,200,125,215, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood19 = new Sprite(169,200,200,215, BloodBar->LPDIRECT3DTEXTURE());

	//Ani BloodBar 6
	LPSPRITE blood21 = new Sprite(13,244,37,259, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood22 = new Sprite(89,245,113,260, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood23 = new Sprite(176,245,192,258, BloodBar->LPDIRECT3DTEXTURE());
	LPSPRITE blood24 = new Sprite(254,246,269,258, BloodBar->LPDIRECT3DTEXTURE());

	Animation* ani_blood1 = new Animation();
	ani_blood1->AddFrame(blood1, 200);
	ani_blood1->AddFrame(blood2, 200);
	ani_blood1->AddFrame(blood3, 200);
	ani_blood1->AddFrame(blood4, 200);

	Animation* ani_blood2 = new Animation();
	ani_blood2->AddFrame(blood5, 200);
	ani_blood2->AddFrame(blood6, 200);
	ani_blood2->AddFrame(blood7, 200);
	ani_blood2->AddFrame(blood8, 200);

	Animation* ani_blood3 = new Animation();
	ani_blood3->AddFrame(blood9, 200);
	ani_blood3->AddFrame(blood10, 200);
	ani_blood3->AddFrame(blood11, 200);
	ani_blood3->AddFrame(blood12,200);

	Animation* ani_blood4 = new Animation();
	ani_blood4->AddFrame(blood13, 200);
	ani_blood4->AddFrame(blood14, 200);
	ani_blood4->AddFrame(blood15, 200);
	ani_blood4->AddFrame(blood16, 200);

	Animation* ani_blood5 = new Animation();
	ani_blood5->AddFrame(blood17, 200);
	ani_blood5->AddFrame(blood18, 200);
	ani_blood5->AddFrame(blood19, 200);

	Animation* ani_blood6 = new Animation();
	ani_blood6->AddFrame(blood21, 200);
	ani_blood6->AddFrame(blood22, 200);
	ani_blood6->AddFrame(blood23, 200);
	ani_blood6->AddFrame(blood24, 200);
	
	ani_blood1->SetRepeat(true);
	this->animations->AddAnimation(ani_blood1, 0);
	this->animations->AddAnimation(ani_blood2, 1);
	this->animations->AddAnimation(ani_blood3, 2);
	this->animations->AddAnimation(ani_blood4, 3);
	this->animations->AddAnimation(ani_blood5, 4);
	this->animations->AddAnimation(ani_blood6, 5);
	//this->animations->Start(0);
}

void Blood::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
}

void Blood::Render(D3DXVECTOR2 pos, LPD3DXSPRITE spriteHandler)
{
	this->animations->Render(pos, spriteHandler);
}

void Blood::BloodBar1()
{
	this->animations->Start(0);
}

void Blood::BloodBar2()
{
	this->animations->Start(1);
}

void Blood::BloodBar3()
{
	this->animations->Start(2);
}

void Blood::BloodBar4()
{
	this->animations->Start(3);
}

void Blood::BloodBar5()
{
	this->animations->Start(4);
}

void Blood::BloodBar6()
{
	this->animations->Start(5);
}
