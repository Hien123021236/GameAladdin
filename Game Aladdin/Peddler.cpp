#include "Peddler.h"

Peddler::Peddler(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::peddler);
}

void Peddler::Update(DWORD dt)
{
	if (animations != nullptr)
	{
		animations->Update(dt);
	}
}

void Peddler::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Peddler = new Texture(L"peddler.png", D3DCOLOR_XRGB(255, 0, 255), d3dd9);
	//Ani Peddler Idle
	LPSPRITE Peddler_idle1 = new Sprite(5, 8, 31, 60, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle2 = new Sprite(5, 100, 59, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle3 = new Sprite(75, 92, 135, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle4 = new Sprite(154, 73, 213, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle5 = new Sprite(227, 71, 310, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle6 = new Sprite(325, 71, 413, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle7 = new Sprite(416, 69, 508, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle8 = new Sprite(513, 69, 606, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle9 = new Sprite(613, 86, 690, 157, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle10 = new Sprite(701, 85, 799, 156, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle11 = new Sprite(809, 85, 910, 155, Peddler->LPDIRECT3DTEXTURE());

	LPSPRITE Peddler_idle12 = new Sprite(6, 191, 106, 264, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle13 = new Sprite(122, 190, 228, 267, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle14 = new Sprite(246, 188, 352, 266, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle15 = new Sprite(364, 188, 472, 267, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle16 = new Sprite(490, 193, 619, 271, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle17 = new Sprite(633, 198, 763, 275, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle18 = new Sprite(779, 202, 915, 277, Peddler->LPDIRECT3DTEXTURE());

	LPSPRITE Peddler_idle19 = new Sprite(10, 304, 159, 361, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle20 = new Sprite(180, 306, 314, 371, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle21 = new Sprite(339, 307, 472, 367, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle22 = new Sprite(490, 312, 598, 364, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle23 = new Sprite(617, 315, 733, 363, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle24 = new Sprite(751, 304, 873, 364, Peddler->LPDIRECT3DTEXTURE());

	LPSPRITE Peddler_idle25 = new Sprite(10, 410, 133, 471, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle26 = new Sprite(152, 416, 213, 470, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle27 = new Sprite(233, 412, 337, 470, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle28 = new Sprite(354, 388, 447, 470, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle29 = new Sprite(465, 398, 547, 469, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle30 = new Sprite(567, 400, 647, 468, Peddler->LPDIRECT3DTEXTURE());
	LPSPRITE Peddler_idle31 = new Sprite(660, 400, 740, 468, Peddler->LPDIRECT3DTEXTURE());


	Animation* ani_idle = new Animation();
	ani_idle->AddFrame(Peddler_idle1, 200);
	ani_idle->AddFrame(Peddler_idle2, 200);
	ani_idle->AddFrame(Peddler_idle3, 200);
	ani_idle->AddFrame(Peddler_idle4, 200);
	ani_idle->AddFrame(Peddler_idle5, 200);
	ani_idle->AddFrame(Peddler_idle6, 200);
	ani_idle->AddFrame(Peddler_idle7, 200);
	ani_idle->AddFrame(Peddler_idle8, 200);
	ani_idle->AddFrame(Peddler_idle9, 200);
	ani_idle->AddFrame(Peddler_idle10, 200);
	ani_idle->AddFrame(Peddler_idle11, 200);
	ani_idle->AddFrame(Peddler_idle12, 200);
	ani_idle->AddFrame(Peddler_idle13, 200);
	ani_idle->AddFrame(Peddler_idle14, 200);
	ani_idle->AddFrame(Peddler_idle15, 200);
	ani_idle->AddFrame(Peddler_idle16, 200);
	ani_idle->AddFrame(Peddler_idle17, 200);
	ani_idle->AddFrame(Peddler_idle18, 200);
	ani_idle->AddFrame(Peddler_idle19, 200);
	ani_idle->AddFrame(Peddler_idle20, 200);
	ani_idle->AddFrame(Peddler_idle21, 200);
	ani_idle->AddFrame(Peddler_idle22, 200);
	ani_idle->AddFrame(Peddler_idle23, 200);
	ani_idle->AddFrame(Peddler_idle24, 200);
	ani_idle->AddFrame(Peddler_idle25, 200);
	ani_idle->AddFrame(Peddler_idle26, 200);
	ani_idle->AddFrame(Peddler_idle27, 200);
	ani_idle->AddFrame(Peddler_idle28, 200);
	ani_idle->AddFrame(Peddler_idle29, 200);
	ani_idle->AddFrame(Peddler_idle30, 200);
	ani_idle->AddFrame(Peddler_idle31, 200);

	ani_idle->SetRepeat(31, 31);
	this->GetAnimations()->AddAnimation(ani_idle, 0);

	this->animations->Start(0);
}
