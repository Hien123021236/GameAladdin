#pragma once
#include <d3dx9.h>
#include <vector>
#include "Sprite.h"
#include"Texture.h"
#include "Object.h"
#include<unordered_map>

using namespace std;

#define tile_size 64
#define tileset_wight 1536
#define titeset_hight 768



class Tile2 {
private:
	LPSPRITE bg;
	vector<LPOBJECT>objects;
public:
	Tile2();
	void AddObject(LPOBJECT Objnam);
	void SetBackground(LPSPRITE SP);
	void Render(LPCAMERA camera, LPD3DXSPRITE d3dx);
	vector <LPOBJECT>GetObj() { return objects; }
	LPSPRITE GetBackground();
};
typedef Tile2* LPTILE2;


class TileSet2
{
private:
	unordered_map<int, LPSPRITE> tileset2;
	int row, colum;
public:
	//LPSPRITE get_tile(int id);
	TileSet2(LPDIRECT3DDEVICE9 d3dd9);
	LPSPRITE get_tile(int id);
};




