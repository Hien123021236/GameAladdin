#pragma once
#include "Object.h"

class Fire : public Object
{
private:
	bool isrun = true;
public:
	Fire();
	Fire(float x, float y, float width, float height);
	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Fire::Update(DWORD dt);
	void FireLeft();
	void FireRight();
	void SetIsRun(bool a) { this->isrun = a; }
	bool GetIsRun() { return this->isrun; }
	~Fire();

};

typedef Fire* LPFIRE;


