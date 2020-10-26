#include "Fire.h"



Fire::Fire()
{
}

Fire::Fire(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2, y + height));
	this->width = width;
	this->height = height;
	this->SetDirection(false, false, false, false);

	this->SetTypeObj(TYPEOBJECT::fire);
	this->exist = false;
}


void Fire::Update(DWORD dt)
{
	if (this->exist == true) {
		if (animations != nullptr) {
			animations->Update(dt);
		}
	}

	float dx = this->BottomPosition()->x + wV.x * dt;
	float dy = this->BottomPosition()->y;
	this->SetBottomPosition(D3DXVECTOR2(dx, dy));
}

void Fire::FireLeft()
{
	this->animations->Start(0);
}

void Fire::FireRight()
{
	this->animations->Start(1);
}


Fire::~Fire()
{
}

void Fire::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	LPTEXTURE FIRE = new Texture(L"JafarLeft.png", D3DCOLOR_XRGB(186, 254, 202), d3ddv);
	LPSPRITE fire1 = new Sprite(780, 286, 855, 336, FIRE->LPDIRECT3DTEXTURE());
	LPSPRITE fire2 = new Sprite(688, 288, 767, 336, FIRE->LPDIRECT3DTEXTURE());
	LPSPRITE fire3 = new Sprite(580, 294, 679, 336, FIRE->LPDIRECT3DTEXTURE());
	LPSPRITE fire4 = new Sprite(477, 295, 567, 336, FIRE->LPDIRECT3DTEXTURE());
	LPSPRITE fire5 = new Sprite(386, 305, 463, 336, FIRE->LPDIRECT3DTEXTURE());
	LPSPRITE fire6 = new Sprite(302, 305, 375, 336, FIRE->LPDIRECT3DTEXTURE());
	LPSPRITE fire7 = new Sprite(231, 293, 295, 336, FIRE->LPDIRECT3DTEXTURE());
	LPSPRITE fire8 = new Sprite(154, 285, 218, 336, FIRE->LPDIRECT3DTEXTURE());

	LPTEXTURE FIRE1 = new Texture(L"JafarRight.png", D3DCOLOR_XRGB(186, 254, 202), d3ddv);
	LPSPRITE fire9 = new Sprite(8, 286, 53, 336, FIRE1->LPDIRECT3DTEXTURE());
	LPSPRITE fire10 = new Sprite(96, 288, 175, 336, FIRE1->LPDIRECT3DTEXTURE());
	LPSPRITE fire11 = new Sprite(184, 294, 283, 336, FIRE1->LPDIRECT3DTEXTURE());
	LPSPRITE fire12 = new Sprite(296, 295, 386, 336, FIRE1->LPDIRECT3DTEXTURE());
	LPSPRITE fire13 = new Sprite(400, 305, 477, 336, FIRE1->LPDIRECT3DTEXTURE());
	LPSPRITE fire14 = new Sprite(488, 305, 561, 336, FIRE1->LPDIRECT3DTEXTURE());
	LPSPRITE fire15 = new Sprite(568, 293, 632, 336, FIRE1->LPDIRECT3DTEXTURE());
	LPSPRITE fire16 = new Sprite(645, 285, 709, 336, FIRE1->LPDIRECT3DTEXTURE());

	Animation* ani_fire_left = new Animation();
	ani_fire_left->AddFrame(fire1, 100);
	ani_fire_left->AddFrame(fire2, 100);
	ani_fire_left->AddFrame(fire3, 100);
	ani_fire_left->AddFrame(fire4, 100);
	ani_fire_left->AddFrame(fire5, 100);
	ani_fire_left->AddFrame(fire6, 100);
	ani_fire_left->AddFrame(fire7, 100);
	ani_fire_left->AddFrame(fire8, 100);
	ani_fire_left->SetRepeat(true);

	Animation* ani_fire_right = new Animation();
	ani_fire_right->AddFrame(fire9, 100);
	ani_fire_right->AddFrame(fire10, 100);
	ani_fire_right->AddFrame(fire11, 100);
	ani_fire_right->AddFrame(fire12, 100);
	ani_fire_right->AddFrame(fire13, 100);
	ani_fire_right->AddFrame(fire14, 100);
	ani_fire_right->AddFrame(fire15, 100);
	ani_fire_right->AddFrame(fire16, 100);
	ani_fire_right->SetRepeat(true);

	this->GetAnimations()->AddAnimation(ani_fire_left, 0);
	this->GetAnimations()->AddAnimation(ani_fire_right, 1);


}