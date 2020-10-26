#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
class SwordGuard: public Object
{
private :
	int HP;
	int Status;
	RECT zoneAttack;
	RECT zoneActive;
public:
	
	enum ANIMATIONS {
		idleleft,
		idleright,
		walkleft,
		walkright,
		idleattackleft,
		idleattackright,
		hurtleft ,
		hurtright,
		die
	};
	SwordGuard(int x, int y, int wight, int hight,RECT rect);
	int GetHP() { return HP; }
	void SetHP(int HP) { this->HP = HP; }
	int GetStatus() { return this->Status; }
	void SetStatus(int status) { this->Status =status ; }
	void Update(DWORD dt);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Hunt(int damage);
	void HurtR(int damage);
	void Die();
	void IdleL();
	void IdleR();
	void AttackL();
	void AttackR();
	void WalkL();
	void WalkR();

	RECT getZoneAttack();
	void setZoneAttack(RECT zone);
	RECT getZoneActive();
	void setZoneActive(RECT zone);
};

