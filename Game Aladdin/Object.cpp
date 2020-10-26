#include "Object.h"

Object::Object()
{
	this->width = 0;
	this->height = 0;
	this->bottomPos = new D3DXVECTOR2();
	this->centerPos = new D3DXVECTOR2();
	this->SetBottomPosition(D3DXVECTOR2(0, 0));
	wG = 0;
	this->exist = true;
	animations = new Animations();
}

Object::Object(float x, float y, float width, float height)
{
	this->width = width;
	this->height = height;
	this->bottomPos = new D3DXVECTOR2();
	this->centerPos = new D3DXVECTOR2();
	this->SetBottomPosition(D3DXVECTOR2(x ,y));
	wG = 0;
	
	animations = new Animations();
}

D3DXVECTOR2 * Object::CenterPosition()
{
	return this->centerPos;
}

D3DXVECTOR2 * Object::BottomPosition()
{
	return bottomPos;
}

D3DXVECTOR2 Object::RenderPosition()
{
	return D3DXVECTOR2(BottomPosition()->x-width/2, BottomPosition()->y-height);
}


D3DXVECTOR2 Object::Velocity()
{
	return this->wV;
}

float Object::Height()
{
	return this->height;
}

float Object::Width()
{
	return this->width;
}

float Object::G()
{
	return wG;
}

LPANIMATIONS Object::GetAnimations()
{
	return this->animations;
}

RECT Object::CollisionBox()
{
	RECT box;
	box.left = RenderPosition().x;
	box.top = RenderPosition().y;
	box.right = RenderPosition().x + width -1;
	box.bottom = RenderPosition().y + height - 1;
	return box;
}

void Object::SetSize(D3DXVECTOR2 size)
{
	if (size.x >= 0 && size.y >= 0) {
		width = size.x;
		height = size.y;
	}
}

void Object::SetVelocity(D3DXVECTOR2 wV)
{
	this->wV = wV;
}

void Object::SetBottomPosition(D3DXVECTOR2 pos)
{
	bottomPos->x = pos.x;
	bottomPos->y = pos.y;

	centerPos->x = pos.x;
	centerPos->y = pos.y - height / 2;
}

void Object::SetCenterPosition(D3DXVECTOR2 pos)
{
	centerPos->x = pos.x;
	centerPos->y = pos.y;

	bottomPos->x = pos.x;
	bottomPos->y = pos.y + height / 2;
}




void Object::SetG(float wG)
{
	this->wG = wG;
}

void Object::ProcessKeyStates(LPKEYBOARD keyboard)
{

}

void Object::Update(DWORD dt)
{

}

void Object::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	if(this->exist == true)
	{
		if (animations != nullptr) {
			animations->Render(*BottomPosition(), camera, spriteHandler);
		}
	}
}

Object::~Object()
{
}

