#pragma once
#include"MapTwo.h"
#include"Aladin.h"
#include"BackGround2.h"
#include"Sound.h"
#include"Text.h"
#include"Blood.h"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
class Mission2
{
private:
	//new_ win ---------------------------------
	bool isRun = true;
	
	//---------------------------------------
	GameMapTwo* map2;
	Aladin* aladdin2;
	LPCAMERA camera;
	vector<LPOBJECT> ListObjectInMission;
	LPKEYBOARD keyboard = NULL;
	int delay = 120000;
	Sound* sound1;
	BackGround2* backG;

	Sprite *_spriteCountRubby;
	Text*_txtCountRubby;

	Sprite* _spriteLevelUp;
	Text* _txtLevelUp;
	//-------------
	Sprite* _spriteBloodBar;

	Blood* blood;

	Sprite* _spriteCountApple;
	Text* _txtCountApple;
public:
	//new---------------------------
	bool GetIsRun() { return isRun; }
	
	//--------------------------------
	void Init(HWND hWnd);
	//bool isRun = false;
	Mission2();
	~Mission2();
	void LoadResources(LPD3DXSPRITE spriteHandler,LPDIRECT3DDEVICE9 d3ddv);
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
	void Interact(DWORD dt);
	void Release();
	void InteractAladinWithFire(LPOBJECT fire);
	void InteractAladinWithStar(LPOBJECT stars,LPOBJECT jafar);
	void InteractAladinWithJafar(LPOBJECT jafar);
	bool CheckIsColiding(LPOBJECT obj1, LPOBJECT obj2);
};

