#include "Mission2.h"



void Mission2::Init(HWND hWnd)
{
	sound1 = new Sound(hWnd);
	sound1->LoadSound("Sounds/PrinceAli.wav", "PrinceAli");
	sound1->Play("PrinceAli", 0, 1);
	keyboard = new Keyboard();
	keyboard->Init(hWnd);
}

Mission2::Mission2()
{

}



Mission2::~Mission2()
{
}


void Mission2::LoadResources(LPD3DXSPRITE spriteHandler,LPDIRECT3DDEVICE9 d3ddv)
{
	camera = new Camera(D3DXVECTOR2(0, 329), 816, 311); //785, 560   // 685, 460
	map2 = new GameMapTwo();
	map2->LoadMap2("Map2.txt", d3ddv);


	aladdin2 = new Aladin(200, 300, 20, 30, 100);
	aladdin2->Init(d3ddv);
	aladdin2->sound = this->sound1;
	
	LPAPPLE apple1 = new Apple(500, 855, 10, 10, 1001);
	apple1->Init(d3ddv);

	aladdin2->AddApples(apple1);

	camera->AnchorTo(aladdin2->CenterPosition());
	camera->SetLimitedZone(map2->Border());
	backG = new BackGround2(65,55,1024,542);
	backG->init(d3ddv);

	LPTEXTURE Item = new Texture(L"Item.png", D3DCOLOR_XRGB(248, 0, 248), d3ddv);
	_spriteCountRubby = new Sprite(340, 111, 357, 127, Item->LPDIRECT3DTEXTURE());
	_txtCountRubby = new Text(spriteHandler, d3ddv, L"0", 10, 10, FW_BOLD);

	_spriteLevelUp = new Sprite(340, 140, 362, 164, Item->LPDIRECT3DTEXTURE());
	_txtLevelUp = new Text(spriteHandler, d3ddv, L"0", 10, 10, FW_BOLD);

	LPTEXTURE BloodBar = new Texture(L"BloodBar.png", D3DCOLOR_XRGB(255, 0, 255), d3ddv);
	_spriteBloodBar = new Sprite(8, 14, 56, 38, BloodBar->LPDIRECT3DTEXTURE());

	_spriteCountApple = new Sprite(341, 17, 352, 29, Item->LPDIRECT3DTEXTURE());
	_txtCountApple = new Text(spriteHandler, d3ddv, L"0", 10, 10, FW_BOLD);

	blood = new Blood(20, 10, 30, 30);
	blood->Init(d3ddv);
}

void Mission2::Update(DWORD dt)
{
	
	keyboard->RecordKeyStates(dt);
	camera->ProcessKeyStates(keyboard);
	camera->Update(dt);

	ListObjectInMission = map2->GetObjectsInCamera(camera);

	for (LPOBJECT obj : ListObjectInMission) {
		obj->Update(dt);
	}

	LPCOLLISION Co = new  Colision();
	Co->init(aladdin2, ListObjectInMission);

	aladdin2->ProcessKeyStates(keyboard);
	aladdin2->Update(dt, &ListObjectInMission);
	backG->update(dt);
	Interact(dt);
	delay -= dt;

	_txtCountRubby->SetString(aladdin2->GetRuby());
	_txtLevelUp->SetString(aladdin2->GetTurn());
	_txtCountApple->SetString(aladdin2->ApplesCount);

	blood->Update(dt);
	if (aladdin2->GetHP() == 12 || aladdin2->GetHP() == 11) {
		blood->BloodBar1();
	}
	if (aladdin2->GetHP() == 10 || aladdin2->GetHP() == 9) {
		blood->BloodBar2();
	}
	if (aladdin2->GetHP() == 8 || aladdin2->GetHP() == 7) {
		blood->BloodBar3();
	}
	if (aladdin2->GetHP() == 6 || aladdin2->GetHP() == 5) {
		blood->BloodBar4();
	}
	if (aladdin2->GetHP() == 4 || aladdin2->GetHP() == 3) {
		blood->BloodBar5();
	}
	if (aladdin2->GetHP() == 2 || aladdin2->GetHP() == 1) {
		blood->BloodBar6();
	}
}

void Mission2::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	backG->Render(this->camera, spriteHandler);
	map2->Render(this->camera, spriteHandler);

	for (LPOBJECT obj : ListObjectInMission) {
		obj->Render(this->camera, spriteHandler);
	}
	aladdin2->Render(this->camera, spriteHandler);

	_spriteCountRubby->Draw(D3DXVECTOR2(500, 270), spriteHandler);
	_txtCountRubby->Draw(D3DXVECTOR2(535, 330));

	_spriteLevelUp->Draw(D3DXVECTOR2(10, 260), spriteHandler);
	_txtLevelUp->Draw(D3DXVECTOR2(45, 330));

	_spriteCountApple->Draw(D3DXVECTOR2(445, 270), spriteHandler);
	_txtCountApple->Draw(D3DXVECTOR2(470, 330));

	_spriteBloodBar->Draw(D3DXVECTOR2(10, 10), spriteHandler);

	blood->Render(D3DXVECTOR2(52, 10), spriteHandler);
}

