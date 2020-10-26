#pragma once
#include"Map.h"
#include"Sound.h"
#include"Text.h"
#include"Pillar.h"
#include"Pillar2.h"
#include"Blood.h"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define TIME_SOUND  291000
class Mission
{
private:
	//HWND hWnd;

	GameMap* map;
	Aladin* aladdin;
	LPCAMERA camera;
	vector<LPOBJECT> ListObjectInMission;
	Keyboard* keyboard =NULL;
	bool isRun = true;
	Sound* sound1;
	Pillar* pillar;
	Pillar2* pillar2;

	float time_sound = TIME_SOUND;

	Sprite *_spriteCountRubby;
	Text*_txtCountRubby;

	Sprite* _spriteLevelUp;
	Text* _txtLevelUp;

	Sprite* _spriteBloodBar;

	Blood* blood;

	Sprite* _spriteCountApple;
	Text* _txtCountApple;
public:
	
	
	Mission();
	~Mission();
	void Init(HWND hWnd);
	void LoadResources(LPD3DXSPRITE spriteHandler, LPDIRECT3DDEVICE9 d3ddv);
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
	bool CheckIsColiding(LPOBJECT obj1, LPOBJECT obj2);
	int CheckIsColidingWithLeash(LPOBJECT leash);
	void Interact(DWORD dt);
	void Release();
	bool GetIsRun() { return isRun; }
	void InteractAladinWithSword(LPOBJECT Sword);
	void InteractAladinWithSkeleton(LPOBJECT Skele);
	void InteractAladinWithStaff(LPOBJECT Staff);
	void InteractAladinWithItem(LPOBJECT Item,int type);
	void InteractAladinWithHeart(LPOBJECT He);
	void InteractAladinWithGenie(LPOBJECT Geni);
	void InteractAladinWithPendulum(LPOBJECT Pen);
	void InteractAladinWithRestart(LPOBJECT Restart);
	void InteractAladinWithJab(LPOBJECT jab);
	void InteractAladinWithBat(LPOBJECT bat);
	void InteractAladinWithBone(LPOBJECT bone);
	void InteractAladinWithLeash(LPOBJECT leash);
	void InteractAladinWithScreen(LPOBJECT NScreen);
	bool check_actack_ani(LPOBJECT a);
	bool isColliding(LPOBJECT a, LPOBJECT b);
};

