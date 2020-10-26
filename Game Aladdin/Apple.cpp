
#include "Apple.h"
#include "Texture.h"

Apple::Apple()
{
}

Apple::Apple(float x, float y, float width, float height,int type): Object(x, y, width, height)
{
	
	SetBottomPosition(D3DXVECTOR2(-100, 0));
}

void Apple::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	LPTEXTURE texture = new Texture(L"Item.png", D3DCOLOR_XRGB(248, 0, 248), d3ddv);
	LPSPRITE sprite = new Sprite(341, 17, 352, 29, texture->LPDIRECT3DTEXTURE());

	LPTEXTURE texture_die = new Texture(L"die.png", D3DCOLOR_XRGB(186, 254, 202), d3ddv);
	LPSPRITE die1 = new Sprite(8, 249, 28, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die2 = new Sprite(40, 236, 70, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die3 = new Sprite(80, 234, 111, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die4 = new Sprite(120, 232, 158, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die5 = new Sprite(168, 228, 208, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die6 = new Sprite(216, 226, 260, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die7 = new Sprite(272, 227, 314, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die8 = new Sprite(328, 228, 364, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die9 = new Sprite(376, 236, 408, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die10 = new Sprite(416, 242, 440, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die11 = new Sprite(448, 249, 468, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die12 = new Sprite(480, 252, 495, 264, texture_die->LPDIRECT3DTEXTURE());
	LPSPRITE die13 = new Sprite(504, 257, 512, 264, texture_die->LPDIRECT3DTEXTURE());

	Animation* ani_apple = new Animation();
	ani_apple->AddFrame(sprite, 100);
	ani_apple->SetRepeat(true);

	Animation* ani_destroy = new Animation();
	ani_destroy->AddFrame(die1, 30);
	ani_destroy->AddFrame(die2, 30);
	ani_destroy->AddFrame(die3, 30);
	ani_destroy->AddFrame(die4, 30);
	ani_destroy->AddFrame(die5, 30);
	ani_destroy->AddFrame(die6, 30);
	ani_destroy->AddFrame(die7, 30);
	ani_destroy->AddFrame(die8, 30);
	ani_destroy->AddFrame(die9, 3);
	ani_destroy->AddFrame(die10, 30);
	ani_destroy->AddFrame(die11, 30);
	ani_destroy->AddFrame(die12, 30);
	ani_destroy->AddFrame(die13, 30);
	ani_destroy->AddFrame(die13, 30);


	this->animations->AddAnimation(ani_apple, ANIMATIONS::idle);
	this->animations->AddAnimation(ani_destroy, ANIMATIONS::destroy);
	this->animations->Start(0);
}

void Apple::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	
	vector<LPCOEVENT> coEvents;
	vector<LPCOEVENT> coEventsResult;

	coEvents.clear();
	Colision* a = new  Colision(this);
	a->CalcPotentialCollisions(objs, coEvents, dt);

	if (coEvents.size() == 0)
	{
		float x = this->BottomPosition()->x + this->wV.x * dt;
		float y = this->BottomPosition()->y + this->wV.y * dt;
		SetBottomPosition(D3DXVECTOR2(x, y));
		this->wV.y += wG * dt;
		
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny = 0;
		a->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (int i = 0; i < coEventsResult.size(); i++) {

			float x = this->bottomPos->x + this->Velocity().x * dt * min_tx + nx * 0.0f;
			float y = this->bottomPos->y + this->Velocity().y * dt * min_ty + ny * 0.0f;


			SetBottomPosition(D3DXVECTOR2(x, y));

			int a = coEvents.at(i)->obj->CollisionBox().top;
			int b = coEventsResult.at(i)->obj->CollisionBox().top;
			if (nx != 0) this->SetVelocity(D3DXVECTOR2(0, this->wV.y));
			if (ny != 0) this->SetVelocity(D3DXVECTOR2(this->wV.x, 0));
			this->Destroy();
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	if (animations != nullptr) {
		animations->Update(dt);
	}

	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::destroy && this->animations->GetCurrentAnimation()->GetCurrentFrameID() == 13) {
		this->SetExist(false);
	}
}

void Apple::Destroy()
{
	this->wV.x = 0.0f;
	this->wV.y = 0.0f;
	this->animations->Start(ANIMATIONS::destroy);
}



Apple::~Apple()
{
}
