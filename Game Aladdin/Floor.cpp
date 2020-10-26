#include "Floor.h"

Floor::Floor(int x, int y, int wight, int hight)
{
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(true, true, true, true);
	this->SetTypeObj(TYPEOBJECT::floor);
}
