#include <d3dx9.h>
#include <vector>
#include "Sprite.h"
#include "Texture.h"
#include "Camera.h"
#include "Object.h"

#include "Debug.h"

#include<fstream>
#include<iostream>
#include"TileSet.h"
#include"Wood.h"
#include"Buttress.h"
#include"SwordGuard.h"
#include"Skeleton.h"
#include"Pendulum.h"
#include"Leash.h"
#include"Bat.h"
#include"StaffGuard.h"
#include"ItemApple.h"
#include"ItemRubi.h"
#include"Heart.h"
#include"Peddler.h"
#include"RestartPoint.h"
#include"Genie.h"
#include"Rock.h"
#include"Jab.h"
#include"Bones.h"
#include"NewScreen.h"
#define Tile_Size 64
#define Max_Map_x 35
#define Max_Map_y 18

using namespace std;
class GameMap
{
private:
	LPTILE **map;
	TileSet* tileset;
	D3DXVECTOR2 size;

public:
	GameMap();
	void LoadMap(char *path, LPDIRECT3DDEVICE9 d3dd9);
	D3DXVECTOR2 Size();
	RECT Border();
	void Update(DWORD dt);
	void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
	vector<LPOBJECT> GetObjectsInCamera(LPCAMERA camera);
};

