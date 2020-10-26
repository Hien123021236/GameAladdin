#include "Mission.h"


Mission::Mission()
{
	
}

Mission::~Mission()
{
}

void Mission::Init(HWND hWnd)
{
	sound1 = new Sound(hWnd);
	
	keyboard = new Keyboard();
	keyboard->Init(hWnd);	
}

void Mission::LoadResources(LPD3DXSPRITE spriteHandler, LPDIRECT3DDEVICE9 d3ddv)
{
	camera = new Camera(D3DXVECTOR2(0, 0), 570, 300); //785, 560   // 685, 460
	map = new GameMap();
	map->LoadMap("aladdintxt.txt", d3ddv);

	pillar = new Pillar(0, 0, 2240, 1152);
	pillar->Init(d3ddv);
	pillar2 = new Pillar2(0, 0, 2240, 1152);
	pillar2->Init(d3ddv);

	
	aladdin = new Aladin(50, 1000, 20, 30, 100);//50, 1000, 20, 30, 100//1550, 300, 20, 30, 100
	aladdin->Init(d3ddv);
	LPAPPLE apple1 = new Apple(400, 855, 10, 10, 1001);
	apple1->Init(d3ddv);
	aladdin->sound = this->sound1;

	camera->AnchorTo(aladdin->CenterPosition());
	camera->SetLimitedZone(map->Border());

	LPTEXTURE Item = new Texture(L"Item.png", D3DCOLOR_XRGB(248, 0, 248), d3ddv);
	_spriteCountRubby = new Sprite(340, 111, 357, 127, Item->LPDIRECT3DTEXTURE());
	_txtCountRubby = new Text(spriteHandler, d3ddv, L"0", 10, 10, FW_BOLD);

	_spriteLevelUp = new Sprite(340, 140, 362, 164, Item->LPDIRECT3DTEXTURE());
	_txtLevelUp = new Text(spriteHandler, d3ddv, L"0", 10, 10, FW_BOLD);

	LPTEXTURE BloodBar = new Texture(L"BloodBar.png", D3DCOLOR_XRGB(255, 0, 255), d3ddv);
	_spriteBloodBar = new Sprite(8, 14, 56, 38, BloodBar->LPDIRECT3DTEXTURE());

	_spriteCountApple = new Sprite(341, 17, 352, 29, Item->LPDIRECT3DTEXTURE());
	_txtCountApple = new Text(spriteHandler, d3ddv, L"0", 10, 10, FW_BOLD);
	
	blood = new Blood(20,10,30,30);
	blood->Init(d3ddv);

}

void Mission::Update(DWORD dt)
{
	
	if (keyboard->IsKeyDown(DIK_P)) {
		this->isRun = false;
	}

	this->time_sound -= dt;
	if (time_sound <= 0) {
		time_sound = TIME_SOUND;
	}
		
	
	keyboard->RecordKeyStates(dt);
	camera->ProcessKeyStates(keyboard);
	camera->Update(dt);
	
	ListObjectInMission = map->GetObjectsInCamera(camera);
	for (LPOBJECT obj : ListObjectInMission) {
		obj->Update(dt);
	}

	LPCOLLISION Co = new  Colision();
	Co->init(aladdin, ListObjectInMission);

	aladdin->ProcessKeyStates(keyboard);
	aladdin->Update(dt, &ListObjectInMission);
	pillar->Update(dt);
	pillar2->Update(dt);

	_txtCountRubby->SetString(aladdin->GetRuby());
	_txtLevelUp->SetString(aladdin->GetTurn());
	_txtCountApple->SetString(aladdin->ApplesCount);

	blood->Update(dt);
	DebugOut(L"mau aladin %d\n", aladdin->GetHP());
	if (aladdin->GetHP() == 12 || aladdin->GetHP()==11) {
		blood->BloodBar1();
	}
	if (aladdin->GetHP() == 10 || aladdin->GetHP() == 9) {
		blood->BloodBar2();
	}
	if (aladdin->GetHP() == 8 || aladdin->GetHP() == 7) {
		blood->BloodBar3();
	}
	if (aladdin->GetHP() == 6 || aladdin->GetHP() == 5) {
		blood->BloodBar4();
	}
	if (aladdin->GetHP() == 4 || aladdin->GetHP() == 3) {
		blood->BloodBar5();
	}
	if (aladdin->GetHP() == 2 || aladdin->GetHP() == 1) {
		blood->BloodBar6();
	}

	
	Interact(dt);

	
}

