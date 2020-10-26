#include "Rock.h"

Rock::Rock(int x, int y, int wight, int hight,int delay)
{

	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));//y + hight-10

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, true, false, false);
	this->SetTypeObj(TYPEOBJECT::rock);
	this->time = delay;
	this->delaytime = delay;
}

void Rock::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Rock = new Texture(L"pendulum.png", D3DCOLOR_XRGB(163, 73, 164), d3dd9);
	LPSPRITE sprite1 = new Sprite(7, 108, 47, 132, Rock->LPDIRECT3DTEXTURE());
	LPSPRITE sprite2 = new Sprite(66, 108, 106, 132, Rock->LPDIRECT3DTEXTURE());
	LPSPRITE sprite3 = new Sprite(124, 108, 164, 132, Rock->LPDIRECT3DTEXTURE());
	LPSPRITE sprite4 = new Sprite(182, 108, 222, 132, Rock->LPDIRECT3DTEXTURE());
	LPSPRITE sprite5 = new Sprite(239, 108, 279, 132, Rock->LPDIRECT3DTEXTURE());

	Animation* ani_rock = new Animation();
	ani_rock->AddFrame(sprite1, 2000);
	ani_rock->AddFrame(sprite2, 100);
	ani_rock->AddFrame(sprite3, 100);
	ani_rock->AddFrame(sprite4, 100);
	ani_rock->AddFrame(sprite5, 2000);

	ani_rock->SetRepeat(true);
	this->GetAnimations()->AddAnimation(ani_rock, 0);

	this->animations->Start(0);

}
void Rock::Update(DWORD dt)
{
	
	if (time <= 0) {
		if (animations != nullptr) {
			animations->Update(dt);
		}
		
	}
	else
	{
		time -= dt;
	}
}
