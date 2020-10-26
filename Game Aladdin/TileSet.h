#pragma once
#include <d3dx9.h>
#include <vector>
#include "Sprite.h"
#include"Texture.h"
#include "Object.h"
#include<unordered_map>

using namespace std;

#define tile_size 64
#define tileset_wight 2240
#define titeset_hight 1152



class Tile {
private:
	LPSPRITE bg;
	vector<LPOBJECT>objects;
public:
	Tile();
	void AddObject(LPOBJECT Objnam);
	void SetBackground(LPSPRITE SP);
	void Render(LPCAMERA camera, LPD3DXSPRITE d3dx);
	vector <LPOBJECT>GetObj() { return objects; }
	LPSPRITE GetBackground();
};
typedef Tile* LPTILE;


class TileSet
{
private:
	unordered_map<int, LPSPRITE> tileset;
	int row, colum;
public:
	//LPSPRITE get_tile(int id);
	TileSet(LPDIRECT3DDEVICE9 d3dd9);
	LPSPRITE get_tile(int id);
};




