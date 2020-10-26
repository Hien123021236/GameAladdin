#pragma once
#include"Aladin.h"
#include"Fire.h"
#include"Star.h"
#define JAFAR_STAR_DELAT_TIME 150
class JaFar :public Object
{
private:
	int HP = 300;
	LPFIRE fire[5];
	int delay = 1100;
	LPSTAR star[20];
	int delay2 = JAFAR_STAR_DELAT_TIME;
	
public:

	enum ANIMATIONS {
		idlejafarleft,
		idlejafarright,
		idlesnakeleft,
		idlesnakeright,
		die,
		firesa
	};
	bool status = true;
	JaFar(int x, int y, int wight, int hight);
	int GetHP() { return HP; }
	void SetHP(int HP) { this->HP = HP; }

	void IdleJafarL(D3DXVECTOR2* posAladin);
	void IdleJafarR(D3DXVECTOR2* posAladin);
	vector<LPFIRE> GetListFire();
	vector<LPSTAR> GetListStar();
	void IdleSnakeL();
	void IdleSnakeR();
	void fires();

	void Init(LPDIRECT3DDEVICE9 d3dd9);
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
};

