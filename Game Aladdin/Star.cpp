#include "Star.h"

Star::Star(float x, float y, float width, float height)
{
	this->SetBottomPosition(D3DXVECTOR2(x + width / 2, y + height));

	this->width = width;
	this->height = height;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::star);
	this->exist = false;
}

void Star::Update(DWORD dt)
{
	if (this->exist == true) {
		if (animations != nullptr) {
			animations->Update(dt);
		}
		if (this->status == 0) {
			float dx = targetPos->x - CenterPosition()->x;
			float dy = targetPos->y - CenterPosition()->y;

			float vx = vx = Star_FLY_SPEED * dx / sqrt(dx * dx + dy * dy);
			float vy = vy = Star_FLY_SPEED * dy / sqrt(dx * dx + dy * dy);
			this->SetVelocity(D3DXVECTOR2(vx, vy));
		}
		float x = this->CenterPosition()->x + this->wV.x * dt;
		float y = this->CenterPosition()->y + this->wV.y * dt;
		SetCenterPosition(D3DXVECTOR2(x, y));
	}
	
	if (this->isLeft&&this->GetAnimations()->GetCurrentAnimationID() == 1 && this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
	{
		
		this->exist = false;
		this->SetVelocity(D3DXVECTOR2(0, 0));
		this->SetBottomPosition(D3DXVECTOR2(700, 550));
		
	}
	if (!this->isLeft && this->GetAnimations()->GetCurrentAnimationID() == 1 && this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
	{
		
		this->exist = false;
		this->SetVelocity(D3DXVECTOR2(0, 0));
		this->SetBottomPosition(D3DXVECTOR2(800, 550));

	}
}

void Star::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	
	if (this->exist == true)
	{
		
		if (animations != nullptr) {
			animations->Render(*BottomPosition(), camera, spriteHandler);
		}
	}

}



void Star::Start()
{
	this->animations->Start(0);
}

void Star::Explode()
{
	this->status = STATUS::explode;
	this->wV.x = 0;
	
	this->animations->Start(1);
	/*if(this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID()==4)
		this->SetExist(false);*/
}

void Star::Dive(D3DXVECTOR2* centerAladdin)
{
	status = STATUS::fly;
	this->targetPos = centerAladdin;
}

void Star::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	LPTEXTURE star = new Texture(L"JafarLeft.png", D3DCOLOR_XRGB(186, 254, 202), d3ddv);
	//sao
	LPSPRITE star1 = new Sprite(637, 226, 665, 240, star->LPDIRECT3DTEXTURE());
	LPSPRITE star2 = new Sprite(601, 224, 625, 240, star->LPDIRECT3DTEXTURE());
	LPSPRITE star3 = new Sprite(567, 225, 593, 240, star->LPDIRECT3DTEXTURE());
	//vu no
	LPSPRITE explode1 = new Sprite(539, 227, 553, 240, star->LPDIRECT3DTEXTURE());
	LPSPRITE explode2 = new Sprite(508, 226, 529, 240, star->LPDIRECT3DTEXTURE());
	LPSPRITE explode3 = new Sprite(494, 237, 497, 240, star->LPDIRECT3DTEXTURE());
	LPSPRITE explode4 = new Sprite(466, 219, 481, 240, star->LPDIRECT3DTEXTURE());

	Animation* ani_star = new Animation();
	ani_star->AddFrame(star1, 100);
	ani_star->AddFrame(star2, 100);
	ani_star->AddFrame(star3, 100);

	Animation* ani_explode = new Animation();
	ani_explode->AddFrame(explode1, 50);
	ani_explode->AddFrame(explode2, 50);
	ani_explode->AddFrame(explode3, 50);
	ani_explode->AddFrame(explode4, 50);
	ani_explode->AddFrame(explode4, 50);
	//ani_star->SetRepeat(true);
	this->GetAnimations()->AddAnimation(ani_star, 0);
	this->GetAnimations()->AddAnimation(ani_explode, 1);
}
