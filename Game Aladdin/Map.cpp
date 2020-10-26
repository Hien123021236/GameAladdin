#include "Map.h"



GameMap::GameMap()
{
	map = nullptr;
	tileset = nullptr;
	
}


void GameMap::LoadMap(char* name, LPDIRECT3DDEVICE9 d3dd9)
{
	this->tileset = new TileSet(d3dd9);
	FILE* file = NULL;

	fopen_s(&file, "aladdintxt.txt", "r");
	map = new LPTILE *[35];
	for (int i = 0; i < 35; i++)
	{
		map[i] = new LPTILE[18];
	}
	
	fscanf_s(file, "%f", &size.x);
	fscanf_s(file, "%f", &size.y);


	int r = 0;
	while (!feof(file))
	{
		for (int c = 0; c < 35; c++)
		{
			int tilesetID;
			fscanf_s(file, "%d", &tilesetID);
			//DebugOut(L"%d ", a[c][r]);

			map[c][r] = new Tile();
			map[c][r]->SetBackground(tileset->get_tile(tilesetID));
		}
		r++;
		DebugOut(L"\n");
	}
	// read object
	FILE* file_nam = NULL;


	fopen_s(&file_nam, "object.txt", "r");
	while (!feof(file_nam))
	{


		int pos_x, pos_y, wight, hight; int type_obj = NULL;
		int timedelay;
		RECT rect;
		int left, top, right, bottom;
		fscanf_s(file_nam, "%d", &type_obj);
		fscanf_s(file_nam, "%d", &timedelay);
		fscanf_s(file_nam, "%d", &pos_x);
		fscanf_s(file_nam, "%d", &pos_y);
		fscanf_s(file_nam, "%d", &wight);
		fscanf_s(file_nam, "%d", &hight);

		fscanf_s(file_nam, "%d", &left);
		fscanf_s(file_nam, "%d", &top);
		fscanf_s(file_nam, "%d", &right);
		fscanf_s(file_nam, "%d", &bottom);

		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;

		LPOBJECT obj = nullptr;
		if (type_obj == 1) {
			obj = new Wood(pos_x, pos_y, wight, hight);
			//obj->Init(d3dd9);
		}
		else if (type_obj == 2)
		{
			obj = new Buttress(pos_x, pos_y, wight, hight);
		}
		else if (type_obj == 3)
		{
			obj = new SwordGuard(pos_x, pos_y, wight, hight ,rect);
			obj->Init(d3dd9);
		}
		else if (type_obj == 4)
		{
			obj = new Skeleton(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 5)
		{
			obj = new Pendulum(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 7)
		{
			obj = new Bat(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if(type_obj==6)
		{
			obj = new Leash(pos_x, pos_y, wight, hight);
		}
		else if (type_obj == 8)
		{
			obj = new StaffGuard(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 9)
		{
			obj = new ItemApple(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 10)
		{
			obj = new ItemRubi(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 11)
		{
			obj = new Heart(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 12)
		{
			obj = new Peddler(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 13)
		{
			obj = new RestartPoint(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 14)
		{
			obj = new Genie(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 15)
		{
			obj = new Rock(pos_x, pos_y, wight, hight+10,timedelay);
			obj->Init(d3dd9);
		}
		else if (type_obj == 16)
		{
			obj = new Jab(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		else if (type_obj == 17)
		{
			obj = new NewScreen(pos_x, pos_y, wight, hight);
			obj->Init(d3dd9);
		}
		char c = fgetc(file_nam);
		for (; c != '\n' && c != EOF; c = fgetc(file_nam))
		{
			int c, r;
			fscanf_s(file_nam, "%d", &c);
			fscanf_s(file_nam, "%d", &r);
			map[c][r]->AddObject(obj);
		}
	}
}

D3DXVECTOR2 GameMap::Size()
{
	return size;
}

RECT GameMap::Border()
{
	RECT b;
	b.left = 0;
	b.top = 0;
	b.right = size.x;
	b.bottom = size.y;
	return b;
}

void GameMap::Update(DWORD dt)
{
}

void GameMap::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{

	int left = camera->Border().left;
	int top = camera->Border().top;
	int right = camera->Border().right;
	int botton = camera->Border().bottom;

	for (int c = top / tile_size; c < ((botton % tile_size) == 0 ? (botton / tile_size) : ((botton / tile_size) + 1)); c++)
	{

		for (int r = left / tile_size; r < ((right % tile_size) == 0 ? (right / tile_size) : ((right / tile_size) + 1)); r++)
		{
			if (c >= 0 && r >= 0 && c < 18 && r < 35)
			{
				D3DXVECTOR2 pos(r * tile_size, c * tile_size);
				LPSPRITE TL = map[r][c]->GetBackground();
				if (TL != nullptr)
					TL->Draw(pos, camera, spriteHandler);

				map[r][c]->Render(camera, spriteHandler);
			}
		}
	}

}

vector<LPOBJECT> GameMap::GetObjectsInCamera(LPCAMERA camera)
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
				if (map[r][c]->GetObj().size()) {
					for (int i = 0; i < map[r][c]->GetObj().size(); i++)
					{
						Listobj.push_back(map[r][c]->GetObj()[i]);
					}
				}
			}
		}
	}
	for (int i = 0; i < Listobj.size()-1; i++) {
		for (int j = i + 1; j < Listobj.size() ;j++) {
			if (Listobj.at(i) == Listobj.at(j))
			{
				Listobj.erase(Listobj.begin() + j);
				j--;
			}
			
		}
	}
	return Listobj;
}