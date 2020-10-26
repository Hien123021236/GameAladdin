#include "JaFar.h"

JaFar::JaFar(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::jafar);
	for (int i = 0; i < 5; i++)
	{
		fire[i] = new Fire(600, 700, 55, 35);//75,50
		fire[i]->SetBottomPosition(D3DXVECTOR2(700, 656));

	}
	for (int i = 0; i < 20; i++)
	{
		star[i] = new Star(600, 700,20,10);
		star[i]->id = i;
		star[i]->SetBottomPosition(D3DXVECTOR2(700, 550));
	}
}



void JaFar::Update(DWORD dt)
{
	if (this->exist) {
		if (animations != nullptr) {
			animations->Update(dt);
		}
		for (int i = 0; i < 5; i++)
		{
			fire[i]->Update(dt);
		}
		for (int i = 0; i < 20; i++)
		{
			star[i]->Update(dt);
		}
		
	}
	else
	{
		this->status = false;
	}
	delay -= dt;
	delay2 -= dt;
}

void JaFar::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	if (this->exist) {
		this->animations->Render(*BottomPosition(), camera, spriteHandler);
		for (int i = 0; i < 5; i++)
		{
			fire[i]->Render(camera, spriteHandler);
		}
		for (int i = 0; i < 20; i++)
		{
			star[i]->Render(camera, spriteHandler);
		}
	}
}
void JaFar::fires()
{
	this->animations->Start(ANIMATIONS::firesa);
}
void JaFar::IdleJafarL(D3DXVECTOR2* posAladin)
{
	this->animations->Start(ANIMATIONS::idlejafarleft);
	
	if (this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 7 &&delay2<=0)
	{
		
		for (int i = 0; i < 20; i++)
		{   
			if (star[i]->GetExist()==0)
			{
				//DebugOut(L"star %d\n", i);
				star[i]->SetIsLeft(true);
				star[i]->SetExist(true);
				star[i]->Start();
				star[i]->Dive(posAladin);
				break;
			}
		}
		delay2 = JAFAR_STAR_DELAT_TIME;
	}
}



void JaFar::IdleJafarR(D3DXVECTOR2* posAladin)
{
	this->animations->Start(ANIMATIONS::idlejafarright);
	if (this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 7 && delay2 <= 0)
	{

		for (int i = 0; i < 20; i++)
		{
			if (star[i]->GetExist() == 0)
			{
				//DebugOut(L"star %d\n", i);
				star[i]->SetIsLeft(false);
				star[i]->SetExist(true);
				star[i]->Start();
				star[i]->Dive(posAladin);
				break;
			}
		}
		delay2 = JAFAR_STAR_DELAT_TIME;
	}
}

vector<LPFIRE> JaFar::GetListFire()
{
	vector<LPFIRE> fires;
	for (int i = 0; i < 5; i++)
	{
		fires.push_back(fire[i]);
	}
	return fires;
}

vector<LPSTAR> JaFar::GetListStar()
{
	vector<LPSTAR> stars;
	for (int i = 0; i < 10; i++)
	{
		stars.push_back(star[i]);
	}
	return stars;
}

void JaFar::IdleSnakeL()
{

	this->animations->Start(ANIMATIONS::idlesnakeleft);
	if (this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 10 && delay <= 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (fire[i]->GetIsRun())//sai
			{
				fire[i]->FireLeft();
				fire[i]->SetExist(true);
				fire[i]->SetVelocity(D3DXVECTOR2(-0.3, 0));
				fire[i]->SetIsRun(false);
				break;
			}
			for (int i = 0; i < 5; i++)
			{
				if (fire[i]->BottomPosition()->x <= 0)
				{
					fire[i]->SetExist(false);
					fire[i]->SetIsRun(true);
					fire[i]->SetVelocity(D3DXVECTOR2(0, 0));
					fire[i]->SetBottomPosition(D3DXVECTOR2(700, 656));
				}
			}
		}
		delay = 1100;
	}
}

