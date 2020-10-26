#pragma once
#include "Animation.h"
#include "Debug.h"
#include "Keyboard.h"
#include"Texture.h"
#include "Sound.h"

#include<vector>

using namespace std;


class Object
{
protected:
	D3DXVECTOR2* bottomPos;
	D3DXVECTOR2* centerPos;
	D3DXVECTOR2 wV;
	float height, width;
	float wG;
	LPANIMATIONS animations;
	int typeobj;
	bool isCollision = false;
	bool direction_l = false;
	bool direction_t = false;
	bool direction_r = false;
	bool direction_b = false;
	bool exist=true;
public:
	enum TYPEOBJECT {
		rong,
		wood,
		buttress,
		swordGuard,
		skeleton,
		pendulum,
		leash,
		bat,
		staffguard,
		apple,
		rubi,
		heart,
		peddler,
		restart,
		genie, 
		rock,
		jab,
		bone,
		floor,
		jafar,
		fire,
		star,
		newscreen
	};

	Sound* sound;

	Object();
	Object(float x, float y, float width, float height);
	virtual void Init(LPDIRECT3DDEVICE9 d3dd9) {};
	virtual D3DXVECTOR2* CenterPosition();
	virtual D3DXVECTOR2* BottomPosition();
	virtual D3DXVECTOR2 RenderPosition();
	virtual D3DXVECTOR2 Velocity();
	virtual float Height();
	virtual float Width();
	virtual float G();
	virtual LPANIMATIONS GetAnimations();
	virtual RECT CollisionBox();
	virtual void SetSize(D3DXVECTOR2 size);
	virtual void SetVelocity(D3DXVECTOR2 wV);
	virtual void SetBottomPosition(D3DXVECTOR2 pos);
	virtual void SetCenterPosition(D3DXVECTOR2 pos);
	virtual void SetG(float wG);
	virtual void ProcessKeyStates(LPKEYBOARD keyboard);
	virtual void Update(DWORD dt);
	virtual void Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler);
	virtual void SetTypeObj(int type) { this->typeobj = type; }
	virtual int GetTypeObj() { return this->typeobj; }

	virtual void SetisCo(bool check) {
		this->isCollision = check;
	};
	virtual bool GetIsCo()
	{
		return isCollision;
	}
	virtual bool GetDirection_l() { return direction_l; }
	virtual bool GetDirection_t() { return direction_t; }
	virtual bool GetDirection_r() { return direction_r; }
	virtual bool GetDirection_b() { return direction_b; }
	virtual void SetDirection(bool left, bool top, bool right, bool bottom) { direction_l = left; direction_t = top; direction_r = right; direction_b = bottom; }
	
	virtual void SetExist(bool ex) { this->exist = ex; }
	virtual bool GetExist() { return this->exist; }
	virtual int GetType() { return this->typeobj; }
	~Object();
};

typedef Object* LPOBJECT;
