#pragma once
#include"Aladin.h"
#include"Sound.h"
#include"AladinEnd.h"
class EndGame
{
private:
	AladinEnd* aladdin;
	LPCAMERA camera;
	Sound* sound;
	Sprite* complete;
	float time_sound = 4000;
	bool isRun = false;
public:
	EndGame();
	~EndGame();

	void Init(HWND hWnd);
	void LoadResources(LPD3DXSPRITE spriteHandler, LPDIRECT3DDEVICE9 d3ddv);
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);

};

