#pragma once
#include <Windows.h>
#include <d3dx9.h>

#include "Camera.h"

class Sprite
{
private:
	LPDIRECT3DTEXTURE9 texture;
	RECT border;
	D3DXVECTOR2 size;
public:
	Sprite(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9 gettexture() { return texture; }
	RECT Border();
	D3DXVECTOR2 Size();
	void Draw(D3DXVECTOR2 position , LPD3DXSPRITE spritehandle);
	void Draw(D3DXVECTOR2 wPos, LPCAMERA camera, LPD3DXSPRITE spritehandle, float opacity = 1.0f);
	~Sprite();
};

typedef Sprite* LPSPRITE;

