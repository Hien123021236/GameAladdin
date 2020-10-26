#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
class StaffGuard:public Object
{
private:
	int HP=3;
	
public:

	enum ANIMATIONS {
		
		idleleft,
		idleright,
		walkleft,
		walkright,
		idleattackleft,
		idleattackright,
		hurtleft,
		hurtright,
		die
	};
	StaffGuard(int x, int y, int wight, int hight);
	int GetHP() { return HP; }
	void SetHP(int HP) { this->HP = HP; }
	
	void Update(DWORD dt);
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Hunt(int damage);
	void Die();
};

