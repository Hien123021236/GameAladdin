#include "Bat.h"
Bat::Bat(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::bat);

}

void Bat::Update(DWORD dt)
{

	if (this->exist == true) {

		delaytime -= dt;

		if (animations != nullptr) {
			animations->Update(dt);
		}
		if (status == STATUS::flydown && delaytime <= 0) {

			float dx = targetPos->x - CenterPosition()->x;
			float dy = targetPos->y - CenterPosition()->y;

			float vx = vx = BAT_FLY_SPEED * dx / sqrt(dx * dx + dy * dy);
			float vy = vy = BAT_FLY_SPEED * dy / sqrt(dx * dx + dy * dy);



			this->SetVelocity(D3DXVECTOR2(vx, vy));

			float distancex = abs(this->CenterPosition()->x - targetPos->x);
			float distancey = abs(this->CenterPosition()->y - targetPos->y);
			if (distancex < 5 && distancey < 5) {
				this->Rise();
			}
		}
		else if (status == STATUS::flyup) {

			float dx = returnPos.x - CenterPosition()->x;
			float dy = returnPos.y - CenterPosition()->y;

			float vx = vx = BAT_FLY_SPEED * dx / sqrt(dx * dx + dy * dy);
			float vy = vy = BAT_FLY_SPEED * dy / sqrt(dx * dx + dy * dy);

			this->SetVelocity(D3DXVECTOR2(vx, vy));

			float distancex = abs(this->CenterPosition()->x - returnPos.x);
			float distancey = abs(this->CenterPosition()->y - returnPos.y);
			if (distancex < 5 && distancey < 5) {
				this->SetCenterPosition(D3DXVECTOR2(returnPos.x, returnPos.y));
				this->Idle();
			}
		}

		float x = this->CenterPosition()->x + this->wV.x * dt;
		float y = this->CenterPosition()->y + this->wV.y * dt;
		SetCenterPosition(D3DXVECTOR2(x, y));
	}
}
void Bat::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	
	if (this->exist == true)
	{
		if (animations != nullptr) {
			animations->Render(*BottomPosition(), camera, spriteHandler);
		}
	}
}
void Bat::Idle()
{
	delaytime = BAT_DIVE_DELAY_TIME;
	wV.x = 0;
	wV.y = 0;
	this->animations->Start(ANIMATIONS::bIdle);
	this->status = STATUS::idle;
}

void Bat::Fly()
{
	this->animations->Start(ANIMATIONS::bFly);
	this->status = STATUS::fly;
}

void Bat::Dive(D3DXVECTOR2* centerAladdin)
{	
	if (this->status == STATUS::idle) {
		this->targetPos = centerAladdin;
		this->returnPos = *CenterPosition();
		this->animations->Start(ANIMATIONS::bFly);
		this->status = STATUS::flydown;
	}
}

void Bat::Rise()
{
	this->animations->Start(ANIMATIONS::bFly);
	this->status = STATUS::flyup;
}


void Bat::Fall()
{

	this->animations->Start(ANIMATIONS::bFall);
}

