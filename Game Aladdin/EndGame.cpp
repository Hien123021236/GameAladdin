#include "EndGame.h"



EndGame::EndGame()
{
}


EndGame::~EndGame()
{
}

void EndGame::Init(HWND hWnd)
{
	sound = new Sound(hWnd);
	
}

void EndGame::LoadResources(LPD3DXSPRITE spriteHandler, LPDIRECT3DDEVICE9 d3ddv)
{
	camera = new Camera(D3DXVECTOR2(0, 0), 570, 300); 
	aladdin = new AladinEnd(570, 170, 20, 30);
	
	aladdin->Init(d3ddv);
	
	LPTEXTURE Complete = new Texture(L"Aladdin.png", D3DCOLOR_XRGB(255, 0, 255), d3ddv);
	complete = new Sprite(525, 2831, 757, 2972, Complete->LPDIRECT3DTEXTURE());
}

void EndGame::Update(DWORD dt)
{
	if (isRun == false) {
		sound->LoadSound("Sounds/LevelComplete.wav", "LevelComplete");
		sound->Play("LevelComplete", 0, 1);
		isRun = true;
	}
	
	time_sound -= dt;

	if (time_sound <= 0) {
		sound->LoadSound("Sounds/LevelComplete.wav", "LevelComplete");
		sound->Play("LevelComplete", 0, 1);
		time_sound = 4000;
	}
	camera->Update(dt);
	aladdin->Update(dt);
	aladdin->Win();
}

void EndGame::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	complete->Draw(D3DXVECTOR2(170, 100), spriteHandler);
	aladdin->Render(aladdin->GetPos(), spriteHandler);
}
