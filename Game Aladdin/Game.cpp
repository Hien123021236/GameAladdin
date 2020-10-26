#include "Game.h"
#include "Apple.h"
#include "CDraw.h"



Game* Game::_instance = NULL;

void Game::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);


	// Initilize keyboard
	mission = new Mission();
	mission->Init(hWnd);
	mission->LoadResources(spriteHandler, d3ddv);
	mission2 = new Mission2();
	mission2->Init(hWnd);
	mission2->LoadResources(spriteHandler,d3ddv);
	complete = new EndGame();
	complete->Init(hWnd);
	complete->LoadResources(spriteHandler, d3ddv);
	OutputDebugString(L"[INFO] InitGame done;\n");
}

void Game::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT border)
{
	D3DXVECTOR3 p(x, y, 0);
	spriteHandler->Draw(texture, &border, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}

void Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / MaxFPS;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}
}




void Game::Update(DWORD dt)
{
	if (mission->GetIsRun()) {
		mission->Update(dt);
		return;
	}

	else if(mission2->GetIsRun()) {
		//mission->Release();
		mission2->Update(dt);
		return;
	}
	else
	{
		complete->Update(dt);
	}
	
}


void Game::Render()
{
	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(this->backBuffer, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		if (mission->GetIsRun()) {
			mission->Render(camera, spriteHandler);
		}
		else
		if (mission2->GetIsRun()) {
			mission2->Render(camera, spriteHandler);
		}
		else
		{
			complete->Render(camera, spriteHandler);
		}
		//complete->Render(camera, spriteHandler);
		spriteHandler->End();
		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
	
}

void Game::End()
{
}



Game* Game::GetInstance()
{
	if (_instance == NULL) _instance = new Game();
	return _instance;
}


Game::~Game()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}



