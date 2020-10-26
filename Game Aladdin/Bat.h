#pragma once
#include"Object.h"
#include"Texture.h"
#include"Aladin.h"
#include"Animation.h"
#define BAT_FLY_SPEED 0.3f
#define BAT_DIVE_DELAY_TIME 1000
class Bat :public Object
{
private:
	int LP;
	int Status;
	D3DXVECTOR2* targetPos;
	D3DXVECTOR2 returnPos;
	int status = 0;
	float direction;
	float delaytime = BAT_DIVE_DELAY_TIME;
public:
	enum ANIMATIONS
	{
		bIdle,
		bFly,
		bDive,
		bFall,
		bDie
	};
	enum STATUS
	{
		idle,
		fly,
		flydown,
		flyup,
		fall,
		die
	};
	Bat(int x, int y, int wight, int hight);
	int GetLP() { return LP; }
	void SetLP(int HP) { this->LP = HP; }
	int GetStatus() { return this->Status; }
	void SetStatus(int status) { this->Status = status; }
	
	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);

	void Idle();
	void Fly();
	void Dive(D3DXVECTOR2* posAladdin);
	void Rise();
	void Fall();
	void Die();
};

