#pragma once
#include <d3dx9.h>
#include <vector>
#include "Sprite.h"
#include "Texture.h"
#include "Camera.h"
#include "Object.h"
#include "Debug.h"
#include"TileSet2.h"
#include<fstream>
#include<iostream>
#include"Floor.h"
#include"JaFar.h"
#define Tile_Size 64
#define Max_Map_x 24
#define Max_Map_y 12

using namespace std;
class GameMapTwo
{
private:
	LPTILE2 **map2;
	TileSet2* tileset2;
	D3DXVECTOR2 size;

public:
	GameMapTwo();
	~GameMapTwo();
	void LoadMap2(char *path, LPDIRECT3DDEVICE9 d3dd9);
	D3DXVECTOR2 Size();
	RECT Border();
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
	vector<LPOBJECT> GetObjectsInCamera(LPCAMERA camera);
};