void Mission::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	
	map->Render(this->camera, spriteHandler);

	for (LPOBJECT obj : ListObjectInMission) {
		obj->Render(this->camera, spriteHandler);
	}

	aladdin->Render(this->camera, spriteHandler);
	

	pillar->Render(this->camera, spriteHandler);

	pillar2->Render(this->camera, spriteHandler);


	_spriteCountRubby->Draw(D3DXVECTOR2(500,270),spriteHandler);
	_txtCountRubby->Draw(D3DXVECTOR2(535,330));

	_spriteLevelUp->Draw(D3DXVECTOR2(10,260), spriteHandler);
	_txtLevelUp->Draw(D3DXVECTOR2(45,330));

	_spriteCountApple->Draw(D3DXVECTOR2(445, 270), spriteHandler);
	_txtCountApple->Draw(D3DXVECTOR2(470, 330));

	_spriteBloodBar->Draw(D3DXVECTOR2(10,10), spriteHandler);

	blood->Render(D3DXVECTOR2(52, 10), spriteHandler);
	if (time_sound == TIME_SOUND)
	{
		sound1->LoadSound("Sounds/PrinceAli.wav", "PrinceAli");
		sound1->Play("PrinceAli", 0, 1);
	}
}

bool Mission::CheckIsColiding(LPOBJECT obj1, LPOBJECT obj2)
{
	float left = obj2->CollisionBox().left - obj1->CollisionBox().right;
	float top = obj2->CollisionBox().bottom - obj1->CollisionBox().top;
	float right = obj2->CollisionBox().right - obj1->CollisionBox().left;
	float bottom = obj2->CollisionBox().top - obj1->CollisionBox().bottom;

	
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

int Mission::CheckIsColidingWithLeash(LPOBJECT leash) {
	float l = leash->CollisionBox().left - 5;
	float t = leash->CollisionBox().top + 65;
	float r = leash->CollisionBox().right + 10;
	float b = leash->CollisionBox().bottom;
	
	float x = aladdin->CenterPosition()->x;
	float y = aladdin->CenterPosition()->y;

	float af_x = x + aladdin->dx;
	float af_y = y + aladdin->dy;

	if (x >= l && x <= r && y >= t && y <= b) // aladdin.center dang va cham so day xich
	{
		return -1;
	}
	else 
	if (af_x >= l && af_x <= r && af_y >= t && af_y <= b)  //aladdin.center se va cham so day xich
	{
		return 1;
	}
	else          //aladdin.center khong va cham so day xich
		return 0;
}

void Mission::Interact(DWORD dt)
{	
	aladdin->IsOnLeash = false;
	aladdin->IsTopLeash = false;

	for (int i = 0; i < ListObjectInMission.size(); i++) {
		
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::swordGuard)
		{  
			//this->isRun = false;
			InteractAladinWithSword(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::staffguard)
		{
			InteractAladinWithStaff(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::skeleton)
		{
			InteractAladinWithSkeleton(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::apple || ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::rubi)
		{
			InteractAladinWithItem(ListObjectInMission.at(i), ListObjectInMission.at(i)->GetType());
			
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::genie)
		{
			InteractAladinWithGenie(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::pendulum)
		{
			InteractAladinWithPendulum(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::restart)
		{
			InteractAladinWithRestart(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::jab)
		{
			InteractAladinWithJab(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::heart)
		{
			InteractAladinWithHeart(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::bat)
		{
			InteractAladinWithBat(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::bone)
		{
			InteractAladinWithBone(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::leash) {
			InteractAladinWithLeash(ListObjectInMission.at(i));
		}
		if (ListObjectInMission.at(i)->GetType() == Object::TYPEOBJECT::newscreen) {
			InteractAladinWithScreen(ListObjectInMission.at(i));
		}
	}
}

void Mission::Release()
{

}

void Mission::InteractAladinWithSword(LPOBJECT Sword)
{
	SwordGuard* a = (SwordGuard*)(Sword);
	if (aladdin->CollisionBox().right < Sword->CollisionBox().left)
	{
		if (aladdin->CollisionBox().right < a->getZoneAttack().left&& a->CollisionBox().left > a->getZoneActive().left&&a->GetAnimations()->GetCurrentAnimationID()!= SwordGuard::ANIMATIONS::hurtleft&& a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::die)
		{
			if(a->getZoneActive().left!=0)
			a->WalkL();
			
		}
		else if (aladdin->CollisionBox().right < a->getZoneAttack().left && a->CollisionBox().left <= a->getZoneActive().left && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::hurtleft && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::die)
		{
			a->IdleL();
		}
		else if (aladdin->CollisionBox().right > a->getZoneAttack().left && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::hurtleft && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::die) {
			
				a->AttackL();
			
		}
		
	}
	else
	{

		if (aladdin->CollisionBox().left > a->getZoneAttack().right && a->CollisionBox().right < a->getZoneActive().right && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::hurtright && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::die)
		{
			if (a->getZoneActive().left != 0)
				a->WalkR();

		}
		else if (aladdin->CollisionBox().left > a->getZoneAttack().right && a->CollisionBox().right >= a->getZoneActive().right && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::hurtright && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::die)
		{
			a->IdleR();
		}
		else if (aladdin->CollisionBox().left < a->getZoneAttack().right && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::hurtright && a->GetAnimations()->GetCurrentAnimationID() != SwordGuard::ANIMATIONS::die) {
			
				a->AttackR();
			
		}
	}
	if (this->isColliding(this->aladdin, Sword)&&Sword->GetExist()==true)
	{
		if (check_actack_ani(aladdin))
		{
			if (aladdin->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
			{
				if (Sword->GetTypeObj() == Object::TYPEOBJECT::swordGuard)
				{
					//SwordGuard* a = (SwordGuard*)(Sword);
					if (a->GetHP() <= 0)
					{
						a->Die();
					}
					else
					{
						a->Hunt(1);
					}
				}
			}
		}
		else
		{
			if ((Sword->GetAnimations()->GetCurrentAnimationID() == SwordGuard::ANIMATIONS::idleattackleft && Sword->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 6) || Sword->GetAnimations()->GetCurrentAnimationID() == SwordGuard::ANIMATIONS::idleattackright && Sword->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 6)
			{
				if (aladdin->GetHP() <= 0)
				{
					aladdin->Die();
				}
				else
				{
					
					aladdin->Hurt(1);
				
				}
			}

		}
	}
}

void Mission::InteractAladinWithSkeleton(LPOBJECT Skele)
{
	Skeleton* a = (Skeleton*)(Skele);
	if (this->isColliding(this->aladdin, Skele))
	{
		if (check_actack_ani(aladdin))
		{
			if (aladdin->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
			{
				if (Skele->GetTypeObj() == Object::TYPEOBJECT::skeleton)
				{
					
					a->Die();
				}
			}
		}
	}
	for (int i = 0; i < a->GetBones().size();i++)
	{
		if (this->isColliding(this->aladdin, a->GetBones().at(i))&& a->GetBones().at(i)->GetExist()==true)
		{
			
			a->GetBones().at(i)->SetExist(false);
			aladdin->Hurt(1);
			/*sound1->LoadSound("Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");
			sound1->Play("Aladdin_Hurt", 0, 1);*/
		}
	}
}

void Mission::InteractAladinWithStaff(LPOBJECT Staff)
{

	if (this->isColliding(this->aladdin, Staff))
	{
		if (check_actack_ani(aladdin))
		{
			if (aladdin->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
			{
				if (Staff->GetTypeObj() == Object::TYPEOBJECT::staffguard)
				{
					StaffGuard* a = (StaffGuard*)(Staff);
					if (a->GetHP() <= 0)
					{
						a->Die();
					}
					else
					{
						a->Hunt(1);
					}
				}
			}
		}
		else
		{
			if ((Staff->GetAnimations()->GetCurrentAnimationID() == StaffGuard::ANIMATIONS::idleattackleft && Staff->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4))
			{
				if (aladdin->GetHP() <= 0)
				{
					/*sound1->LoadSound("Sounds/Aladdin_Die.wav", "Aladdin_Die");
					sound1->Play("Aladdin_Die", 0, 1);*/
					aladdin->Die();
				}
				else
				{
					aladdin->Hurt(1);
					/*sound1->LoadSound("Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");
					sound1->Play("Aladdin_Hurt", 0, 1);*/
	
				}
			}

		}
	}
}

void Mission::InteractAladinWithItem(LPOBJECT Item,int type)
{
	if (this->CheckIsColiding(this->aladdin, Item))
	{
		
		if (type == Object::TYPEOBJECT::rubi) {
			if (Item->GetExist() == true) {
				int a = this->aladdin->GetRuby() + 1;
				this->aladdin->SetRuby(a);
			}
			Item->SetExist(false);
		}
		else
		{
			if (Item->GetExist() == true) {
				aladdin->ApplesCount++;
			}
			Item->SetExist(false);
		}
		DebugOut(L"so luong ru bi: %d\n", aladdin->GetRuby());
	}
}

void Mission::InteractAladinWithHeart(LPOBJECT He)
{
	if (this->CheckIsColiding(this->aladdin, He)&& He->GetExist()==true)
	{
		this->aladdin->SetHP(12);
		He->SetExist(false);
		DebugOut(L"mau sau reset: %d \n", this->aladdin->GetHP());
	}
}

void Mission::InteractAladinWithGenie(LPOBJECT Geni)
{
	if (this->isColliding(this->aladdin, Geni))
	{
		Genie* a = (Genie*)(Geni);
		a->Die();
	}
}

void Mission::InteractAladinWithPendulum(LPOBJECT Pen)
{
	if (this->isColliding(this->aladdin, Pen))
	{
		if (Pen->GetAnimations()->GetCurrentAnimationID() == 0 && Pen->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 11)
		{
			if (aladdin->GetHP() <= 0)
			{
				/*sound1->LoadSound("Sounds/Aladdin_Die.wav", "Aladdin_Die");
				sound1->Play("Aladdin_Die", 0, 1);*/
				aladdin->Die();
			}
			else
			{
				aladdin->Hurt(1);
				/*sound1->LoadSound("Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");
				sound1->Play("Aladdin_Hurt", 0, 1);*/
			}
		}
	}
}

void Mission::InteractAladinWithRestart(LPOBJECT Restart)
{
	if (this->isColliding(this->aladdin, Restart))
	{
		if (check_actack_ani(aladdin))
		{
			if (aladdin->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
			{
				
				RestartPoint* a = (RestartPoint*)(Restart);
				if(!a->attack)
					a->Attacked();
				float x = aladdin->BottomPosition()->x;
				float y = aladdin->BottomPosition()->y;
				aladdin->SetPoReStart(D3DXVECTOR2(x,y));
			}
		}
	}
}

void Mission::InteractAladinWithJab(LPOBJECT jab)
{
	if (this->isColliding(this->aladdin, jab))
	{

		if (jab->GetAnimations()->GetCurrentAnimationID() == 0 && jab->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 5)
		{
			if (aladdin->GetHP() <= 0)
			{
				/*sound1->LoadSound("Sounds/Aladdin_Die.wav", "Aladdin_Die");
				sound1->Play("Aladdin_Die", 0, 1);*/
				aladdin->Die();
			}
			else
			{
				aladdin->Hurt(1);
				/*sound1->LoadSound("Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");
				sound1->Play("Aladdin_Hurt", 0, 1);*/
				
			}
		}

	}
}

void Mission::InteractAladinWithBat(LPOBJECT bat)
{

	Bat* a = (Bat*)bat;
	if (abs(this->aladdin->CenterPosition()->x - bat->CenterPosition()->x) < 100 && (bat->CollisionBox().top < this->aladdin->CollisionBox().bottom)&&(this->aladdin->CollisionBox().bottom- bat->CollisionBox().top)<=150)
	{
		a->Dive(aladdin->CenterPosition());
	}

	if (this->isColliding(this->aladdin, a)&&a->GetExist()==true)
	{
		if (check_actack_ani(aladdin))
		{
			if (aladdin->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 4)
			{
				a->Die();
				a->SetExist(false);
			}
		}
		else
		{
			if (aladdin->GetHP() <= 0)
			{
				/*sound1->LoadSound("Sounds/Aladdin_Die.wav", "Aladdin_Die");
				sound1->Play("Aladdin_Die", 0, 1);*/
				aladdin->Die();
			}
			else
			{
				aladdin->Hurt(1);
				/*sound1->LoadSound("Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");
				sound1->Play("Aladdin_Hurt", 0, 1);*/
				
			}
		}

	}
}

void Mission::InteractAladinWithBone(LPOBJECT bone)
{
	if (this->isColliding(this->aladdin, bone))
	{
		if (bone->GetAnimations()->GetCurrentAnimationID() == 0)
		{
			if (aladdin->GetHP() <= 0)
			{
				aladdin->Die();
			}
			else
			{
				aladdin->Hurt(1);
				bone->SetExist(false);
			}
		}
	}
}

void Mission::InteractAladinWithLeash(LPOBJECT leash)
{
	int check = CheckIsColidingWithLeash(leash);

	if (check == 1) {
		//DebugOut(L"[Mission.cpp] on: %d\n", check);
		aladdin->IsOnLeash = true;
		if (true) {
			aladdin->SetCenterPosition(D3DXVECTOR2(leash->CenterPosition()->x, aladdin->CenterPosition()->y + aladdin->dy));
			aladdin->IdleClimb();
		}
	}

	if (check == -1) {
		aladdin->IsOnLeash = true;
		if (aladdin->IsAni(Aladin::ANIMATIONS::climbjump) && aladdin->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() == 8) {
			aladdin->SetCenterPosition(D3DXVECTOR2(leash->CenterPosition()->x, aladdin->CenterPosition()->y + aladdin->dy));
			aladdin->IdleClimb();
		}

		if (aladdin->CenterPosition()->y <= leash->CollisionBox().top + 65 + 10) {
			aladdin->IsTopLeash = true;
		}
	}

}

void Mission::InteractAladinWithScreen(LPOBJECT NScreen)
{
	if (aladdin->CenterPosition()->x > NScreen->CollisionBox().left)
	{
		this->isRun = false;
	}

}

bool Mission::check_actack_ani(LPOBJECT a)
{
	if (a->GetAnimations()->GetCurrentAnimationID() == 4 || a->GetAnimations()->GetCurrentAnimationID() == 24 ||
		a->GetAnimations()->GetCurrentAnimationID() == 5 || a->GetAnimations()->GetCurrentAnimationID() == 25
		||a->GetAnimations()->GetCurrentAnimationID()==Aladin::ANIMATIONS::sitattackright || a->GetAnimations()->GetCurrentAnimationID() == Aladin::ANIMATIONS::sitattackleft
		|| a->GetAnimations()->GetCurrentAnimationID() == Aladin::ANIMATIONS::jumpattackright|| a->GetAnimations()->GetCurrentAnimationID() == Aladin::ANIMATIONS::jumpattackleft
		
		)
		return true;
	return false;
}
bool Mission::isColliding(LPOBJECT object, LPOBJECT other)
{
	RECT r_obj; RECT r_other;
	if (object->CollisionBox().left < other->CollisionBox().left) {
		r_obj.left = object->CollisionBox().left;
		r_obj.top = object->CollisionBox().top;
		r_obj.right = r_obj.left + object->GetAnimations()->GetCurrentAnimation()->Width();
		r_obj.bottom = r_obj.top + object->GetAnimations()->GetCurrentAnimation()->Height();
	}
	else if (object->CollisionBox().left >= other->CollisionBox().left)
	{
		r_obj.right = object->CollisionBox().right;
		r_obj.bottom = object->CollisionBox().bottom;
		r_obj.left = r_obj.right - object->GetAnimations()->GetCurrentAnimation()->Width();
		r_obj.top = r_obj.bottom - object->GetAnimations()->GetCurrentAnimation()->Height();
	}
	r_other = other->CollisionBox();

	float left = r_other.left - r_obj.right;
	float top = r_other.bottom - r_obj.top;
	float right = r_other.right - r_obj.left;
	float bottom = r_other.top - r_obj.bottom;
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}