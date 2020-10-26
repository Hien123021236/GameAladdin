#include "SwordGuard.h"

SwordGuard::SwordGuard(int x, int y, int wight, int hight , RECT rect)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, false, false, false);
	this->SetTypeObj(TYPEOBJECT::swordGuard);
	this->HP = 3;
	zoneActive = rect;

	RECT rect1;
	rect1.left = x - 30;
	rect1.top = y;
	rect1.right = x + wight + 30;
	rect1.bottom = y + hight;
	
	this->setZoneAttack(rect1);
}

void SwordGuard::Update(DWORD dt)
{
	if (animations != nullptr) {
		animations->Update(dt);
	}
	RECT rect;
	rect.left = this->getZoneAttack().left + wV.x*dt;
	rect.top = this->getZoneAttack().top;
	rect.right = this->getZoneAttack().right + wV.x*dt;
	rect.bottom = this->getZoneAttack().bottom;
	this->setZoneAttack(rect);

	float x = this->BottomPosition()->x + wV.x*dt;
	float y = this->BottomPosition()->y; 
	this->SetBottomPosition(D3DXVECTOR2(x,y));

	if (this->animations->GetCurrentAnimationID() == ANIMATIONS::die && this->animations->GetCurrentAnimation()->GetCurrentFrameID() == 10)
	{
		this->SetExist(false);
	}

}

