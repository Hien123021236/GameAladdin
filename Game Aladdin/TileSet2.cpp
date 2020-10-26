#include "TileSet2.h"



TileSet2::TileSet2(LPDIRECT3DDEVICE9 d3dd9)
{
	LPCWSTR path = L"Map2.png";
	Texture *texture = new Texture(path, D3DCOLOR_XRGB(0, 0, 0), d3dd9);
	this->row = titeset_hight / tile_size;
	this->colum = tileset_wight / tile_size;
	int index = 1;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < colum; j++)
		{
			int left = j * tile_size;
			int top = i * tile_size;
			int right = left + tile_size;
			int bottom = top + tile_size;
			LPSPRITE tile = new Sprite(left, top, right, bottom, texture->LPDIRECT3DTEXTURE());
			tileset2[index] = tile;
			index++;
		}
	}
}



Tile2::Tile2()
{
	this->bg = nullptr;
	this->objects.clear();
}

void Tile2::AddObject(LPOBJECT Objnam)
{
	objects.push_back(Objnam);
}

void Tile2::SetBackground(LPSPRITE SP)
{
	bg = SP;
}

void Tile2::Render(LPCAMERA camera, LPD3DXSPRITE d3dx)
{
	if (objects.size() != 0)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			/*if(objects[i] != nullptr)
				objects[i]->Render(camera, d3dx);*/
		}
	}
}

LPSPRITE Tile2::GetBackground()
{
	return bg;
}


LPSPRITE TileSet2::get_tile(int id)
{
	if (tileset2.size() > 0 && id > 0)
		return tileset2.at(id);
	else
	{
		return nullptr;
	}
}
