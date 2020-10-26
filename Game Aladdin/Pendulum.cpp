#include "Pendulum.h"

Pendulum::Pendulum(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));
	
	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::pendulum);
}

void Pendulum::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
}

void Pendulum::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Pendulum = new Texture(L"pendulum.png", D3DCOLOR_XRGB(163, 73, 164), d3dd9);
	
	LPSPRITE sprite1 = new Sprite(5,10,37,77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite2 = new Sprite(54,10,88 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite3 = new Sprite(104,10 ,137 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite4 = new Sprite(153, 10,186 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite5 = new Sprite(203, 10,236 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite6 = new Sprite(251, 10,284 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite7 = new Sprite(298, 10,331 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite8 = new Sprite(344, 10, 377, 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite9 = new Sprite(385, 10,418 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite10 = new Sprite(429, 10, 462, 77, Pendulum->LPDIRECT3DTEXTURE());

	LPSPRITE sprite11 = new Sprite(477, 10,510 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite12 = new Sprite(517, 10,550 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite13 = new Sprite(563, 10, 596, 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite14 = new Sprite(606, 10,639 , 77, Pendulum->LPDIRECT3DTEXTURE());
	LPSPRITE sprite15 = new Sprite(651, 10, 684, 77, Pendulum->LPDIRECT3DTEXTURE());
	Animation* ani_Pendulum = new Animation();
	ani_Pendulum->AddFrame(sprite1, 100);
	ani_Pendulum->AddFrame(sprite2, 100);
	ani_Pendulum->AddFrame(sprite3, 100);
	ani_Pendulum->AddFrame(sprite4, 100);
	ani_Pendulum->AddFrame(sprite5, 100);
	ani_Pendulum->AddFrame(sprite6, 100);
	ani_Pendulum->AddFrame(sprite7, 100);
	ani_Pendulum->AddFrame(sprite8, 100);
	ani_Pendulum->AddFrame(sprite9, 100);
	ani_Pendulum->AddFrame(sprite10, 100);
	ani_Pendulum->AddFrame(sprite11, 100);
	ani_Pendulum->AddFrame(sprite12, 100);
	ani_Pendulum->AddFrame(sprite13, 100);
	ani_Pendulum->AddFrame(sprite14, 100);
	ani_Pendulum->AddFrame(sprite15, 100);


	ani_Pendulum->AddFrame(sprite15, 100);
	ani_Pendulum->AddFrame(sprite14, 100);
	ani_Pendulum->AddFrame(sprite13, 100);
	ani_Pendulum->AddFrame(sprite12, 100);
	ani_Pendulum->AddFrame(sprite11, 100);
	ani_Pendulum->AddFrame(sprite10, 100);
	ani_Pendulum->AddFrame(sprite9, 100);
	ani_Pendulum->AddFrame(sprite8, 100);
	ani_Pendulum->AddFrame(sprite7, 100);
	ani_Pendulum->AddFrame(sprite6, 100);
	ani_Pendulum->AddFrame(sprite5, 100);
	ani_Pendulum->AddFrame(sprite4, 100);
	ani_Pendulum->AddFrame(sprite3, 100);
	ani_Pendulum->AddFrame(sprite2, 100);
	ani_Pendulum->AddFrame(sprite1, 100);
	ani_Pendulum->SetRepeat(true);
	this->GetAnimations()->AddAnimation(ani_Pendulum,0);

	this->animations->Start(0);
}