void Mission2::Interact(DWORD dt)
{
	for (int i = 0; i < ListObjectInMission.size(); i++)
	{
		if (ListObjectInMission.at(i)->GetTypeObj() == Object::TYPEOBJECT::jafar)
		{

			JaFar* jafar = (JaFar*)(ListObjectInMission.at(i));
			if (jafar->GetExist() == false)
			{
				this->isRun = false;
			}

			if (jafar->GetHP() >= 150)//jafar->GetHP() >= 5||delay>=0
			{
				
				//nguoi
				if (aladdin2->CollisionBox().right < jafar->CollisionBox().left)
				{
					jafar->IdleJafarL(aladdin2->CenterPosition());
				}
				else
				{
					jafar->IdleJafarR(aladdin2->CenterPosition());
				}
			}
			else
			{
				

				//ran
				if (aladdin2->CollisionBox().right < jafar->CollisionBox().left)
				{

					jafar->IdleSnakeL();
				}
				else
				{
					jafar->IdleSnakeR();
				}

			}
			for (int i = 0; i < jafar->GetListFire().size(); i++)
			{
				InteractAladinWithFire(jafar->GetListFire().at(i));
			}
			for (int i = 0; i < jafar->GetListStar().size(); i++)
			{
				InteractAladinWithStar(jafar->GetListStar().at(i), jafar);
			}
			
			InteractAladinWithJafar(jafar);
		
			
		}

	}
}

void Mission2::Release()
{
}

void Mission2::InteractAladinWithFire(LPOBJECT fire)
{
	if (CheckIsColiding(aladdin2, fire)&&fire->GetExist()==true)
	{
		if (aladdin2->GetHP() <= 0)
		{
			aladdin2->Die();
			/*sound1->LoadSound("Sounds/Aladdin_Die.wav", "Aladdin_Die");
			sound1->Play("Aladdin_Die", 0, 1);*/
		}
		else
		{
			aladdin2->Hurt(1);
			/*sound1->LoadSound("Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");
			sound1->Play("Aladdin_Hurt", 0, 1);*/
		}
	}
}

void Mission2::InteractAladinWithStar(LPOBJECT stars,LPOBJECT jafar)
{
	Star* a = (Star*)(stars);
	JaFar* jafa = (JaFar*)(jafar);
	if (CheckIsColiding(aladdin2, stars))
	{
		if (aladdin2->CollisionBox().right < jafa->CollisionBox().left) {
			float x = aladdin2->BottomPosition()->x + 2;
			float y = aladdin2->BottomPosition()->y;
			aladdin2->SetBottomPosition(D3DXVECTOR2(x, y));
			a->Explode();
		}
		else
		{
			float x = aladdin2->BottomPosition()->x - 2;
			float y = aladdin2->BottomPosition()->y;
			aladdin2->SetBottomPosition(D3DXVECTOR2(x, y));
			a->Explode();
		}
		
	}
}


void Mission2::InteractAladinWithJafar(LPOBJECT jafar)
{
	if (this->CheckIsColiding(aladdin2, jafar) && jafar->GetExist() == true)
	{
		if (aladdin2->GetAnimations()->GetCurrentAnimationID() == 4 || aladdin2->GetAnimations()->GetCurrentAnimationID() == 24 ||
			aladdin2->GetAnimations()->GetCurrentAnimationID() == 5 || aladdin2->GetAnimations()->GetCurrentAnimationID() == 25)
		{
			if (aladdin2->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
			{
				JaFar* a = (JaFar*)(jafar);
				int hp = a->GetHP();
				a->SetHP(hp - 1);
				if (a->GetHP() <= 0)
				{
					a->SetExist(false);	
					this->isRun = false;
				}
			}
		}
		
		else
		{
			if (aladdin2->GetHP() <= 0)
			{
				aladdin2->Die();
				
			}
			else
			{
				aladdin2->Hurt(1);
			
			}
		}
	}
}

bool Mission2::CheckIsColiding(LPOBJECT obj1, LPOBJECT obj2)
{
	float left = obj2->CollisionBox().left - obj1->CollisionBox().right;
	float top = obj2->CollisionBox().bottom - obj1->CollisionBox().top;
	float right = obj2->CollisionBox().right - obj1->CollisionBox().left;
	float bottom = obj2->CollisionBox().top - obj1->CollisionBox().bottom;


	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}
