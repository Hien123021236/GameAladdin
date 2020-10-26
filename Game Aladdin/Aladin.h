#pragma once
#include "Apple.h"
#include"Collision.h"
#include"Animation.h"
#include"SwordGuard.h"
#include"JaFar.h"
//#include"Skeleton.h"
#include"StaffGuard.h"
#define ALADDIN_WALKING_SPEED 0.15f
#define ALADDIN_JUMPING_GRAVITY 0.002f
#define ALADDIN_OPACITY 0.6f
#define ALADDIN_APPLE_COUNT_ONE_TIME 5
#define ALADDIN_THROW_TIME 500

class Aladin : public Object
{
private:
	
	std::vector<LPOBJECT>LisEnemy;
	int HP = 12;
	LPDIRECT3DDEVICE9 d3ddv = NULL;
	D3DXVECTOR2 posrestart;
	LPAPPLE apples[ALADDIN_APPLE_COUNT_ONE_TIME];
	int solanchoi = 2;
	int timenotdie = 2000;
	bool statushurt = false;
	int countruby=0;
	float t = 0;
	float throwtime = ALADDIN_THROW_TIME;
	
public:
	std::vector<LPOBJECT> GetEnemy() { return LisEnemy; };
	int GetHP() { return HP; }
	void SetHP(int HP) { this->HP = HP; }
	int GetRuby() { return countruby; }
	void SetRuby(int count) { this->countruby = count; }
	int GetTurn() { return solanchoi; }

	D3DXVECTOR2 GetPosReStart() { return this->posrestart; }
	void SetPoReStart(D3DXVECTOR2 pos) { this->posrestart = pos; }
	enum ANIMATIONS {
		idleright,
		idleleft,
		idlethrowright,
		idlethrowleft,
		idleattackright,
		idleattackleft,

		jumpupright,
		jumpupleft,
		jumpright,
		jumpleft,
		jumpupthrowright,
		jumpupthrowleft,
		jumpupattackright,
		jumpupattackleft,
		jumpattackright,
		jumpattackleft,

		sitright,
		sitleft,
		sitthrowright,
		sitthrowleft,
		sitattackright,
		sitattackleft,

		walkright,
		walkleft,
		walkattackright,
		walkattackleft,
		walkthrowright,
		walkthrowleft,

		climbup,
		climbdown,
		climbjump,
		climbdropdown,

		fallright,
		fallleft,

		stopright,
		stopleft,
		
		hurtright,
		hurtleft,

		dieright,
		dieleft,

		revivalright,
		revivalleft,

		upright,
		upleft,

		idleclimb,
		win
	};
	int ApplesCount = 100;
	bool IsOnLeash = 0;
	bool IsTopLeash = 0;
	bool Direction = 0;
	bool IsAni(int aniid);
	float dx = 0;
	float dy = 0;

	Aladin(float x, float y, float width, float height,int type);

	void ProcessKeyStates(LPKEYBOARD keyboard);

	void Update(DWORD dt,vector<LPOBJECT>* objs);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);

	void AddApples(LPAPPLE apple);

	void Idle();
	void IdleRight();
	void IdleLeft();
	void IdleThrowRight();
	void IdleThrowLeft();
	void IdleAttackRight();
	void IdleAttackLeft();

	void JumpUpRight();
	void JumpUpLeft();
	void JumpRight();
	void JumpLeft();
	void JumpUpThrowRight();
	void JumpUpThrowLeft();
	void JumpUpAttackRight();
	void JumpUpAttackLeft();
	void JumpAttackRight();
	void JumpAttackLeft();

	void SitRight();
	void SitLeft();
	void SitThrowRight();
	void SitThrowLeft();
	void SitAttackRight();
	void SitAttackLeft();

	void WalkRight();
	void WalkLeft();
	void WalkAttackRight();
	void WalkAttackLeft();
	void WalkThrowRight();
	void WalkThrowLeft();

	void ClimbUp();
	void ClimbDown();
	void ClimbJump();
	void ClimbDropDown();


	/*void DropDownRight();
	void DropDownLeft();*/

	void FallRight();
	void FallLeft();

	void StopRight();
	void StopLeft();

	void HurtRight();
	void HurtLeft();

	void DieRight();
	void DieLeft();

	void RevivalRight();
	void RevivalLeft();

	void UpRight();
	void UpLeft();

	void IdleClimb();

	void MoveRight();
	void MoveLeft();
	
	bool IsGround();
	void SetIsGround(bool _isGround);

	void ThrowApple();
	void Hurt(int damage);
	void Die();
	void Interact(DWORD dt, vector<LPOBJECT>* objs);
	void InteractAladinWithSword(LPOBJECT Sword);
	void InteractAladinWithSkeleton(LPOBJECT Skele);
	void InteractAladinWithStaff(LPOBJECT Staff);
	void InteractAladinWithJafar(LPOBJECT Jafar);
	bool isColliding(LPOBJECT a, LPOBJECT b);
	bool CheckBoder(RECT  object, RECT  other);
};