void Bat::Die()
{
	this->status = STATUS::idle;
}
void Bat::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	LPTEXTURE texture2 = new Texture(L"Bat.png", D3DCOLOR_XRGB(255, 0, 255), d3ddv);
	LPTEXTURE EnemyDie = new Texture(L"no.png", D3DCOLOR_XRGB(186, 254, 202), d3ddv);
	//Ani Bat Idle
	LPSPRITE sprite503 = new Sprite(9, 18, 16, 34, texture2->LPDIRECT3DTEXTURE());

	//Ani Bat Fly
	LPSPRITE sprite504 = new Sprite(20, 10, 41, 32, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite505 = new Sprite(48, 13, 67, 36, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite506 = new Sprite(76, 18, 97, 32, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite507 = new Sprite(10, 60, 34, 75, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite508 = new Sprite(39, 52, 52, 75, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite509 = new Sprite(56, 58, 86, 75, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite510 = new Sprite(89, 67, 121, 83, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite511 = new Sprite(128, 67, 136, 92, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite512 = new Sprite(143, 67, 163, 83, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite513 = new Sprite(165, 61, 199, 75, texture2->LPDIRECT3DTEXTURE());

	//Ani Bat fall
	LPSPRITE sprite514 = new Sprite(10, 119, 23, 132, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite515 = new Sprite(38, 111, 89, 139, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite516 = new Sprite(93, 111, 115, 136, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite517 = new Sprite(128, 101, 150, 154, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite518 = new Sprite(160, 106, 189, 155, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite519 = new Sprite(199, 106, 228, 159, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite520 = new Sprite(233, 109, 266, 154, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite521 = new Sprite(275, 106, 298, 157, texture2->LPDIRECT3DTEXTURE());
	LPSPRITE sprite522 = new Sprite(306, 106, 335, 157, texture2->LPDIRECT3DTEXTURE());

	//Ani Bat Die
	LPSPRITE sprite542 = new Sprite(8, 249, 28, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite543 = new Sprite(40, 236, 70, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite544 = new Sprite(80, 234, 111, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite545 = new Sprite(120, 232, 158, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite546 = new Sprite(168, 228, 208, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite547 = new Sprite(216, 226, 260, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite548 = new Sprite(272, 227, 314, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite549 = new Sprite(328, 228, 364, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite550 = new Sprite(376, 236, 408, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite551 = new Sprite(416, 242, 440, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite552 = new Sprite(448, 249, 468, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite553 = new Sprite(480, 252, 495, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite554 = new Sprite(504, 257, 512, 264, EnemyDie->LPDIRECT3DTEXTURE());
	LPSPRITE sprite555 = new Sprite(479, 126, 574, 203, EnemyDie->LPDIRECT3DTEXTURE());

	Animation* ani_idle_bat = new Animation();
	ani_idle_bat->AddFrame(sprite503, 100);
	//ani_idle_bat->SetRepeat(true);

	Animation* ani_fly_bat = new Animation();
	ani_fly_bat->AddFrame(sprite504, 100);
	ani_fly_bat->AddFrame(sprite505, 100);
	ani_fly_bat->AddFrame(sprite506, 100);
	ani_fly_bat->AddFrame(sprite507, 100);
	ani_fly_bat->AddFrame(sprite508, 100);
	ani_fly_bat->AddFrame(sprite509, 100);
	ani_fly_bat->AddFrame(sprite510, 100);
	ani_fly_bat->AddFrame(sprite511, 100);
	ani_fly_bat->AddFrame(sprite512, 100);
	ani_fly_bat->AddFrame(sprite513, 100);
	//ani_fly_bat->SetRepeat(3, 9);

	Animation* ani_dive_bat = new Animation();
	ani_dive_bat->AddFrame(sprite504, 100);
	ani_dive_bat->AddFrame(sprite505, 100);
	ani_dive_bat->AddFrame(sprite506, 100);

	Animation* ani_fall_bat = new Animation();
	ani_fall_bat->AddFrame(sprite514, 100);
	ani_fall_bat->AddFrame(sprite515, 100);
	ani_fall_bat->AddFrame(sprite516, 100);
	ani_fall_bat->AddFrame(sprite517, 100);
	ani_fall_bat->AddFrame(sprite518, 100);
	ani_fall_bat->AddFrame(sprite519, 100);
	ani_fall_bat->AddFrame(sprite520, 100);
	ani_fall_bat->AddFrame(sprite521, 100);
	ani_fall_bat->AddFrame(sprite522, 100);

	Animation* ani_die_bat = new Animation();
	ani_die_bat->AddFrame(sprite542, 100);
	ani_die_bat->AddFrame(sprite543, 100);
	ani_die_bat->AddFrame(sprite544, 100);
	ani_die_bat->AddFrame(sprite545, 100);
	ani_die_bat->AddFrame(sprite546, 100);
	ani_die_bat->AddFrame(sprite547, 100);
	ani_die_bat->AddFrame(sprite548, 100);
	ani_die_bat->AddFrame(sprite549, 100);
	ani_die_bat->AddFrame(sprite550, 100);
	ani_die_bat->AddFrame(sprite551, 100);
	ani_die_bat->AddFrame(sprite552, 100);
	ani_die_bat->AddFrame(sprite553, 100);
	ani_die_bat->AddFrame(sprite554, 100);
	ani_die_bat->AddFrame(sprite555, 100);

	this->GetAnimations()->AddAnimation(ani_idle_bat, Bat::ANIMATIONS::bIdle);
	this->GetAnimations()->AddAnimation(ani_fly_bat, Bat::ANIMATIONS::bFly);
	this->GetAnimations()->AddAnimation(ani_dive_bat, Bat::ANIMATIONS::bDive);
	this->GetAnimations()->AddAnimation(ani_fall_bat, Bat::ANIMATIONS::bFall);
	this->GetAnimations()->AddAnimation(ani_die_bat, Bat::ANIMATIONS::bDie);

	this->Idle();
	//this->wV.y = 0.05f;
	//this->wV.x = 0.05f;
}