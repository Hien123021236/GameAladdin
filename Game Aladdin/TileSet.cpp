#include "TileSet.h"



TileSet::TileSet(LPDIRECT3DDEVICE9 d3dd9)
{
	//new text ture 
	LPCWSTR path = L"map.png";
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
			tileset[index] = tile;
			index++;
		}
	}
}

LPSPRITE TileSet::get_tile(int id)
{
	if (tileset.size() > 0 && id > 0)
		return tileset.at(id);
	else
	{
		return nullptr;
	}
}

Tile::Tile()
{
	this->bg = nullptr;
	this->objects.clear();
}

void Tile::AddObject(LPOBJECT Objnam)
{
	objects.push_back(Objnam);
}

void Tile::SetBackground(LPSPRITE SP)
{
	bg = SP;
}
void Tile::Render(LPCAMERA camera, LPD3DXSPRITE d3dx)
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
LPSPRITE Tile::GetBackground()
{
	return bg;
}