void JaFar::IdleSnakeR()
{

	this->animations->Start(ANIMATIONS::idlesnakeright);
	if (this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 10 && delay <= 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (fire[i]->GetIsRun())//sai
			{
				fire[i]->FireRight();
				fire[i]->SetExist(true);
				fire[i]->SetVelocity(D3DXVECTOR2(0.3, 0));
				fire[i]->SetIsRun(false);
				break;
			}
			for (int i = 0; i < 5; i++)
			{
				if (fire[i]->BottomPosition()->x >= 1100)
				{
					fire[i]->SetExist(false);
					fire[i]->SetIsRun(true);
					fire[i]->SetVelocity(D3DXVECTOR2(0, 0));

					fire[i]->SetBottomPosition(D3DXVECTOR2(800, 650));
				}
			}
		}
		delay = 1100;
	}
}



void JaFar::Init(LPDIRECT3DDEVICE9 d3dd9)
{

	LPTEXTURE JaFar = new Texture(L"JaFarRight.png", D3DCOLOR_XRGB(186, 254, 202), d3dd9);
	//lua
	
	// idle right nguoi
	LPSPRITE idle1 = new Sprite(8, 9, 72, 80, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle2 = new Sprite(80, 10, 137, 80, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle3 = new Sprite(144, 11, 199, 80, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle4 = new Sprite(208, 12, 259, 80, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle5 = new Sprite(272, 11, 336, 80, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle6 = new Sprite(344, 11, 426, 80, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle7 = new Sprite(440, 11, 525, 80, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle8 = new Sprite(536, 11, 604, 80, JaFar->LPDIRECT3DTEXTURE());

	//idle left nguoi
	LPTEXTURE JaFar1 = new Texture(L"JaFarLeft.png", D3DCOLOR_XRGB(186, 254, 202), d3dd9);
	//lua
	LPSPRITE fire1 = new Sprite(825, 193, 849, 240, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE fire2 = new Sprite(795, 187, 817, 240, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE fire3 = new Sprite(761, 193, 785, 240, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE fire4 = new Sprite(726, 190, 753, 240, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE fire5 = new Sprite(678, 194, 713, 240, JaFar1->LPDIRECT3DTEXTURE());

	LPSPRITE idle9 = new Sprite(791, 9, 855, 80, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle10 = new Sprite(726, 10, 783, 80, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle11 = new Sprite(664, 11, 719, 80, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle12 = new Sprite(604, 12, 655, 80, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle13 = new Sprite(527, 11, 591, 80, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle14 = new Sprite(437, 11, 519, 80, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle15 = new Sprite(338, 11, 423, 80, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle16 = new Sprite(259, 11, 327, 80, JaFar1->LPDIRECT3DTEXTURE());

	// idle right ran
	LPSPRITE idle_snack1 = new Sprite(8, 118, 78, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack2 = new Sprite(88, 112, 152, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack3 = new Sprite(160, 104, 227, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack4 = new Sprite(240, 104, 311, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack5 = new Sprite(320, 92, 389, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack6 = new Sprite(400, 93, 469, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack7 = new Sprite(480, 94, 550, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack8 = new Sprite(560, 94, 630, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack9 = new Sprite(644, 93, 708, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack10 = new Sprite(716, 95, 780, 176, JaFar->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack11 = new Sprite(788, 116, 859, 176, JaFar->LPDIRECT3DTEXTURE());

	// idle left ran
	LPSPRITE idle_snack12 = new Sprite(785, 118, 855, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack13 = new Sprite(711, 112, 775, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack14 = new Sprite(636, 104, 703, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack15 = new Sprite(552, 104, 623, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack16 = new Sprite(474, 92, 543, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack17 = new Sprite(394, 93, 463, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack18 = new Sprite(313, 94, 383, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack19 = new Sprite(233, 94, 303, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack20 = new Sprite(155, 93, 219, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack21 = new Sprite(83, 95, 147, 176, JaFar1->LPDIRECT3DTEXTURE());
	LPSPRITE idle_snack22 = new Sprite(4, 116, 75, 176, JaFar1->LPDIRECT3DTEXTURE());



	//
	Animation* ani_idlejafar_right = new Animation();
	ani_idlejafar_right->AddFrame(idle1, 200);
	ani_idlejafar_right->AddFrame(idle2, 200);
	ani_idlejafar_right->AddFrame(idle3, 200);
	ani_idlejafar_right->AddFrame(idle4, 200);
	ani_idlejafar_right->AddFrame(idle5, 200);
	ani_idlejafar_right->AddFrame(idle6, 200);
	ani_idlejafar_right->AddFrame(idle7, 200);
	ani_idlejafar_right->AddFrame(idle8, 200);
	ani_idlejafar_right->SetRepeat(7, 7);

	Animation* ani_idlejafar_left = new Animation();
	ani_idlejafar_left->AddFrame(idle9, 200);
	ani_idlejafar_left->AddFrame(idle10, 200);
	ani_idlejafar_left->AddFrame(idle11, 200);
	ani_idlejafar_left->AddFrame(idle12, 200);
	ani_idlejafar_left->AddFrame(idle13, 200);
	ani_idlejafar_left->AddFrame(idle14, 200);
	ani_idlejafar_left->AddFrame(idle15, 200);
	ani_idlejafar_left->AddFrame(idle16, 200);
	ani_idlejafar_left->SetRepeat(7, 7);

	Animation* ani_idlesnake_right = new Animation();
	ani_idlesnake_right->AddFrame(idle_snack1, 100);
	ani_idlesnake_right->AddFrame(idle_snack2, 100);
	ani_idlesnake_right->AddFrame(idle_snack3, 100);
	ani_idlesnake_right->AddFrame(idle_snack4, 100);
	ani_idlesnake_right->AddFrame(idle_snack5, 100);
	ani_idlesnake_right->AddFrame(idle_snack6, 100);
	ani_idlesnake_right->AddFrame(idle_snack7, 100);
	ani_idlesnake_right->AddFrame(idle_snack8, 100);
	ani_idlesnake_right->AddFrame(idle_snack9, 100);
	ani_idlesnake_right->AddFrame(idle_snack10, 100);
	ani_idlesnake_right->AddFrame(idle_snack11, 100);

	Animation* ani_idlesnake_left = new Animation();
	ani_idlesnake_left->AddFrame(idle_snack12, 100);
	ani_idlesnake_left->AddFrame(idle_snack13, 100);
	ani_idlesnake_left->AddFrame(idle_snack14, 100);
	ani_idlesnake_left->AddFrame(idle_snack15, 100);
	ani_idlesnake_left->AddFrame(idle_snack16, 100);
	ani_idlesnake_left->AddFrame(idle_snack17, 100);
	ani_idlesnake_left->AddFrame(idle_snack18, 100);
	ani_idlesnake_left->AddFrame(idle_snack19, 100);
	ani_idlesnake_left->AddFrame(idle_snack20, 100);
	ani_idlesnake_left->AddFrame(idle_snack21, 100);
	ani_idlesnake_left->AddFrame(idle_snack22, 100);

	Animation* ani_fire = new Animation();
	ani_fire->AddFrame(fire1, 200);
	ani_fire->AddFrame(fire2, 200);
	ani_fire->AddFrame(fire3, 200);
	ani_fire->AddFrame(fire4, 200);
	ani_fire->AddFrame(fire5, 200);

	this->GetAnimations()->AddAnimation(ani_idlejafar_left, ANIMATIONS::idlejafarleft);
	this->GetAnimations()->AddAnimation(ani_idlejafar_right, ANIMATIONS::idlejafarright);
	this->GetAnimations()->AddAnimation(ani_idlesnake_left, ANIMATIONS::idlesnakeleft);
	this->GetAnimations()->AddAnimation(ani_idlesnake_right, ANIMATIONS::idlesnakeright);
	this->GetAnimations()->AddAnimation(ani_fire, ANIMATIONS::firesa);
	for (int i = 0; i < 5; i++)
	{
		fire[i]->Init(d3dd9);
	}
	for (int i = 0; i < 20; i++)
	{
		star[i]->Init(d3dd9);
	}
}