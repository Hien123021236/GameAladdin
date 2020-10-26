#include "MapTwo.h"



GameMapTwo::GameMapTwo()
{
	map2 = nullptr;
	tileset2 = nullptr;
}


GameMapTwo::~GameMapTwo()
{
}


void GameMapTwo::LoadMap2(char * path, LPDIRECT3DDEVICE9 d3dd9)
{
	this->tileset2 = new TileSet2(d3dd9);
	FILE* file = NULL;

	fopen_s(&file, "Map2.txt", "r");
	map2 = new LPTILE2 *[24];
	for (int i = 0; i < 24; i++)
	{
		map2[i] = new LPTILE2[12];
	}

	fscanf_s(file, "%f", &size.x);
	fscanf_s(file, "%f", &size.y);


	int r = 0;
	while (!feof(file))
	{
		for (int c = 0; c < 24; c++)
		{
			int tilesetID;
			fscanf_s(file, "%d", &tilesetID);
			//DebugOut(L"%d ", a[c][r]);

			map2[c][r] = new Tile2();
			map2[c][r]->SetBackground(tileset2->get_tile(tilesetID));
		}
		r++;
		DebugOut(L"\n");
	}
	// read object
	FILE* file_nam = NULL;


	fopen_s(&file_nam, "Object2.txt", "r");
	while (!feof(file_nam))
	{


		int pos_x, pos_y, wight, hight; int type_obj = NULL;
		fscanf_s(file_nam, "%d", &type_obj);
		fscanf_s(file_nam, "%d", &pos_x);
		fscanf_s(file_nam, "%d", &pos_y);
		fscanf_s(file_nam, "%d", &wight);
		fscanf_s(file_nam, "%d", &hight);
		LPOBJECT obj = nullptr;
		if (type_obj == 1) {
			obj = new Floor(pos_x, pos_y, wight, hight);
			//obj->Init(d3dd9);
		}
		else if (type_obj == 2)
		{
			obj = new JaFar(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		
		char c = fgetc(file_nam);
		for (; c != '\n' && c != EOF; c = fgetc(file_nam))
		{
			int c, r;
			fscanf_s(file_nam, "%d", &c);
			fscanf_s(file_nam, "%d", &r);
			map2[c][r]->AddObject(obj);
		}
	}
}

D3DXVECTOR2 GameMapTwo::Size()
{
	return size;
}

RECT GameMapTwo::Border()
{
	RECT b;
	b.left = 0;
	b.top = 0;
	b.right = size.x;
	b.bottom = size.y;
	return b;
}

void GameMapTwo::Update(DWORD dt)
{

}

void GameMapTwo::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	int left = camera->Border().left;
	int top = camera->Border().top;
	int right = camera->Border().right;
	int botton = camera->Border().bottom;

	for (int c = top / tile_size; c < ((botton % tile_size) == 0 ? (botton / tile_size) : ((botton / tile_size) + 1)); c++)
	{

		for (int r = left / tile_size; r < ((right % tile_size) == 0 ? (right / tile_size) : ((right / tile_size) + 1)); r++)
		{
			if (c >= 0 && r >= 0 && c < 12 && r < 24)
			{
				D3DXVECTOR2 pos(r * tile_size, c * tile_size);
				LPSPRITE TL = map2[r][c]->GetBackground();
				if (TL != nullptr)
					TL->Draw(pos, camera, spriteHandler);

				map2[r][c]->Render(camera, spriteHandler);
			}
		}
	}
}

vector<LPOBJECT> GameMapTwo::GetObjectsInCamera(LPCAMERA camera)
{
	int left = camera->Border().left;
	int top = camera->Border().top;
	int right = camera->Border().right;
	int botton = camera->Border().bottom;

	vector<LPOBJECT> Listobj;
	Listobj.clear();

	for (int c = top / tile_size; c < ((botton % tile_size) == 0 ? (botton / tile_size) : ((botton / tile_size) + 1)); c++)
	{

		for (int r = left / tile_size; r < ((right % tile_size) == 0 ? (right / tile_size) : ((right / tile_size) + 1)); r++)
		{
			if (c >= 0 && r >= 0 && c < Max_Map_y && r < Max_Map_x)
			{
				if (map2[r][c]->GetObj().size()) {
					for (int i = 0; i < map2[r][c]->GetObj().size(); i++)
					{
						Listobj.push_back(map2[r][c]->GetObj()[i]);
					}
				}
			}
		}
	}
	for (int i = 0; i < Listobj.size() - 1; i++) {
		for (int j = i + 1; j < Listobj.size(); j++) {
			if (Listobj.at(i) == Listobj.at(j))
			{
				Listobj.erase(Listobj.begin() + j);
				j--;
			}

		}
	}
	return Listobj;
}
