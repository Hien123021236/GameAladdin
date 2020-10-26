#pragma once
#include<unordered_map>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "Object.h"
#include "Texture.h"
//#include "Keyboard.h"
//#include "Map.h"
#include "Debug.h"
#include"Collision.h"
#include"SwordGuard.h"
#include"Mission.h"
#include"Mission2.h"
#include"EndGame.h"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

#define BLACK(alpha)         D3DCOLOR_ARGB(alpha, 0, 0, 0)
#define RED(alpha)           D3DCOLOR_ARGB(alpha, 255, 0, 0)
#define GREEN(alpha)         D3DCOLOR_ARGB(alpha, 0, 128, 0)
#define LAWNGREEN(alpha)     D3DCOLOR_ARGB(alpha, 124, 252, 0)
#define BLUE(alpha)          D3DCOLOR_ARGB(alpha, 0, 200, 255)
#define DEEPSKYBLUE(alpha)   D3DCOLOR_ARGB(alpha, 0, 191, 255)
#define SKYBLUE(alpha)       D3DCOLOR_ARGB(alpha, 0, 122, 204)
#define YELLOW(alpha)        D3DCOLOR_ARGB(alpha, 255, 255, 0)
class Game
{
private:
	static Game* _instance;
	HWND hWnd;										// Window handle
	LPDIRECT3D9 d3d = NULL;							// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;					// Direct3D device object
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;				// Sprite helper library to help us draw 2D image on the screen 

	//LPKEYBOARD keyboard = NULL;


	//LPMAP map;
	//GameMap *map;
	LPCAMERA camera;

	std::vector<LPOBJECT> objects;

	int MaxFPS = 240;
	Mission* mission;
	Mission2* mission2;
	EndGame* complete;
public:
	void Init(HWND hWnd);
	void Draw(float cX, float cY, LPDIRECT3DTEXTURE9 texture, RECT tile);
	void Run();
	void Update(DWORD dt);
	void Render();
	void End();
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	static Game* GetInstance();

	~Game();
};

