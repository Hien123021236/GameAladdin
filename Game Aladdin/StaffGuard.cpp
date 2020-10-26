#include "StaffGuard.h"

StaffGuard::StaffGuard(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::swordGuard);
	this->HP = 3;
	
}

void StaffGuard::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::die && this->animations->GetCurrentAnimation()->GetCurrentFrameID() == 10)
	{
		this->SetExist(false);
	}
}

void StaffGuard::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE StaffGuard = new Texture(L"SwordGuard.png", D3DCOLOR_XRGB(120, 193, 152), d3dd9);
	
	//left
	//sp StaffGuard Idle
	LPSPRITE Idle_left1 = new Sprite(8, 175, 52, 233, StaffGuard->LPDIRECT3DTEXTURE());
	////sp StaffGuard Walk
	LPSPRITE Walk_left1 = new Sprite(2, 9, 47, 76, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_left2 = new Sprite(53, 10, 98, 76, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_left3 = new Sprite(109, 11, 155, 76, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_left4 = new Sprite(164, 11, 209, 76, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_left5 = new Sprite(214, 10, 251, 76, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_left6 = new Sprite(259, 9, 302, 76, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_left7 = new Sprite(308, 9, 358, 76, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_left8 = new Sprite(363, 11, 399, 76, StaffGuard->LPDIRECT3DTEXTURE());
	//sp StaffGuard Attack
	LPSPRITE Attack_left1 = new Sprite(9, 82, 46, 156, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_left2 = new Sprite(53, 96, 102, 156, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_left3 = new Sprite(109, 98, 201, 156, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_left4 = new Sprite(203, 97, 289, 156, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_left5 = new Sprite(292, 96, 369, 156, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_left6 = new Sprite(382, 96, 423, 156, StaffGuard->LPDIRECT3DTEXTURE());
	//sp StaffGuard Hurt
	LPSPRITE Hurt_left1 = new Sprite(59, 185, 99, 233, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_left2 = new Sprite(114, 160, 153, 233, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_left3 = new Sprite(161, 165, 202, 233, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_left4 = new Sprite(210, 171, 256, 233, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_left5 = new Sprite(268, 162, 310, 233, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_left6 = new Sprite(318, 184, 365, 233, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_left7 = new Sprite(378, 185, 418, 233, StaffGuard->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_left8 = new Sprite(433, 166, 478, 233, StaffGuard->LPDIRECT3DTEXTURE());

	// right
	LPTEXTURE StaffGuardright = new Texture(L"SwordGuardright.png", D3DCOLOR_XRGB(122, 195, 154), d3dd9);
	//sp StaffGuard Idle

	LPSPRITE Idle_right1 = new Sprite(446,175,490,233, StaffGuardright->LPDIRECT3DTEXTURE());
	////sp StaffGuard Walk
	LPSPRITE Walk_right1 = new Sprite(451,9,496,76, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right2 = new Sprite(400,10,445,76, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right3 = new Sprite(343,11,389,76, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right4 = new Sprite(289,11,334,76, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right5 = new Sprite(247,10,284,76, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right6 = new Sprite(196,9,239,76, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right7 = new Sprite(140,9,190,76, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right8 = new Sprite(99,11,135,76, StaffGuardright->LPDIRECT3DTEXTURE());
	//sp StaffGuard Attack
	LPSPRITE Attack_right1 = new Sprite(452, 82, 489, 156, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right2 = new Sprite(396,96,445,156, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right3 = new Sprite(297,98,389,156, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right4 = new Sprite(209,97,295,156, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right5 = new Sprite(129,96,206,156, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right6 = new Sprite(75,95,116,156, StaffGuardright->LPDIRECT3DTEXTURE());
	//sp StaffGuard Hurt
	LPSPRITE Hurt_right1 = new Sprite(399,185,439,233, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right2 = new Sprite(345,160,384,233, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right3 = new Sprite(296,165,337,233, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right4 = new Sprite(242,171,288,233, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right5 = new Sprite(188,162,230,233, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right6 = new Sprite(133,184,180,233, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right7 = new Sprite(80,185,120,233, StaffGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right8 = new Sprite(20,166,65,233, StaffGuardright->LPDIRECT3DTEXTURE());
	//Ani StaffGuard  idle left
	Animation* ani_idle_left = new Animation();
	ani_idle_left->AddFrame(Idle_left1, 200);
	//Ani StaffGuard idle right
	Animation* ani_idle_right = new Animation();
	ani_idle_right->AddFrame(Idle_right1, 200);
	//Ani StaffGuard Walkleft left
	Animation* ani_walk_left = new Animation();
	ani_walk_left->AddFrame(Walk_left1, 200);
	ani_walk_left->AddFrame(Walk_left2, 200);
	ani_walk_left->AddFrame(Walk_left3, 200);
	ani_walk_left->AddFrame(Walk_left4, 200);
	ani_walk_left->AddFrame(Walk_left5, 200);
	ani_walk_left->AddFrame(Walk_left6, 200);
	ani_walk_left->AddFrame(Walk_left7, 200);
	ani_walk_left->AddFrame(Walk_left8, 200);
	//Ani StaffGuard Walkleft right
	Animation* ani_walk_right = new Animation();
	ani_walk_right->AddFrame(Walk_right1, 200);
	ani_walk_right->AddFrame(Walk_right2, 200);
	ani_walk_right->AddFrame(Walk_right3, 200);
	ani_walk_right->AddFrame(Walk_right4, 200);
	ani_walk_right->AddFrame(Walk_right5, 200);
	ani_walk_right->AddFrame(Walk_right6, 200);
	ani_walk_right->AddFrame(Walk_right7, 200);
	ani_walk_right->AddFrame(Walk_right8, 200);
	//Ani StaffGuard  Attack left
	Animation* ani_attack_left = new Animation();
	ani_attack_left->AddFrame(Attack_left1, 200);
	ani_attack_left->AddFrame(Attack_left2, 200);
	ani_attack_left->AddFrame(Attack_left3, 200);
	ani_attack_left->AddFrame(Attack_left4, 200);
	ani_attack_left->AddFrame(Attack_left5, 200);
	ani_attack_left->AddFrame(Attack_left6, 200);
	//Ani StaffGuard  Attack right
	Animation* ani_attack_right = new Animation();
	ani_attack_right->AddFrame(Attack_right1, 200);
	ani_attack_right->AddFrame(Attack_right2, 200);
	ani_attack_right->AddFrame(Attack_right3, 200);
	ani_attack_right->AddFrame(Attack_right4, 200);
	ani_attack_right->AddFrame(Attack_right5, 200);
	ani_attack_right->AddFrame(Attack_right6, 200);
	//Ani StaffGuard hurt left
	Animation* ani_hurt_lett = new Animation();
	ani_hurt_lett->AddFrame(Hurt_left1, 200);
	ani_hurt_lett->AddFrame(Hurt_left2, 200);
	ani_hurt_lett->AddFrame(Hurt_left3, 200);
	ani_hurt_lett->AddFrame(Hurt_left4, 200);
	ani_hurt_lett->AddFrame(Hurt_left5, 200);
	ani_hurt_lett->AddFrame(Hurt_left6, 200);
	ani_hurt_lett->AddFrame(Hurt_left7, 200);
	ani_hurt_lett->AddFrame(Hurt_left8, 200);
	//Ani StaffGuard hurt right
	Animation* ani_hurt_right = new Animation();
	ani_hurt_right->AddFrame(Hurt_right1, 200);
	ani_hurt_right->AddFrame(Hurt_right2, 200);
	ani_hurt_right->AddFrame(Hurt_right3, 200);
	ani_hurt_right->AddFrame(Hurt_right4, 200);
	ani_hurt_right->AddFrame(Hurt_right5, 200);
	ani_hurt_right->AddFrame(Hurt_right6, 200);
	ani_hurt_right->AddFrame(Hurt_right7, 200);
	ani_hurt_right->AddFrame(Hurt_right8, 200);
	// die
	LPTEXTURE StaffGuard_die = new Texture(L"die.png", D3DCOLOR_XRGB(186, 254, 202), d3dd9);
	LPSPRITE die1 = new Sprite(8, 249, 28, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die2 = new Sprite(40, 236, 70, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die3 = new Sprite(80, 234, 111, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die4 = new Sprite(120, 232, 158, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die5 = new Sprite(168, 228, 208, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die6 = new Sprite(216, 226, 260, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die7 = new Sprite(272, 227, 314, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die8 = new Sprite(328, 228, 364, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die9 = new Sprite(376, 236, 408, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die10 = new Sprite(416, 242, 440, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die11 = new Sprite(448, 249, 468, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die12 = new Sprite(480, 252, 495, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die13 = new Sprite(504, 257, 512, 264, StaffGuard_die->LPDIRECT3DTEXTURE());
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

	
	
	this->GetAnimations()->AddAnimation(ani_idle_left, ANIMATIONS::idleleft);
	this->GetAnimations()->AddAnimation(ani_idle_right, ANIMATIONS::idleright);
	this->GetAnimations()->AddAnimation(ani_walk_left, ANIMATIONS::walkleft);
	this->GetAnimations()->AddAnimation(ani_walk_right, ANIMATIONS::walkright);
	this->GetAnimations()->AddAnimation(ani_attack_left, ANIMATIONS::idleattackleft);
	this->GetAnimations()->AddAnimation(ani_attack_right, ANIMATIONS::idleattackright);
	this->GetAnimations()->AddAnimation(ani_hurt_lett, ANIMATIONS::hurtleft);
	this->GetAnimations()->AddAnimation(ani_hurt_right, ANIMATIONS::hurtright);
	this->GetAnimations()->AddAnimation(ani_die, ANIMATIONS::die);
	
}

void StaffGuard::Hunt(int damage)
{
	if (this->animations->GetCurrentAnimationID() != hurtleft)
	{
		this->SetHP(this->HP - damage);
		this->GetAnimations()->Start(hurtleft);
		
	}
}

void StaffGuard::Die()
{
	this->GetAnimations()->Start(die);
}