void SwordGuard::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	//left 
	LPTEXTURE SwordGuard = new Texture(L"SwordGuard.png", D3DCOLOR_XRGB(120, 193, 152), d3dd9);
	//Animation Enemy1 Idle
	LPSPRITE sprite440 = new Sprite(5, 317, 49, 370, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite441 = new Sprite(56, 316, 93, 370, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite442 = new Sprite(98, 317, 152, 370, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite443 = new Sprite(157, 317, 215, 370, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite444 = new Sprite(221, 317, 270, 370, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite445 = new Sprite(278, 317, 322, 370, SwordGuard->LPDIRECT3DTEXTURE());

	//Animation Enemy1 walk
	LPSPRITE sprite446 = new Sprite(2, 255, 49, 307, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite447 = new Sprite(55, 253, 107, 307, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite448 = new Sprite(111, 252, 167, 307, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite449 = new Sprite(173, 253, 224, 307, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite450 = new Sprite(230, 255, 279, 307, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite451 = new Sprite(284, 254, 326, 307, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite452 = new Sprite(334, 251, 378, 307, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite453 = new Sprite(382, 253, 429, 307, SwordGuard->LPDIRECT3DTEXTURE());

	//Animation Enemy1 attack
	LPSPRITE sprite454 = new Sprite(6, 378, 61, 430, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite455 = new Sprite(65, 386, 132, 430, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite456 = new Sprite(140, 388, 210, 430, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite457 = new Sprite(216, 387, 291, 430, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite458 = new Sprite(297, 385, 385, 430, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite459 = new Sprite(395, 384, 490, 430, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite460 = new Sprite(6, 447, 49, 507, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite461 = new Sprite(61, 434, 104, 507, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite462 = new Sprite(116, 441, 168, 507, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite463 = new Sprite(178, 451, 292, 507, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite464 = new Sprite(300, 434, 391, 507, SwordGuard->LPDIRECT3DTEXTURE());
	//Animation Enemy1 hurt
	LPSPRITE sprite465 = new Sprite(6, 538, 60, 586, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite466 = new Sprite(71, 515, 134, 586, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite467 = new Sprite(138, 529, 203, 586, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite468 = new Sprite(210, 520, 281, 586, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite469 = new Sprite(290, 522, 364, 586, SwordGuard->LPDIRECT3DTEXTURE());
	LPSPRITE sprite470 = new Sprite(382, 530, 448, 586, SwordGuard->LPDIRECT3DTEXTURE());

	Animation* ani_idle_left = new Animation();
	ani_idle_left->AddFrame(sprite440, 200);
	ani_idle_left->AddFrame(sprite441, 200);
	ani_idle_left->AddFrame(sprite442, 100);
	ani_idle_left->AddFrame(sprite443, 100);
	ani_idle_left->AddFrame(sprite444, 100);
	ani_idle_left->AddFrame(sprite445, 100);

	Animation* ani_hurt_letf = new Animation();
	ani_hurt_letf->AddFrame(sprite465, 100);
	ani_hurt_letf->AddFrame(sprite466, 100);
	ani_hurt_letf->AddFrame(sprite467, 100);
	ani_hurt_letf->AddFrame(sprite468, 100);
	ani_hurt_letf->AddFrame(sprite469, 100);
	ani_hurt_letf->AddFrame(sprite470, 100);

	Animation* ani_attack_letf = new Animation();
	ani_attack_letf->AddFrame(sprite454, 100);
	ani_attack_letf->AddFrame(sprite455, 100);
	ani_attack_letf->AddFrame(sprite456, 100);
	ani_attack_letf->AddFrame(sprite457, 100);
	ani_attack_letf->AddFrame(sprite458, 100);
	ani_attack_letf->AddFrame(sprite459, 100);
	ani_attack_letf->AddFrame(sprite460, 100);
	ani_attack_letf->AddFrame(sprite461, 100);
	ani_attack_letf->AddFrame(sprite462, 100);
	ani_attack_letf->AddFrame(sprite463, 100);
	ani_attack_letf->AddFrame(sprite464, 100);

	Animation* ani_walk_letf = new Animation();
	ani_walk_letf->AddFrame(sprite446, 100);
	ani_walk_letf->AddFrame(sprite447, 100);
	ani_walk_letf->AddFrame(sprite448, 100);
	ani_walk_letf->AddFrame(sprite449, 100);
	ani_walk_letf->AddFrame(sprite450, 100);
	ani_walk_letf->AddFrame(sprite451, 100);
	ani_walk_letf->AddFrame(sprite452, 100);
	ani_walk_letf->AddFrame(sprite453, 100);

	// right
	LPTEXTURE SwordGuardright = new Texture(L"SwordGuardright.png", D3DCOLOR_XRGB(122, 195, 154), d3dd9);
	//sp idle
	LPSPRITE Idle_right1 = new Sprite(449, 317, 493, 370, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Idle_right2 = new Sprite(405, 316, 442, 370, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Idle_right3 = new Sprite(346, 317, 400, 370, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Idle_right4 = new Sprite(283, 317, 341, 370, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Idle_right5 = new Sprite(228, 317, 277, 370, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Idle_right6 = new Sprite(176, 317, 220, 370, SwordGuardright->LPDIRECT3DTEXTURE());

	//sp Enemy1 walk right
	LPSPRITE Walk_right1 = new Sprite(449, 255, 496, 307, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right2 = new Sprite(391, 253, 443, 307, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right3 = new Sprite(331, 252, 387, 307, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right4 = new Sprite(274, 253, 325, 307, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right5 = new Sprite(219, 255, 268, 307, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right6 = new Sprite(172, 254, 214, 307, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right7 = new Sprite(120, 251, 164, 307, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Walk_right8 = new Sprite(69, 253, 116, 307, SwordGuardright->LPDIRECT3DTEXTURE());

	//Animation Enemy1 attack right
	LPSPRITE Attack_right1 = new Sprite(437, 378, 492, 430, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right2 = new Sprite(366, 386, 433, 430, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right3 = new Sprite(288, 388, 358, 430, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right4 = new Sprite(207, 387, 282, 430, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right5 = new Sprite(113, 385, 201, 430, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right6 = new Sprite(8, 384, 103, 430, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right7 = new Sprite(449, 447, 492, 507, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right8 = new Sprite(394, 434, 437, 507, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right9 = new Sprite(330, 441, 382, 507, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right10 = new Sprite(206, 451, 320, 507, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Attack_right11 = new Sprite(107, 434, 198, 507, SwordGuardright->LPDIRECT3DTEXTURE());
	//Animation Enemy1 hurt right
	LPSPRITE Hurt_right1 = new Sprite(438, 538, 492, 586, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right2 = new Sprite(364, 515, 427, 586, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right3 = new Sprite(295, 529, 360, 586, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right4 = new Sprite(217, 520, 288, 586, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right5 = new Sprite(134, 522, 208, 586, SwordGuardright->LPDIRECT3DTEXTURE());
	LPSPRITE Hurt_right6 = new Sprite(50, 530, 116, 586, SwordGuardright->LPDIRECT3DTEXTURE());

	Animation* ani_idle_right = new Animation();
	ani_idle_right->AddFrame(Idle_right1, 200);
	ani_idle_right->AddFrame(Idle_right2, 200);
	ani_idle_right->AddFrame(Idle_right3, 100);
	ani_idle_right->AddFrame(Idle_right4, 100);
	ani_idle_right->AddFrame(Idle_right5, 100);
	ani_idle_right->AddFrame(Idle_right6, 100);

	Animation* ani_hurt_right = new Animation();
	ani_hurt_right->AddFrame(Hurt_right1, 100);
	ani_hurt_right->AddFrame(Hurt_right2, 100);
	ani_hurt_right->AddFrame(Hurt_right3, 100);
	ani_hurt_right->AddFrame(Hurt_right4, 100);
	ani_hurt_right->AddFrame(Hurt_right5, 100);
	ani_hurt_right->AddFrame(Hurt_right6, 100);

	Animation* ani_attack_right = new Animation();
	ani_attack_right->AddFrame(Attack_right1, 100);
	ani_attack_right->AddFrame(Attack_right2, 100);
	ani_attack_right->AddFrame(Attack_right3, 100);
	ani_attack_right->AddFrame(Attack_right4, 100);
	ani_attack_right->AddFrame(Attack_right5, 100);
	ani_attack_right->AddFrame(Attack_right6, 100);
	ani_attack_right->AddFrame(Attack_right7, 100);
	ani_attack_right->AddFrame(Attack_right8, 100);
	ani_attack_right->AddFrame(Attack_right9, 100);
	ani_attack_right->AddFrame(Attack_right10, 100);
	ani_attack_right->AddFrame(Attack_right11, 100);

	Animation* ani_walk_right = new Animation();
	ani_walk_right->AddFrame(Walk_right1, 100);
	ani_walk_right->AddFrame(Walk_right2, 100);
	ani_walk_right->AddFrame(Walk_right3, 100);
	ani_walk_right->AddFrame(Walk_right4, 100);
	ani_walk_right->AddFrame(Walk_right5, 100);
	ani_walk_right->AddFrame(Walk_right6, 100);
	ani_walk_right->AddFrame(Walk_right7, 100);
	ani_walk_right->AddFrame(Walk_right8, 100);

	LPTEXTURE SwordGuard_die = new Texture(L"die.png", D3DCOLOR_XRGB(186, 254, 202), d3dd9);
	LPSPRITE die1 = new Sprite(8, 249, 28, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die2 = new Sprite(40, 236, 70, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die3 = new Sprite(80, 234, 111, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die4 = new Sprite(120, 232, 158, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die5 = new Sprite(168, 228, 208, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die6 = new Sprite(216, 226, 260, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die7 = new Sprite(272, 227, 314, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die8 = new Sprite(328, 228, 364, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die9 = new Sprite(376, 236, 408, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die10 = new Sprite(416, 242, 440, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die11 = new Sprite(448, 249, 468, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die12 = new Sprite(480, 252, 495, 264, SwordGuard_die->LPDIRECT3DTEXTURE());
	LPSPRITE die13 = new Sprite(504, 257, 512, 264, SwordGuard_die->LPDIRECT3DTEXTURE());

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


	ani_idle_left->SetRepeat(true);
	ani_idle_right->SetRepeat(true);
	/*ani_walk_letf->SetRepeat(true);
	ani_walk_right->SetRepeat(true);*/
	/*ani_attack_letf->SetRepeat(true); */
	ani_attack_right->SetRepeat(true);
	/*ani_hurt_letf->SetRepeat(true);
	ani_hurt_right->SetRepeat(true);*/
	//ani_die->SetRepeat(true);
	ani_attack_letf->SetRepeat(true);
	this->GetAnimations()->AddAnimation(ani_idle_left,ANIMATIONS::idleleft);
	this->GetAnimations()->AddAnimation(ani_idle_right, ANIMATIONS::idleright);
	this->GetAnimations()->AddAnimation(ani_walk_letf, ANIMATIONS::walkleft);
	this->GetAnimations()->AddAnimation(ani_walk_right, ANIMATIONS::walkright);
	this->GetAnimations()->AddAnimation(ani_attack_letf, ANIMATIONS::idleattackleft);
	this->GetAnimations()->AddAnimation(ani_attack_right, ANIMATIONS::idleattackright);
	this->GetAnimations()->AddAnimation(ani_hurt_letf, ANIMATIONS::hurtleft);
	this->GetAnimations()->AddAnimation(ani_hurt_right, ANIMATIONS::hurtright);
	this->GetAnimations()->AddAnimation(ani_die, ANIMATIONS::die);
	//this->GetAnimations()->Start(4);
	
}

void SwordGuard::Hunt(int damage)
{
	///
	// mat mau 
	//ani_hurt

	//di
	if (this->animations->GetCurrentAnimationID()!=hurtleft)
	{
		this->SetHP(this->HP - damage);
		this->animations->Start(ANIMATIONS::hurtleft);
	}
	
}

void SwordGuard::HurtR(int damage)
{
	if (this->animations->GetCurrentAnimationID() != hurtright)
	{
		this->SetHP(this->HP - damage);
		this->animations->Start(ANIMATIONS::hurtright);
	}
}

void SwordGuard::Die()
{
	this->wV.x = 0;
	this->animations->Start(ANIMATIONS::die);
}

void SwordGuard::IdleL()
{
	this->SetVelocity(D3DXVECTOR2(0, 0));
	this->animations->Start(ANIMATIONS::idleleft);
}

void SwordGuard::IdleR()
{
	this->SetVelocity(D3DXVECTOR2(0, 0));
	this->animations->Start(ANIMATIONS::idleright);
}

void SwordGuard::AttackL()
{
	this->SetVelocity(D3DXVECTOR2(0, 0));
	this->animations->Start(ANIMATIONS::idleattackleft);
}

void SwordGuard::AttackR()
{
	this->SetVelocity(D3DXVECTOR2(0, 0));
	this->animations->Start(ANIMATIONS::idleattackright);
}

void SwordGuard::WalkL()
{
	this->wV.x = -0.15f;
	this->animations->Start(ANIMATIONS::walkleft);
}

void SwordGuard::WalkR()
{
	this->wV.x = 0.15f;
	this->animations->Start(ANIMATIONS::walkright);
}

RECT SwordGuard::getZoneAttack()
{
	return zoneAttack;
}

void SwordGuard::setZoneAttack(RECT zone)
{
	this->zoneAttack = zone;
}

RECT SwordGuard::getZoneActive()
{
	return zoneActive;
}

void SwordGuard::setZoneActive(RECT zone)
{
	this->zoneActive = zone;
}
