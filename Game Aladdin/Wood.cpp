#include "Wood.h"
Wood::Wood(int x, int y, int wight, int hight)
{  /*--------------------*/
	this->SetBottomPosition(D3DXVECTOR2(x + wight / 2, y + hight));

	this->width = wight;
	this->height = hight;
	this->SetDirection(false, true, false, false);
	this->SetTypeObj(TYPEOBJECT::wood);
}

