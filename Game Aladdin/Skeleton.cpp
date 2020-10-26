#include "Skeleton.h"

Skeleton::Skeleton(int x, int y, int wight, int hight)
{

	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));
	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::skeleton);
	for (int i = 0; i < 8; i++)
	{
		bones[i] = new Bones(this->CenterPosition()->x, this->CenterPosition()->y, 10, 10);
		/*this->bones[i]->SetExist(false);
		this.*/
	}
}

void Skeleton::Update(DWORD dt)
{
	
	if (this->exist == true) {
		if (animations != nullptr) {
			animations->Update(dt);
		}
		if ((this->animations->GetCurrentAnimationID() == 1 && this->animations->GetCurrentAnimation()->GetCurrentFrameID() == 10))
		{

			this->SetExist(false);

		}

	}
	if (this->animations->GetCurrentAnimationID() == 0 && this->animations->GetCurrentAnimation()->GetCurrentFrameID() == 18)
	{


		for (int i = 0; i < 8; i++)
		{
			bones[i]->Update(dt);
		}
		Explode();
	}
}

void Skeleton::Render( LPCAMERA camera, LPD3DXSPRITE sprite)
{
	if (this->exist == true)
	{
		this->animations->Render(*BottomPosition(), camera, sprite);
	}
	for (int i = 0; i < 8; i++)
	{
		bones[i]->Render(camera, sprite);
	}
}

void Skeleton::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE Skeleton = new Texture(L"Skeleton.png", D3DCOLOR_XRGB(255, 0, 255), d3dd9);
	LPSPRITE sprite523 = new Sprite(8, 73, 94, 99, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite524 = new Sprite(101, 68, 181, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite525 = new Sprite(188, 52, 263, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite526 = new Sprite(283, 37, 345, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite527 = new Sprite(365, 29, 415, 96, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite528 = new Sprite(427, 25, 475, 96, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite529 = new Sprite(486, 22, 534, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite530 = new Sprite(544, 16, 595, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite531 = new Sprite(601, 16, 652, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite532 = new Sprite(662, 16, 714, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite533 = new Sprite(726, 16, 794, 97, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite534 = new Sprite(799, 8, 864, 97, Skeleton->LPDIRECT3DTEXTURE());

	LPSPRITE sprite535 = new Sprite(13, 122, 63, 204, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite536 = new Sprite(75, 123, 124, 204, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite537 = new Sprite(132, 121, 193, 205, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite538 = new Sprite(203, 130, 267, 205, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite539 = new Sprite(279, 121, 353, 206, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite540 = new Sprite(376, 115, 457, 206, Skeleton->LPDIRECT3DTEXTURE());
	LPSPRITE sprite541 = new Sprite(479, 126, 574, 203, Skeleton->LPDIRECT3DTEXTURE());

	Animation* ani_idle_ske = new Animation();
	ani_idle_ske->AddFrame(sprite523, 200);
	ani_idle_ske->AddFrame(sprite524, 200);
	ani_idle_ske->AddFrame(sprite525, 200);
	ani_idle_ske->AddFrame(sprite526, 200);
	ani_idle_ske->AddFrame(sprite527, 200);
	ani_idle_ske->AddFrame(sprite528, 200);
	ani_idle_ske->AddFrame(sprite529, 200);
	ani_idle_ske->AddFrame(sprite530, 200);
	ani_idle_ske->AddFrame(sprite531, 200);
	ani_idle_ske->AddFrame(sprite532, 200);
	ani_idle_ske->AddFrame(sprite533, 200);
	ani_idle_ske->AddFrame(sprite534, 200);

	ani_idle_ske->AddFrame(sprite535, 200);
	ani_idle_ske->AddFrame(sprite536, 200);
	ani_idle_ske->AddFrame(sprite537, 200);
	ani_idle_ske->AddFrame(sprite538, 200);
	ani_idle_ske->AddFrame(sprite539, 200);
	ani_idle_ske->AddFrame(sprite540, 200);
	ani_idle_ske->AddFrame(sprite541, 200);
	
	LPTEXTURE Skeleton_die = new Texture(L"die.png", D3DCOLOR_XRGB(186, 254, 202), d3dd9);
	LPSPRITE die1 = new Sprite(8, 249, 28, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die2 = new Sprite(40, 236, 70, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die3 = new Sprite(80, 234, 111, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die4 = new Sprite(120, 232, 158, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die5 = new Sprite(168, 228, 208, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die6 = new Sprite(216, 226, 260, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die7 = new Sprite(272, 227, 314, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die8 = new Sprite(328, 228, 364, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die9 = new Sprite(376, 236, 408, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die10 = new Sprite(416, 242, 440, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die11 = new Sprite(448, 249, 468, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die12 = new Sprite(480, 252, 495, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	LPSPRITE die13 = new Sprite(504, 257, 512, 264, Skeleton_die->LPDIRECT3DTEXTURE());
	Animation* ani_die = new Animation();
	ani_die->AddFrame(die1, 100);
	ani_die->AddFrame(die2, 100);
	ani_die->AddFrame(die3, 100);
	ani_die->AddFrame(die4, 100);
	ani_die->AddFrame(die5, 100);
	ani_die->AddFrame(die6, 100);
	ani_die->AddFrame(die7, 100);
	ani_die->AddFrame(die8, 100);
	ani_die->AddFrame(die9, 100);
	ani_die->AddFrame(die10, 100);
	ani_die->AddFrame(die11, 100);
	ani_die->AddFrame(die12, 100);
	ani_die->AddFrame(die13, 100);
	for (int i = 0; i < 8; i++)
	{
		bones[i]->Init(d3dd9);
	}
	this->GetAnimations()->AddAnimation(ani_idle_ske, 0);
	this->GetAnimations()->AddAnimation(ani_die, 1);
	this->animations->Start(0);
}
void Skeleton::Explode()
{
	for (int i = 0; i < 8; i++) {
		bones[i]->SetExist(true);
	}
	bones[0]->SetVelocity(D3DXVECTOR2(0, -.5f));
	bones[1]->SetVelocity(D3DXVECTOR2(0.5, -0.5));
	bones[2]->SetVelocity(D3DXVECTOR2(.44f, 0));
	bones[3]->SetVelocity(D3DXVECTOR2(0.5, 0.5));
	bones[4]->SetVelocity(D3DXVECTOR2(0, 0.5f));
	bones[5]->SetVelocity(D3DXVECTOR2(-0.5, 0.5));
	bones[6]->SetVelocity(D3DXVECTOR2(-.5f, 0));
	bones[7]->SetVelocity(D3DXVECTOR2(-0.5, -0.5));

	this->exist = false;
}
vector<LPBONE> Skeleton::GetBones()
{
	vector<LPBONE> listbones;
	for (int i = 0; i < 8; i++)
	{
		listbones.push_back(bones[i]);
	}
	return listbones;
}
void Skeleton::Die()
{
	this->animations->Start(1);
}
