#include "Bones.h"
Bones::Bones()
{
}

Bones::Bones(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2, y + height));

	this->width = width;
	this->height = height;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::bone);
}


void Bones::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	LPTEXTURE Skeleton = new Texture(L"skeleton.png", D3DCOLOR_XRGB(255, 0, 255), d3ddv);
	//Ani Skeleton nổ tung
	LPSPRITE sprite542 = new Sprite(665, 129, 681, 134, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite543 = new Sprite(688, 122, 694, 137, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite544 = new Sprite(700, 122, 712, 135, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite545 = new Sprite(718, 126, 724, 134, Skeleton->LPDIRECT3DTEXTURE());

	Animation* ani_explode = new Animation();
	ani_explode->AddFrame(sprite542, 100);
	ani_explode->AddFrame(sprite543, 100);
	ani_explode->AddFrame(sprite544, 100);
	ani_explode->AddFrame(sprite545, 100);
	this->GetAnimations()->AddAnimation(ani_explode, 0);
	this->animations->Start(0);
}

void Bones::Update(DWORD dt)
{
	if (this->exist == true) {
		if (animations != nullptr) {
			this->animations->Update(dt);
		}
		float dx = this->BottomPosition()->x + wV.x * dt;
		float dy = this->BottomPosition()->y + wV.y * dt;

		this->SetBottomPosition(D3DXVECTOR2(dx, dy));
	}
}


void Bones::Fly(D3DXVECTOR2 V)
{
	wV = V;
}


Bones::~Bones()
{
}