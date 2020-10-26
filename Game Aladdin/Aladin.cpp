#include "Aladin.h"

Aladin::Aladin(float x, float y, float width, float height,int type) : Object(x, y, width, height)
{
	
	this->posrestart.x = x;
	this->posrestart.y = y;
	for (int i = 0; i < ALADDIN_APPLE_COUNT_ONE_TIME; i++) {
		apples[i] = new Apple(0, 0, 20, 20, 0);
	}
	SetisCo(true);
	wG = 0.00096f;
}


bool Aladin::IsAni(int aniid)
{
	if (animations != nullptr) {
		if (animations->GetCurrentAnimationID() == aniid)
			return true;
	}
	return false;
}


void Aladin::ProcessKeyStates(LPKEYBOARD keyboard)
{
	bool keyLeft = keyboard->IsKeyDown(DIK_LEFT);
	bool pressLeft = keyboard->IsKeyPress(DIK_LEFT);
	bool keyRight = keyboard->IsKeyDown(DIK_RIGHT);
	bool pressRight = keyboard->IsKeyPress(DIK_RIGHT);
	bool keyUp = keyboard->IsKeyDown(DIK_UP);
	bool keyDown = keyboard->IsKeyDown(DIK_DOWN);
	bool keyZ = keyboard->IsKeyPress(DIK_Z);
	bool keyX = keyboard->IsKeyPress(DIK_X);
	bool keyC = keyboard->IsKeyPress(DIK_C);


	//
	//---------LEFT --------//
	//
	if (keyLeft && !IsAni(ANIMATIONS::dieleft) && !IsAni(ANIMATIONS::dieright)) {
		if (IsAni(ANIMATIONS::idleleft) || IsAni(ANIMATIONS::idleright)) {
			this->WalkLeft();
		}
		else
		if (IsAni(ANIMATIONS::jumpleft) || IsAni(ANIMATIONS::jumpupleft)) {
			this->MoveLeft();
		}
		else
		if (IsAni(ANIMATIONS::jumpright)) {
			this->animations->Start(ANIMATIONS::jumpleft, this->animations->GetCurrentAnimation()->GetCurrentFrameID());
			this->MoveLeft();
		}
		else
		if (IsAni(ANIMATIONS::jumpupright)) {
			this->animations->Start(ANIMATIONS::jumpupleft, this->animations->GetCurrentAnimation()->GetCurrentFrameID());
			this->MoveLeft();
		}
		else
		if (IsAni(ANIMATIONS::climbjump)) {
			this->ClimbDropDown();
			this->MoveLeft();
		}
	}
	else {
		this->animations->Stop(ANIMATIONS::walkleft);
		if (wV.x < 0) wV.x = 0;
	}



	//
	//---------RIGHT --------//
	//
	if (keyRight && !IsAni(ANIMATIONS::dieleft) && !IsAni(ANIMATIONS::dieright)) {
		if (IsAni(ANIMATIONS::idleleft) || IsAni(ANIMATIONS::idleright)) {
			this->WalkRight();
		}
		else
		if (IsAni(ANIMATIONS::jumpright) || IsAni(ANIMATIONS::jumpupright)) {
			this->MoveRight();
		}
		else
		if (IsAni(ANIMATIONS::jumpleft)) {
			this->animations->Start(ANIMATIONS::jumpright, this->animations->GetCurrentAnimation()->GetCurrentFrameID());
			this->MoveRight();
		}
		else
		if (IsAni(ANIMATIONS::jumpupleft)) {
			this->animations->Start(ANIMATIONS::jumpupright, this->animations->GetCurrentAnimation()->GetCurrentFrameID());
			this->MoveRight();
		}
		else
		if (IsAni(ANIMATIONS::climbjump)) {
			this->ClimbDropDown();
			this->MoveRight();
		}
	}
	else {
		this->animations->Stop(ANIMATIONS::walkright);
		if (wV.x > 0) wV.x = 0;
	}


	//DebugOut(L" ani: %d | is top: %d\n", animations->GetCurrentAnimationID(), IsTopLeash);

	//
	//--------- UP --------//
	//
	if (keyUp && !IsAni(ANIMATIONS::dieleft) && !IsAni(ANIMATIONS::dieright)) {
		if (IsAni(ANIMATIONS::idleright) || IsAni(ANIMATIONS::idleleft)) {
			if (Direction == 1)
				this->UpRight();
			else
				this->UpLeft();
		}
		
		if (IsAni(ANIMATIONS::climbup) || IsAni(ANIMATIONS::idleclimb)) {
			if (IsOnLeash && !IsTopLeash) {
				this->ClimbUp();
			}
			else
			{	
				wV.y = 0.0f;
				this->IdleClimb();
			}
		}
		
		/*else 
		{	
			this->animations->Stop(ANIMATIONS::climbup);
			wV.y = 0.0f;
		}*/
	}
	else {
		if (IsAni(ANIMATIONS::climbup)) {
			wV.y = 0.0f;
		}
		this->animations->Stop(ANIMATIONS::climbup);
		this->animations->Stop(ANIMATIONS::upright);
		this->animations->Stop(ANIMATIONS::upleft);
	}
	

	//
	//--------- DOWN --------//
	//
	if (keyDown && !IsAni(ANIMATIONS::dieleft) && !IsAni(ANIMATIONS::dieright)) {
		if (IsAni(ANIMATIONS::idleright) || IsAni(ANIMATIONS::idleleft)) {
			if (Direction == 1)
				this->SitRight();
			else
				this->SitLeft();
		}
		else
		if (IsAni(ANIMATIONS::idleclimb) || IsAni(ANIMATIONS::climbdown)) {
			if (IsOnLeash == true) {
				this->ClimbDown();
			}
			else
			{	
				this->ClimbDropDown();
				//this->animations->Stop(ANIMATIONS::climbdown);
			}
		}
	}
	else {
		if (IsAni(ANIMATIONS::climbdown))
			wV.y = 0.0f;
		this->animations->Stop(ANIMATIONS::sitleft);
		this->animations->Stop(ANIMATIONS::sitright);
		this->animations->Stop(ANIMATIONS::climbdown);
	}



	//
	//--------- C --------//
	//
	if (keyC && !IsAni(ANIMATIONS::dieleft) && !IsAni(ANIMATIONS::dieright)) {
		if (IsAni(ANIMATIONS::idleright) || IsAni(ANIMATIONS::idleleft)) {
			if (Direction == 1)
				this->JumpUpRight();
			else
				this->JumpUpLeft();
		}
		else
		if (IsAni(ANIMATIONS::walkright)) {
			this->JumpRight();
		}
		else
		if (IsAni(ANIMATIONS::walkleft)) {
			this->JumpLeft();
		}
		else
		if ( IsAni(ANIMATIONS::idleclimb) || IsAni(ANIMATIONS::climbup) || IsAni(ANIMATIONS::climbdown)) {
			this->ClimbJump();
		}

	}



	//
	//--------- X --------//
	//
	if (keyX && !IsAni(ANIMATIONS::dieleft) && !IsAni(ANIMATIONS::dieright)) {
		if (IsAni(ANIMATIONS::idleleft) || IsAni(ANIMATIONS::idleright)) {
			if (Direction == 1)
				this->IdleAttackRight();
			else
				this->IdleAttackLeft();
		}
		if (IsAni(ANIMATIONS::walkleft) || IsAni(ANIMATIONS::walkright)) {
			if (Direction == 1)
				this->WalkAttackRight();
			else
				this->WalkAttackLeft();
		}
		else
		if (IsAni(ANIMATIONS::jumpupleft) || IsAni(ANIMATIONS::jumpupright)) {
			if (Direction == 1)
				this->JumpUpAttackRight();
			else
				this->JumpUpAttackLeft();
		}
		else
		if (IsAni(ANIMATIONS::jumpleft) || IsAni(ANIMATIONS::jumpright)) {
			if (Direction == 1)
				this->JumpAttackRight();
			else
				this->JumpAttackLeft();
		}
		else
		if (IsAni(ANIMATIONS::sitleft) || IsAni(ANIMATIONS::sitright)) {
			if (Direction == 1)
				this->SitAttackRight();
			else
				this->SitAttackLeft();
		}
	}



	//
	//--------- Z --------//
	//
	if (keyZ && throwtime <= 0 && !IsAni(ANIMATIONS::dieleft) && !IsAni(ANIMATIONS::dieright)) {
		throwtime = ALADDIN_THROW_TIME;
		if (IsAni(ANIMATIONS::idleright) || IsAni(ANIMATIONS::idleleft)) {
			if (Direction == 1)
				this->IdleThrowRight();
			else
				this->IdleThrowLeft();
		}
		else
		if (IsAni(ANIMATIONS::jumpupleft) || IsAni(ANIMATIONS::jumpupright)) {
			if (Direction == 1)
				this->JumpUpThrowRight();
			else
				this->JumpUpThrowLeft();
		}
	}


	//
	//--------- Idle --------//
	//
	if (	!keyUp && !keyDown && !keyRight && !keyLeft && !keyX && !keyZ && !keyC 
		&&	this->animations->GetCurrentAnimationID() <= 0
		/*&&	!IsAni(ANIMATIONS::walkleft) && !IsAni(ANIMATIONS::walkright)
		&&	!IsAni(ANIMATIONS::jumpupleft) && !IsAni(ANIMATIONS::jumpupright)
		&&  !IsAni(ANIMATIONS::jumpupthrowleft) && !IsAni(ANIMATIONS::jumpupthrowright)
		&&	!IsAni(ANIMATIONS::jumpleft) && !IsAni(ANIMATIONS::jumpright)	
		&&  !IsAni(ANIMATIONS::dropdownleft) && !IsAni(ANIMATIONS::dropdownright)
		&&  !IsAni(ANIMATIONS::idlethrowleft) && !IsAni(ANIMATIONS::idlethrowright)*/
		)
	{
		if (IsOnLeash) {
			IdleClimb();
		}
		else {
			if (Direction == 1)
				this->IdleRight();
			else
				this->IdleLeft();
		}
		
	}
	
	//DebugOut(L"ani: %d\n", this->animations->GetCurrentAnimationID());

}



void Aladin::Init(LPDIRECT3DDEVICE9 d3dd9)
{
	LPTEXTURE texture = new  Texture(L"Aladdin.png", D3DCOLOR_XRGB(255, 0, 255), d3dd9);
	//Animation idle right
	LPSPRITE sprite0 = new Sprite(3, 9, 40, 59, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite1 = new Sprite(47, 11, 88, 58, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite2 = new Sprite(95, 6, 135, 58, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite3 = new Sprite(143, 3, 187, 58, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite4 = new Sprite(197, 6, 238, 57, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite5 = new Sprite(250, 5, 292, 56, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite6 = new Sprite(303, 2, 347, 55, texture->LPDIRECT3DTEXTURE());

	LPSPRITE sprite7 = new Sprite(6, 83, 46, 135, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite8 = new Sprite(51, 81, 112, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite9 = new Sprite(116, 80, 178, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite10 = new Sprite(180, 81, 221, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite11 = new Sprite(228, 81, 267, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite12 = new Sprite(275, 81, 311, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite13 = new Sprite(319, 81, 359, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite14 = new Sprite(366, 79, 407, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite15 = new Sprite(417, 61, 460, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite16 = new Sprite(465, 57, 507, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite17 = new Sprite(516, 63, 558, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite18 = new Sprite(568, 72, 610, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite19 = new Sprite(619, 80, 660, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite20 = new Sprite(668, 80, 708, 134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite21 = new Sprite(715, 81, 754, 134, texture->LPDIRECT3DTEXTURE());

	LPSPRITE sprite22 = new Sprite(3, 165, 39, 218, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite23 = new Sprite(46, 165, 86, 218, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite24 = new Sprite(91, 163, 132, 218, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite25 = new Sprite(140, 155, 178, 218, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite26 = new Sprite(188, 151, 229, 218, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite27 = new Sprite(238, 159, 280, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite28 = new Sprite(287, 168, 325, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite29 = new Sprite(334, 168, 373, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite30 = new Sprite(378, 168, 417, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite31 = new Sprite(425, 156, 463, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite32 = new Sprite(472, 150, 510, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite33 = new Sprite(519, 143, 555, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite34 = new Sprite(568, 138, 607, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite35 = new Sprite(615, 155, 657, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite36 = new Sprite(666, 163, 707, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite37 = new Sprite(715, 163, 755, 217, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite38 = new Sprite(762, 164, 801, 217, texture->LPDIRECT3DTEXTURE());

	//Animation walk right
	LPSPRITE sprite39 = new Sprite(14, 1225, 54, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite40 = new Sprite(66, 1222, 109, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite41 = new Sprite(120, 1220, 161, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite42 = new Sprite(171, 1216, 212, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite43 = new Sprite(220, 1216, 272, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite44 = new Sprite(279, 1219, 325, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite45 = new Sprite(334, 1215, 376, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite46 = new Sprite(386, 1221, 427, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite47 = new Sprite(440, 1219, 475, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite48 = new Sprite(488, 1216, 537, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite49 = new Sprite(547, 1215, 602, 1273, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite50 = new Sprite(611, 1219, 666, 1274, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite51 = new Sprite(679, 1218, 723, 1275, texture->LPDIRECT3DTEXTURE());

	//Animation sit right
	LPSPRITE sprite52 = new Sprite(205, 500, 247, 549, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite53 = new Sprite(258, 509, 306, 549, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite54 = new Sprite(315, 519, 369, 549, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite55 = new Sprite(378, 516, 431, 551, texture->LPDIRECT3DTEXTURE());

	//Animation sit throw right
	LPSPRITE sprite56 = new Sprite(9, 571, 46, 615, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite57 = new Sprite(58, 567, 95, 615, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite58 = new Sprite(107, 571, 157, 619, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite59 = new Sprite(164, 578, 246, 615, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite60 = new Sprite(256, 579, 313, 616, texture->LPDIRECT3DTEXTURE());

	//Animation sit attack right
	LPSPRITE sprite61 = new Sprite(9, 640, 56, 673, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite62 = new Sprite(64, 642, 109, 673, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite63 = new Sprite(115, 640, 186, 673, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite64 = new Sprite(193, 639, 285, 673, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite65 = new Sprite(298, 640, 382, 673, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite66 = new Sprite(392, 640, 463, 673, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite67 = new Sprite(475, 642, 520, 673, texture->LPDIRECT3DTEXTURE());

	//Animation Jump up right
	LPSPRITE sprite68 = new Sprite(8, 846, 67, 889, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite69 = new Sprite(75, 828, 127, 890, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite70 = new Sprite(137, 829, 191, 890, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite71 = new Sprite(203, 824, 257, 893, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite72 = new Sprite(269, 820, 320, 894, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite73 = new Sprite(336, 829, 374, 895, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite74 = new Sprite(390, 818, 425, 897, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite75 = new Sprite(448, 808, 482, 901, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite76 = new Sprite(504, 810, 538, 903, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite77 = new Sprite(564, 812, 598, 905, texture->LPDIRECT3DTEXTURE());

	//Animation Jump Right
	LPSPRITE sprite78 = new Sprite(10, 705, 51, 747, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite79 = new Sprite(66, 683, 111, 759, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite80 = new Sprite(124, 686, 181, 743, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite81 = new Sprite(199, 698, 257, 740, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite82 = new Sprite(273, 696, 334, 744, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite83 = new Sprite(350, 692, 408, 745, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite84 = new Sprite(419, 688, 472, 746, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite85 = new Sprite(491, 680, 541, 765, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite86 = new Sprite(560, 719, 619, 763, texture->LPDIRECT3DTEXTURE());

	//Animation walk left
	LPSPRITE sprite87 = new Sprite(1875, 1340, 1915, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite88 = new Sprite(1820, 1337, 1863, 1389, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite89 = new Sprite(1768, 1335, 1809, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite90 = new Sprite(1717, 1331, 1758, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite91 = new Sprite(1657, 1331, 1709, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite92 = new Sprite(1604, 1334, 1650, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite93 = new Sprite(1553, 1330, 1595, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite94 = new Sprite(1502, 1336, 1543, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite95 = new Sprite(1454, 1334, 1489, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite96 = new Sprite(1392, 1331, 1441, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite97 = new Sprite(1327, 1330, 1382, 1388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite98 = new Sprite(1263, 1334, 1318, 1389, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite99 = new Sprite(1206, 1333, 1250, 1390, texture->LPDIRECT3DTEXTURE());

	//Animation Idle Left
	LPSPRITE sprite100 = new Sprite(1889, 124, 1926, 174, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite101 = new Sprite(1841, 124, 1883, 174, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite102 = new Sprite(1794, 121, 1838, 171, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite103 = new Sprite(1742, 117, 1790, 167, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite104 = new Sprite(1691, 121, 1732, 172, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite105 = new Sprite(1637, 120, 1679, 171, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite106 = new Sprite(1582, 117, 1626, 170, texture->LPDIRECT3DTEXTURE());

	LPSPRITE sprite107 = new Sprite(1883, 198, 1923, 250, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite108 = new Sprite(1817, 195, 1879, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite109 = new Sprite(1751, 195, 1813, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite110 = new Sprite(1705, 196, 1749, 250, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite111 = new Sprite(1662, 196, 1701, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite112 = new Sprite(1618, 196, 1655, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite113 = new Sprite(1569, 196, 1610, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite114 = new Sprite(1522, 194, 1563, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite115 = new Sprite(1475, 193, 1512, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite116 = new Sprite(1426, 193, 1464, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite117 = new Sprite(1375, 193, 1413, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite118 = new Sprite(1321, 194, 1361, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite119 = new Sprite(1269, 195, 1310, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite120 = new Sprite(1221, 195, 1261, 249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite121 = new Sprite(1175, 196, 1214, 249, texture->LPDIRECT3DTEXTURE());

	LPSPRITE sprite122 = new Sprite(1890, 280, 1926, 333, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite123 = new Sprite(1843, 280, 1883, 333, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite124 = new Sprite(1797, 278, 1838, 333, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite125 = new Sprite(1751, 270, 1789, 333, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite126 = new Sprite(1700, 266, 1741, 333, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite127 = new Sprite(1649, 274, 1691, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite128 = new Sprite(1604, 283, 1642, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite129 = new Sprite(1556, 283, 1595, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite130 = new Sprite(1512, 283, 1551, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite131 = new Sprite(1466, 271, 1504, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite132 = new Sprite(1419, 265, 1457, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite133 = new Sprite(1374, 258, 1410, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite134 = new Sprite(1322, 253, 1361, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite135 = new Sprite(1272, 270, 1314, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite136 = new Sprite(1222, 278, 1263, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite137 = new Sprite(1174, 278, 1214, 332, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite138 = new Sprite(1128, 279, 1167, 332, texture->LPDIRECT3DTEXTURE());


	//Animation Idle Throw Right
	LPSPRITE sprite139 = new Sprite(7, 235, 50, 291, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite140 = new Sprite(57, 232, 98, 291, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite141 = new Sprite(109, 233, 147, 291, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite142 = new Sprite(163, 231, 209, 291, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite143 = new Sprite(221, 233, 258, 291, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite144 = new Sprite(268, 239, 307, 291, texture->LPDIRECT3DTEXTURE());


	//Animation Idle Throw Left
	LPSPRITE sprite145 = new Sprite(1879, 350, 1922, 406, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite146 = new Sprite(1831, 347, 1872, 406, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite147 = new Sprite(1782, 348, 1820, 406, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite148 = new Sprite(1720, 346, 1766, 406, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite149 = new Sprite(1671, 348, 1708, 406, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite150 = new Sprite(1622, 354, 1661, 406, texture->LPDIRECT3DTEXTURE());


	//Animation Idle Attack Right
	LPSPRITE sprite151 = new Sprite(5, 337, 50, 388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite152 = new Sprite(54, 326, 105, 388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite153 = new Sprite(115, 314, 160, 388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite154 = new Sprite(171, 319, 253, 388, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite155 = new Sprite(260, 335, 311, 388, texture->LPDIRECT3DTEXTURE());

	//Animation Idle Attack Left
	LPSPRITE sprite156 = new Sprite(1879, 452, 1925, 503, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite157 = new Sprite(1824, 441, 1875, 503, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite158 = new Sprite(1769, 429, 1814, 503, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite159 = new Sprite(1676, 439, 1766, 503, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite160 = new Sprite(1618, 450, 1669, 503, texture->LPDIRECT3DTEXTURE());

	//Animation Up Right
	LPSPRITE sprite161 = new Sprite(11, 496, 50, 549, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite162 = new Sprite(59, 490, 104, 549, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite163 = new Sprite(111, 491, 160, 549, texture->LPDIRECT3DTEXTURE());

	//Animation Up Left
	LPSPRITE sprite164 = new Sprite(1879, 611, 1918, 664, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite165 = new Sprite(1825, 605, 1870, 664, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite166 = new Sprite(1769, 606, 1818, 664, texture->LPDIRECT3DTEXTURE());

	//Animation sit left
	LPSPRITE sprite167 = new Sprite(1682, 615, 1724, 664, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite168 = new Sprite(1623, 624, 1671, 664, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite169 = new Sprite(1560, 634, 1614, 664, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite170 = new Sprite(1498, 631, 1551, 666, texture->LPDIRECT3DTEXTURE());

	//Animation sit throw left
	LPSPRITE sprite171 = new Sprite(1875, 686, 1926, 730, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite172 = new Sprite(1834, 682, 1871, 730, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite173 = new Sprite(1772, 686, 1822, 734, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite174 = new Sprite(1683, 693, 1765, 730, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite175 = new Sprite(1616, 694, 1673, 731, texture->LPDIRECT3DTEXTURE());

	//Animation sit attack left
	LPSPRITE sprite176 = new Sprite(1873, 753, 1920, 788, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite177 = new Sprite(1820, 756, 1865, 788, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite178 = new Sprite(1743, 740, 1815, 788, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite179 = new Sprite(1644, 754, 1736, 800, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite180 = new Sprite(1574, 755, 1658, 788, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite181 = new Sprite(1466, 755, 1537, 788, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite182 = new Sprite(1409, 757, 1454, 788, texture->LPDIRECT3DTEXTURE());

	//Animation Jump up left
	LPSPRITE sprite183 = new Sprite(1862, 961, 1921, 1004, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite184 = new Sprite(1802, 942, 1854, 1005, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite185 = new Sprite(1738, 944, 1792, 1005, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite186 = new Sprite(1672, 939, 1726, 1008, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite187 = new Sprite(1609, 935, 1660, 1010, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite188 = new Sprite(1555, 944, 1593, 1011, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite189 = new Sprite(1504, 933, 1539, 1012, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite190 = new Sprite(1447, 923, 1495, 1016, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite191 = new Sprite(1391, 925, 1425, 1018, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite192 = new Sprite(1331, 927, 1365, 1020, texture->LPDIRECT3DTEXTURE());

	//Animation Jump left
	LPSPRITE sprite193 = new Sprite(1878, 820, 1919, 862, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite194 = new Sprite(1818, 798, 1863, 874, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite195 = new Sprite(1748, 801, 1805, 858, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite196 = new Sprite(1672, 813, 1730, 855, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite197 = new Sprite(1595, 811, 1656, 859, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite198 = new Sprite(1521, 807, 1579, 860, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite199 = new Sprite(1457, 803, 1510, 861, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite200 = new Sprite(1388, 795, 1438, 880, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite201 = new Sprite(1310, 834, 1369, 878, texture->LPDIRECT3DTEXTURE());

	//Animation Jumpup throw right
	LPSPRITE sprite202 = new Sprite(19, 1005, 68, 1060, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite203 = new Sprite(77, 1007, 120, 1059, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite204 = new Sprite(132, 1008, 171, 1061, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite205 = new Sprite(253, 1012, 293, 1064, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite206 = new Sprite(185, 1008, 237, 1061, texture->LPDIRECT3DTEXTURE());

	//Animation Jumpup throw left
	LPSPRITE sprite207 = new Sprite(1861, 1120, 1910, 1175, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite208 = new Sprite(1809, 1122, 1852, 1174, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite209 = new Sprite(1758, 1123, 1797, 1176, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite210 = new Sprite(1692, 1123, 1744, 1176, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite211 = new Sprite(1636, 1127, 1676, 1179, texture->LPDIRECT3DTEXTURE());

	//Animation Jumpup attack right
	LPSPRITE sprite212 = new Sprite(13, 1077, 65, 1131, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite213 = new Sprite(75, 1075, 125, 1127, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite214 = new Sprite(140, 1067, 187, 1133, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite215 = new Sprite(199, 1078, 251, 1134, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite216 = new Sprite(260, 1069, 350, 1130, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite217 = new Sprite(361, 1087, 419, 1142, texture->LPDIRECT3DTEXTURE());

	//Animation Jumpup attack left
	LPSPRITE sprite218 = new Sprite(1856, 1191, 1916, 1248, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite219 = new Sprite(1804, 1190, 1854, 1242, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite220 = new Sprite(1742, 1182, 1789, 1248, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite221 = new Sprite(1678, 1193, 1730, 1249, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite222 = new Sprite(1580, 1194, 1663, 1245, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite223 = new Sprite(1521, 1202, 1568, 1257, texture->LPDIRECT3DTEXTURE());

	//Animation Climb up right
	LPSPRITE sprite224 = new Sprite(11, 1362, 40, 1448, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite225 = new Sprite(53, 1361, 81, 1450, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite226 = new Sprite(94, 1374, 122, 1448, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite227 = new Sprite(133, 1377, 175, 1439, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite228 = new Sprite(186, 1363, 217, 1439, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite229 = new Sprite(231, 1358, 260, 1444, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite230 = new Sprite(274, 1367, 302, 1446, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite231 = new Sprite(314, 1377, 346, 1440, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite232 = new Sprite(406, 1362, 434, 1443, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite233 = new Sprite(356, 1377, 398, 1439, texture->LPDIRECT3DTEXTURE());

	//Animation Climb up left
	LPSPRITE sprite234 = new Sprite(1885, 1477, 1918, 1564, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite235 = new Sprite(1848, 1476, 1876, 1565, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite236 = new Sprite(1807, 1489, 1835, 1567, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite237 = new Sprite(1754, 1492, 1796, 1554, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite238 = new Sprite(1712, 1478, 1749, 1555, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite239 = new Sprite(1668, 1473, 1698, 1562, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite240 = new Sprite(1627, 1482, 1655, 1561, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite241 = new Sprite(1581, 1492, 1615, 1558, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite242 = new Sprite(1532, 1492, 1574, 1554, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite243 = new Sprite(1492, 1477, 1520, 1558, texture->LPDIRECT3DTEXTURE());


	//Animation Drop Down right
	LPSPRITE sprite244 = new Sprite(10, 1870, 44, 1943, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite245 = new Sprite(65, 1873, 90, 1950, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite246 = new Sprite(100, 1874, 136, 1945, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite247 = new Sprite(144, 1874, 192, 1938, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite248 = new Sprite(204, 1875, 263, 1929, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite249 = new Sprite(281, 1876, 340, 1917, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite250 = new Sprite(354, 1869, 406, 1923, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite251 = new Sprite(422, 1871, 469, 1938, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite252 = new Sprite(482, 1866, 527, 1941, texture->LPDIRECT3DTEXTURE());

	//Animation Drop Down left
	LPSPRITE sprite253 = new Sprite(1885, 1985, 1919, 2060, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite254 = new Sprite(1839, 1988, 1864, 2065, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite255 = new Sprite(1793, 1989, 1829, 2060, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite256 = new Sprite(1737, 1989, 1788, 2055, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite257 = new Sprite(1666, 1990, 1726, 2046, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite258 = new Sprite(1589, 1991, 1648, 2038, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite259 = new Sprite(1522, 1984, 1575, 2040, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite260 = new Sprite(1460, 1986, 1507, 2053, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite261 = new Sprite(1402, 1981, 1447, 2056, texture->LPDIRECT3DTEXTURE());

	//Animation Fall Right
	LPSPRITE sprite262 = new Sprite(15, 901, 69, 984, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite263 = new Sprite(87, 911, 141, 976, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite264 = new Sprite(145, 942, 212, 979, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite265 = new Sprite(215, 949, 279, 978, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite266 = new Sprite(288, 950, 356, 980, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite267 = new Sprite(366, 948, 442, 982, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite268 = new Sprite(451, 935, 537, 982, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite269 = new Sprite(549, 928, 635, 983, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite270 = new Sprite(644, 925, 740, 986, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite271 = new Sprite(748, 925, 844, 986, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite272 = new Sprite(853, 926, 955, 986, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite273 = new Sprite(968, 928, 1070, 978, texture->LPDIRECT3DTEXTURE());

	//Animation Fall Left
	LPSPRITE sprite274 = new Sprite(1854, 1016, 1914, 1099, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite275 = new Sprite(1787, 1026, 1842, 1091, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite276 = new Sprite(1717, 1057, 1784, 1094, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite277 = new Sprite(1650, 1064, 1714, 1093, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite278 = new Sprite(1573, 1065, 1641, 1095, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite279 = new Sprite(1487, 1063, 1563, 1097, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite280 = new Sprite(1392, 1050, 1478, 1097, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite281 = new Sprite(1294, 1043, 1380, 1098, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite282 = new Sprite(1189, 1040, 1285, 1101, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite283 = new Sprite(1085, 1040, 1181, 1101, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite284 = new Sprite(974, 1041, 1076, 1101, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite285 = new Sprite(859, 1043, 961, 1093, texture->LPDIRECT3DTEXTURE());

	//Animation Stop walk right
	LPSPRITE sprite286 = new Sprite(11, 1293, 68, 1350, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite287 = new Sprite(83, 1294, 127, 1350, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite288 = new Sprite(134, 1284, 185, 1350, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite289 = new Sprite(200, 1283, 246, 1348, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite290 = new Sprite(256, 1285, 298, 1349, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite291 = new Sprite(309, 1306, 364, 1352, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite292 = new Sprite(376, 1308, 428, 1352, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite293 = new Sprite(437, 1300, 483, 1352, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite294 = new Sprite(498, 1294, 549, 1346, texture->LPDIRECT3DTEXTURE());

	//Animation Stop walk left
	LPSPRITE sprite295 = new Sprite(1861, 1408, 1918, 1465, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite296 = new Sprite(1802, 1409, 1846, 1465, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite297 = new Sprite(1744, 1399, 1795, 1465, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite298 = new Sprite(1683, 1398, 1729, 1463, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite299 = new Sprite(1631, 1400, 1673, 1464, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite300 = new Sprite(1565, 1421, 1620, 1467, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite301 = new Sprite(1501, 1423, 1553, 1467, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite302 = new Sprite(1446, 1409, 1431, 1461, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite303 = new Sprite(1380, 1409, 1431, 1461, texture->LPDIRECT3DTEXTURE());

	//Animation Hurt Right
	LPSPRITE sprite304 = new Sprite(9, 2167, 51, 2213, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite305 = new Sprite(58, 2161, 113, 2213, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite306 = new Sprite(122, 2162, 181, 2212, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite307 = new Sprite(189, 2163, 269, 2211, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite308 = new Sprite(282, 2160, 343, 2211, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite309 = new Sprite(351, 2161, 410, 2210, texture->LPDIRECT3DTEXTURE());

	//Animation Hurt Left
	LPSPRITE sprite310 = new Sprite(1877, 2282, 1930, 2328, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite311 = new Sprite(1816, 2276, 1872, 2328, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite312 = new Sprite(1748, 2277, 1807, 2327, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite313 = new Sprite(1660, 2278, 1740, 2326, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite314 = new Sprite(1586, 2275, 1647, 2326, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite315 = new Sprite(1519, 2276, 1581, 2325, texture->LPDIRECT3DTEXTURE());

	//Animation Die Right
	LPSPRITE sprite316 = new Sprite(1, 2234, 81, 2282, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite317 = new Sprite(87, 2231, 148, 2282, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite318 = new Sprite(160, 2224, 205, 2282, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite319 = new Sprite(213, 2224, 258, 2282, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite320 = new Sprite(264, 2231, 303, 281, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite321 = new Sprite(312, 2230, 352, 2281, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite322 = new Sprite(361, 2230, 396, 2281, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite323 = new Sprite(407, 2230, 443, 2281, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite324 = new Sprite(454, 2232, 493, 2281, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite325 = new Sprite(505, 2227, 549, 2283, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite326 = new Sprite(560, 2228, 601, 2281, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite327 = new Sprite(614, 2232, 653, 2282, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite328 = new Sprite(661, 2232, 701, 2283, texture->LPDIRECT3DTEXTURE());

	LPSPRITE sprite329 = new Sprite(2, 2335, 39, 2386, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite330 = new Sprite(49, 2329, 86, 2386, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite331 = new Sprite(97, 2331, 140, 2386, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite332 = new Sprite(148, 2333, 209, 2386, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite333 = new Sprite(223, 2336, 284, 2387, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite334 = new Sprite(296, 2310, 372, 2393, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite335 = new Sprite(383, 2309, 460, 2394, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite336 = new Sprite(476, 2309, 551, 2394, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite337 = new Sprite(567, 2311, 635, 2394, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite338 = new Sprite(654, 2313, 720, 2394, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite339 = new Sprite(734, 2321, 800, 2395, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite340 = new Sprite(811, 2323, 877, 2397, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite341 = new Sprite(888, 2323, 954, 2397, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite342 = new Sprite(970, 2325, 1036, 2399, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite343 = new Sprite(1049, 2325, 1115, 2399, texture->LPDIRECT3DTEXTURE());

	//Animation Die Left
	LPSPRITE sprite344 = new Sprite(1848, 2349, 1928, 2397, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite345 = new Sprite(1781, 2346, 1842, 2397, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite346 = new Sprite(1724, 2337, 1769, 2395, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite347 = new Sprite(1671, 2338, 1716, 2395, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite348 = new Sprite(1626, 2346, 1665, 2396, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite349 = new Sprite(1577, 2345, 1617, 2396, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite350 = new Sprite(1533, 2345, 1568, 2396, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite351 = new Sprite(1486, 2345, 1522, 2396, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite352 = new Sprite(1436, 2347, 1475, 2396, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite353 = new Sprite(1380, 2342, 1424, 2398, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite354 = new Sprite(1328, 2343, 1369, 2396, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite355 = new Sprite(1276, 2347, 1315, 2397, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite356 = new Sprite(1225, 2347, 1268, 2398, texture->LPDIRECT3DTEXTURE());

	LPSPRITE sprite357 = new Sprite(1890, 2441, 1939, 2501, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite358 = new Sprite(1837, 2441, 1880, 2501, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite359 = new Sprite(1789, 2446, 1832, 2501, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite360 = new Sprite(1720, 2442, 1781, 2508, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite361 = new Sprite(1645, 2443, 1706, 2507, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite362 = new Sprite(1553, 2425, 1633, 2508, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite363 = new Sprite(1469, 2424, 1546, 2509, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite364 = new Sprite(1378, 2424, 1453, 2509, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite365 = new Sprite(1294, 2426, 1362, 2509, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite366 = new Sprite(1209, 2428, 1275, 2509, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite367 = new Sprite(1129, 2436, 1195, 2510, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite368 = new Sprite(1052, 2438, 1118, 2512, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite369 = new Sprite(975, 2438, 1041, 2512, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite370 = new Sprite(893, 2440, 959, 2514, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite371 = new Sprite(814, 2440, 880, 2514, texture->LPDIRECT3DTEXTURE());

	//Animation revival Right
	LPSPRITE sprite372 = new Sprite(2, 2472, 66, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite373 = new Sprite(79, 2475, 135, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite374 = new Sprite(143, 2508, 163, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite375 = new Sprite(173, 2503, 196, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite376 = new Sprite(205, 2495, 230, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite377 = new Sprite(243, 2483, 270, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite378 = new Sprite(278, 2474, 316, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite379 = new Sprite(333, 2460, 370, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite380 = new Sprite(382, 2460, 424, 2544, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite381 = new Sprite(442, 2454, 495, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite382 = new Sprite(510, 2441, 553, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite383 = new Sprite(563, 2426, 613, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite384 = new Sprite(623, 2407, 668, 2541, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite385 = new Sprite(682, 2400, 722, 2541, texture->LPDIRECT3DTEXTURE());

	//Animation revival Left
	LPSPRITE sprite386 = new Sprite(1858, 2587, 1927, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite387 = new Sprite(1794, 2590, 1850, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite388 = new Sprite(1766, 2623, 1786, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite389 = new Sprite(1733, 2618, 1756, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite390 = new Sprite(1699, 2610, 1724, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite391 = new Sprite(1659, 2598, 1686, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite392 = new Sprite(1613, 2589, 1651, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite393 = new Sprite(1559, 2575, 1596, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite394 = new Sprite(1505, 2575, 1547, 2659, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite395 = new Sprite(1434, 2569, 1487, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite396 = new Sprite(1376, 2556, 1419, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite397 = new Sprite(1316, 2541, 1366, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite398 = new Sprite(1261, 2522, 1306, 2656, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite399 = new Sprite(1207, 2515, 1247, 2656, texture->LPDIRECT3DTEXTURE());

	//Animation Jump attack right
	LPSPRITE sprite400 = new Sprite(15, 2750, 55, 2798, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite401 = new Sprite(71, 2744, 106, 2798, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite402 = new Sprite(119, 2741, 168, 2798, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite403 = new Sprite(187, 2742, 228, 2799, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite404 = new Sprite(238, 2729, 289, 2794, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite405 = new Sprite(312, 2727, 366, 2786, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite406 = new Sprite(412, 2732, 504, 2795, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite407 = new Sprite(530, 2746, 592, 2798, texture->LPDIRECT3DTEXTURE());

	//Animation Jump attack left
	LPSPRITE sprite408 = new Sprite(1874, 2865, 1914, 2913, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite409 = new Sprite(1823, 2859, 1858, 2913, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite410 = new Sprite(1761, 2856, 1810, 2913, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite411 = new Sprite(1701, 2857, 1742, 2914, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite412 = new Sprite(1640, 2844, 1691, 2909, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite413 = new Sprite(1563, 2842, 1617, 2901, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite414 = new Sprite(1425, 2839, 1517, 2911, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite415 = new Sprite(1337, 2861, 1399, 2913, texture->LPDIRECT3DTEXTURE());

	//Animation Walk attack right
	LPSPRITE sprite416 = new Sprite(25, 3798, 60, 3850, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite417 = new Sprite(70, 3790, 121, 3850, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite418 = new Sprite(131, 3797, 181, 3850, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite419 = new Sprite(191, 3790, 239, 3850, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite420 = new Sprite(249, 3795, 322, 3850, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite421 = new Sprite(332, 3800, 392, 3850, texture->LPDIRECT3DTEXTURE());

	//Animation Walk attack left
	LPSPRITE sprite422 = new Sprite(1869, 3913, 1904, 3965, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite423 = new Sprite(1808, 3905, 1859, 3965, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite424 = new Sprite(1748, 3912, 1798, 3965, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite425 = new Sprite(1690, 3905, 1738, 3965, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite426 = new Sprite(1607, 3910, 1680, 3965, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite427 = new Sprite(1537, 3915, 1597, 3965, texture->LPDIRECT3DTEXTURE());

	//Animation walk throw right
	LPSPRITE sprite428 = new Sprite(17, 3889, 54, 3944, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite429 = new Sprite(62, 3888, 111, 3944, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite430 = new Sprite(123, 3889, 172, 3944, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite431 = new Sprite(183, 3882, 238, 3944, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite432 = new Sprite(241, 3881, 288, 3944, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite433 = new Sprite(324, 3887, 357, 3944, texture->LPDIRECT3DTEXTURE());

	//Animation walk throw left
	LPSPRITE sprite434 = new Sprite(1875, 4004, 1912, 4059, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite435 = new Sprite(1818, 4003, 1867, 4059, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite436 = new Sprite(1757, 4004, 1806, 4059, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite437 = new Sprite(1691, 3997, 1746, 4059, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite438 = new Sprite(1641, 3996, 1688, 4059, texture->LPDIRECT3DTEXTURE());
	LPSPRITE sprite439 = new Sprite(1572, 4002, 1605, 4059, texture->LPDIRECT3DTEXTURE());

	// ani idle

	Animation* ani_idle_right = new Animation();
	ani_idle_right->AddFrame(sprite0, 600);
	ani_idle_right->AddFrame(sprite1, 200);
	ani_idle_right->AddFrame(sprite2, 200);
	ani_idle_right->AddFrame(sprite3, 400);
	ani_idle_right->AddFrame(sprite4, 100);
	ani_idle_right->AddFrame(sprite5, 200);
	ani_idle_right->AddFrame(sprite6, 400);
	ani_idle_right->AddFrame(sprite4, 100);
	ani_idle_right->AddFrame(sprite2, 200);
	ani_idle_right->AddFrame(sprite3, 300);
	ani_idle_right->AddFrame(sprite4, 100);
	ani_idle_right->AddFrame(sprite5, 300);
	ani_idle_right->AddFrame(sprite6, 300);
	ani_idle_right->AddFrame(sprite4, 100);
	ani_idle_right->AddFrame(sprite2, 200);
	ani_idle_right->AddFrame(sprite3, 400); //------------
	ani_idle_right->AddFrame(sprite7, 50);
	ani_idle_right->AddFrame(sprite8, 100);
	ani_idle_right->AddFrame(sprite9, 100);
	ani_idle_right->AddFrame(sprite10, 200);
	ani_idle_right->AddFrame(sprite11, 200);
	ani_idle_right->AddFrame(sprite12, 200);
	ani_idle_right->AddFrame(sprite13, 100);
	ani_idle_right->AddFrame(sprite14, 100);
	ani_idle_right->AddFrame(sprite15, 100);
	ani_idle_right->AddFrame(sprite16, 100);
	ani_idle_right->AddFrame(sprite17, 100);
	ani_idle_right->AddFrame(sprite18, 100);
	ani_idle_right->AddFrame(sprite19, 100);
	ani_idle_right->AddFrame(sprite20, 100);
	ani_idle_right->AddFrame(sprite21, 300);
	ani_idle_right->AddFrame(sprite12, 200);
	ani_idle_right->AddFrame(sprite13, 100);
	ani_idle_right->AddFrame(sprite14, 100);
	ani_idle_right->AddFrame(sprite15, 100);
	ani_idle_right->AddFrame(sprite16, 100);
	ani_idle_right->AddFrame(sprite17, 100);
	ani_idle_right->AddFrame(sprite18, 100);
	ani_idle_right->AddFrame(sprite19, 100);
	ani_idle_right->AddFrame(sprite20, 100);
	ani_idle_right->AddFrame(sprite21, 400);//-----------
	ani_idle_right->AddFrame(sprite22, 200);
	ani_idle_right->AddFrame(sprite23, 400);
	ani_idle_right->AddFrame(sprite24, 100);
	ani_idle_right->AddFrame(sprite25, 100);
	ani_idle_right->AddFrame(sprite26, 100);
	ani_idle_right->AddFrame(sprite27, 100);
	ani_idle_right->AddFrame(sprite28, 200);
	ani_idle_right->AddFrame(sprite29, 200);
	ani_idle_right->AddFrame(sprite30, 200);
	ani_idle_right->AddFrame(sprite31, 200);
	ani_idle_right->AddFrame(sprite32, 100);
	ani_idle_right->AddFrame(sprite33, 100);
	ani_idle_right->AddFrame(sprite34, 100);
	ani_idle_right->AddFrame(sprite35, 100);
	ani_idle_right->AddFrame(sprite36, 100);
	ani_idle_right->AddFrame(sprite37, 200);
	ani_idle_right->AddFrame(sprite38, 300);//---------
	ani_idle_right->AddFrame(sprite12, 200);
	ani_idle_right->AddFrame(sprite13, 100);
	ani_idle_right->AddFrame(sprite14, 100);
	ani_idle_right->AddFrame(sprite15, 100);
	ani_idle_right->AddFrame(sprite16, 100);
	ani_idle_right->AddFrame(sprite17, 100);
	ani_idle_right->AddFrame(sprite18, 100);
	ani_idle_right->AddFrame(sprite19, 100);
	ani_idle_right->AddFrame(sprite20, 100);
	ani_idle_right->AddFrame(sprite21, 400);//-------------
	ani_idle_right->AddFrame(sprite22, 200);
	ani_idle_right->AddFrame(sprite23, 400);
	ani_idle_right->AddFrame(sprite24, 100);
	ani_idle_right->AddFrame(sprite25, 100);
	ani_idle_right->AddFrame(sprite26, 100);
	ani_idle_right->AddFrame(sprite27, 100);
	ani_idle_right->AddFrame(sprite28, 200);
	ani_idle_right->AddFrame(sprite29, 200);
	ani_idle_right->AddFrame(sprite30, 200);
	ani_idle_right->AddFrame(sprite31, 200);
	ani_idle_right->AddFrame(sprite32, 100);
	ani_idle_right->AddFrame(sprite33, 100);
	ani_idle_right->AddFrame(sprite34, 100);
	ani_idle_right->AddFrame(sprite35, 100);
	ani_idle_right->AddFrame(sprite36, 100);
	ani_idle_right->AddFrame(sprite37, 200);
	ani_idle_right->AddFrame(sprite38, 300);
	ani_idle_right->SetRepeat(true);

	Animation* ani_idle_left = new Animation();
	ani_idle_left->AddFrame(sprite100, 600);
	ani_idle_left->AddFrame(sprite101, 200);
	ani_idle_left->AddFrame(sprite102, 200);
	ani_idle_left->AddFrame(sprite103, 400);
	ani_idle_left->AddFrame(sprite104, 100);
	ani_idle_left->AddFrame(sprite105, 200);
	ani_idle_left->AddFrame(sprite106, 400);
	ani_idle_left->AddFrame(sprite104, 100);
	ani_idle_left->AddFrame(sprite102, 200);
	ani_idle_left->AddFrame(sprite103, 300);
	ani_idle_left->AddFrame(sprite104, 100);
	ani_idle_left->AddFrame(sprite105, 300);
	ani_idle_left->AddFrame(sprite106, 300);
	ani_idle_left->AddFrame(sprite104, 100);
	ani_idle_left->AddFrame(sprite102, 200);
	ani_idle_left->AddFrame(sprite103, 400);//---------------
	ani_idle_left->AddFrame(sprite107, 50);
	ani_idle_left->AddFrame(sprite108, 100);
	ani_idle_left->AddFrame(sprite109, 100);
	ani_idle_left->AddFrame(sprite110, 200);
	ani_idle_left->AddFrame(sprite111, 200);
	ani_idle_left->AddFrame(sprite112, 200);
	ani_idle_left->AddFrame(sprite113, 100);
	ani_idle_left->AddFrame(sprite114, 100);
	ani_idle_left->AddFrame(sprite115, 100);
	ani_idle_left->AddFrame(sprite116, 100);
	ani_idle_left->AddFrame(sprite117, 100);
	ani_idle_left->AddFrame(sprite118, 100);
	ani_idle_left->AddFrame(sprite119, 100);
	ani_idle_left->AddFrame(sprite120, 100);
	ani_idle_left->AddFrame(sprite121, 300);//-----------------
	ani_idle_left->AddFrame(sprite112, 200);
	ani_idle_left->AddFrame(sprite113, 100);
	ani_idle_left->AddFrame(sprite114, 100);
	ani_idle_left->AddFrame(sprite115, 100);
	ani_idle_left->AddFrame(sprite116, 100);
	ani_idle_left->AddFrame(sprite117, 100);
	ani_idle_left->AddFrame(sprite118, 100);
	ani_idle_left->AddFrame(sprite119, 100);
	ani_idle_left->AddFrame(sprite120, 100);
	ani_idle_left->AddFrame(sprite121, 400);//---------------------
	ani_idle_left->AddFrame(sprite122, 200);
	ani_idle_left->AddFrame(sprite123, 400);
	ani_idle_left->AddFrame(sprite124, 100);
	ani_idle_left->AddFrame(sprite125, 100);
	ani_idle_left->AddFrame(sprite126, 100);
	ani_idle_left->AddFrame(sprite127, 100);
	ani_idle_left->AddFrame(sprite128, 200);
	ani_idle_left->AddFrame(sprite129, 200);
	ani_idle_left->AddFrame(sprite130, 200);
	ani_idle_left->AddFrame(sprite131, 200);
	ani_idle_left->AddFrame(sprite132, 100);
	ani_idle_left->AddFrame(sprite133, 100);
	ani_idle_left->AddFrame(sprite134, 100);
	ani_idle_left->AddFrame(sprite135, 100);
	ani_idle_left->AddFrame(sprite136, 100);
	ani_idle_left->AddFrame(sprite137, 200);
	ani_idle_left->AddFrame(sprite138, 300);//--------------------
	ani_idle_left->AddFrame(sprite112, 200);
	ani_idle_left->AddFrame(sprite113, 100);
	ani_idle_left->AddFrame(sprite114, 100);
	ani_idle_left->AddFrame(sprite115, 100);
	ani_idle_left->AddFrame(sprite116, 100);
	ani_idle_left->AddFrame(sprite117, 100);
	ani_idle_left->AddFrame(sprite118, 100);
	ani_idle_left->AddFrame(sprite119, 100);
	ani_idle_left->AddFrame(sprite120, 100);
	ani_idle_left->AddFrame(sprite121, 400);//-------------------
	ani_idle_left->AddFrame(sprite122, 200);
	ani_idle_left->AddFrame(sprite123, 400);
	ani_idle_left->AddFrame(sprite124, 100);
	ani_idle_left->AddFrame(sprite125, 100);
	ani_idle_left->AddFrame(sprite126, 100);
	ani_idle_left->AddFrame(sprite127, 100);
	ani_idle_left->AddFrame(sprite128, 200);
	ani_idle_left->AddFrame(sprite129, 200);
	ani_idle_left->AddFrame(sprite130, 200);
	ani_idle_left->AddFrame(sprite131, 200);
	ani_idle_left->AddFrame(sprite132, 100);
	ani_idle_left->AddFrame(sprite133, 100);
	ani_idle_left->AddFrame(sprite134, 100);
	ani_idle_left->AddFrame(sprite135, 100);
	ani_idle_left->AddFrame(sprite136, 100);
	ani_idle_left->AddFrame(sprite137, 200);
	ani_idle_left->AddFrame(sprite138, 300);
	ani_idle_left->SetRepeat(true);

	Animation * ani_idlethrow_right = new Animation();
	ani_idlethrow_right->AddFrame(sprite139, 100);
	ani_idlethrow_right->AddFrame(sprite140, 100);
	ani_idlethrow_right->AddFrame(sprite141, 100);
	ani_idlethrow_right->AddFrame(sprite142, 10);
	ani_idlethrow_right->AddFrame(sprite143, 100);
	ani_idlethrow_right->AddFrame(sprite144, 100);

	Animation * ani_idlethrow_left = new Animation();
	ani_idlethrow_left->AddFrame(sprite145, 100);
	ani_idlethrow_left->AddFrame(sprite146, 100);
	ani_idlethrow_left->AddFrame(sprite147, 100);
	ani_idlethrow_left->AddFrame(sprite148, 10);
	ani_idlethrow_left->AddFrame(sprite149, 100);
	ani_idlethrow_left->AddFrame(sprite150, 100);

	Animation * ani_idleattack_right = new Animation();
	ani_idleattack_right->AddFrame(sprite151, 50);
	ani_idleattack_right->AddFrame(sprite152, 50);
	ani_idleattack_right->AddFrame(sprite153, 100);
	ani_idleattack_right->AddFrame(sprite154, 100);
	ani_idleattack_right->AddFrame(sprite155, 100);

	Animation * ani_idleattack_left = new Animation();
	ani_idleattack_left->AddFrame(sprite156, 50);
	ani_idleattack_left->AddFrame(sprite157, 50);
	ani_idleattack_left->AddFrame(sprite158, 100);
	ani_idleattack_left->AddFrame(sprite159, 100);
	ani_idleattack_left->AddFrame(sprite160, 100);


	// ani jump

	Animation* ani_jumpup_right = new Animation();
	ani_jumpup_right->AddFrame(sprite69, 100);
	ani_jumpup_right->AddFrame(sprite70, 200);
	ani_jumpup_right->AddFrame(sprite71, 200);
	ani_jumpup_right->AddFrame(sprite72, 100);
	ani_jumpup_right->AddFrame(sprite73, 200);
	ani_jumpup_right->AddFrame(sprite74, 100);
	ani_jumpup_right->AddFrame(sprite85, 100);
	//ani_jumpup_right->SetRepeat(6, 6);

	Animation* ani_jumpup_left = new Animation();
	ani_jumpup_left->AddFrame(sprite184, 100);
	ani_jumpup_left->AddFrame(sprite185, 200);
	ani_jumpup_left->AddFrame(sprite186, 200);
	ani_jumpup_left->AddFrame(sprite187, 100);
	ani_jumpup_left->AddFrame(sprite188, 200);
	ani_jumpup_left->AddFrame(sprite189, 100);
	ani_jumpup_left->AddFrame(sprite200, 100);
	//ani_jumpup_left->SetRepeat(6, 6);



	Animation* ani_jump_right = new Animation();
	ani_jump_right->AddFrame(sprite78, 100);
	ani_jump_right->AddFrame(sprite79, 100);
	ani_jump_right->AddFrame(sprite80, 200);
	ani_jump_right->AddFrame(sprite81, 100);
	ani_jump_right->AddFrame(sprite82, 100);
	ani_jump_right->AddFrame(sprite83, 100);
	ani_jump_right->AddFrame(sprite84, 100);
	//ani_jump_right->SetRepeat(6, 6);

	Animation* ani_jump_left = new Animation();
	ani_jump_left->AddFrame(sprite193, 100);
	ani_jump_left->AddFrame(sprite194, 100);
	ani_jump_left->AddFrame(sprite195, 200);
	ani_jump_left->AddFrame(sprite196, 100);
	ani_jump_left->AddFrame(sprite197, 100);
	ani_jump_left->AddFrame(sprite198, 100);
	ani_jump_left->AddFrame(sprite199, 100);
	//ani_jump_left->SetRepeat(6, 6);

	Animation* ani_jumpupthrow_right = new Animation();
	//ani_jumpupthrow_right->AddFrame(sprite202, 100);
	ani_jumpupthrow_right->AddFrame(sprite203, 50);
	ani_jumpupthrow_right->AddFrame(sprite204, 50);
	ani_jumpupthrow_right->AddFrame(sprite205, 50);
	ani_jumpupthrow_right->AddFrame(sprite206, 50);

	Animation* ani_jumpupthrow_left = new Animation();
	//ani_jumpupthrow_left->AddFrame(sprite207, 100);
	ani_jumpupthrow_left->AddFrame(sprite208, 50);
	ani_jumpupthrow_left->AddFrame(sprite209, 50);
	ani_jumpupthrow_left->AddFrame(sprite210, 50);
	ani_jumpupthrow_left->AddFrame(sprite211, 50);

	Animation* ani_jumpupattack_right = new Animation();
	ani_jumpupattack_right->AddFrame(sprite212, 50);
	ani_jumpupattack_right->AddFrame(sprite213, 50);
	ani_jumpupattack_right->AddFrame(sprite214, 50);
	ani_jumpupattack_right->AddFrame(sprite215, 50);
	ani_jumpupattack_right->AddFrame(sprite216, 50);
	ani_jumpupattack_right->AddFrame(sprite217, 50);

	Animation* ani_jumpupattack_left = new Animation();
	ani_jumpupattack_left->AddFrame(sprite218, 50);
	ani_jumpupattack_left->AddFrame(sprite219, 50);
	ani_jumpupattack_left->AddFrame(sprite220, 50);
	ani_jumpupattack_left->AddFrame(sprite221, 50);
	ani_jumpupattack_left->AddFrame(sprite222, 50);
	ani_jumpupattack_left->AddFrame(sprite223, 50);

	Animation* ani_jumpattack_right = new Animation();
	ani_jumpattack_right->AddFrame(sprite400, 50);
	ani_jumpattack_right->AddFrame(sprite401, 50);
	ani_jumpattack_right->AddFrame(sprite402, 50);
	ani_jumpattack_right->AddFrame(sprite403, 50);
	ani_jumpattack_right->AddFrame(sprite404, 50);
	ani_jumpattack_right->AddFrame(sprite405, 50);
	ani_jumpattack_right->AddFrame(sprite406, 50);
	ani_jumpattack_right->AddFrame(sprite407, 50);

	Animation* ani_jumpattack_left = new Animation();
	ani_jumpattack_left->AddFrame(sprite408, 50);
	ani_jumpattack_left->AddFrame(sprite409, 50);
	ani_jumpattack_left->AddFrame(sprite410, 50);
	ani_jumpattack_left->AddFrame(sprite411, 50);
	ani_jumpattack_left->AddFrame(sprite412, 50);
	ani_jumpattack_left->AddFrame(sprite413, 50);
	ani_jumpattack_left->AddFrame(sprite414, 50);
	ani_jumpattack_left->AddFrame(sprite415, 50);

	// ani sit

	Animation* ani_sit_right = new Animation();
	ani_sit_right->AddFrame(sprite52, 50);
	ani_sit_right->AddFrame(sprite53, 50);
	ani_sit_right->AddFrame(sprite54, 100);
	ani_sit_right->AddFrame(sprite55, 200);
	ani_sit_right->SetRepeat(3, 3);

	Animation* ani_sit_left = new Animation();
	ani_sit_left->AddFrame(sprite167, 50);
	ani_sit_left->AddFrame(sprite168, 50);
	ani_sit_left->AddFrame(sprite169, 100);
	ani_sit_left->AddFrame(sprite170, 200);
	ani_sit_left->SetRepeat(3, 3);

	Animation* ani_sitthrow_right = new Animation();
	ani_sitthrow_right->AddFrame(sprite56, 100);
	ani_sitthrow_right->AddFrame(sprite57, 100);
	ani_sitthrow_right->AddFrame(sprite58, 100);
	ani_sitthrow_right->AddFrame(sprite59, 100);
	ani_sitthrow_right->AddFrame(sprite60, 100);

	Animation* ani_sitthrow_left = new Animation();
	ani_sitthrow_left->AddFrame(sprite171, 100);
	ani_sitthrow_left->AddFrame(sprite172, 100);
	ani_sitthrow_left->AddFrame(sprite173, 100);
	ani_sitthrow_left->AddFrame(sprite174, 100);
	ani_sitthrow_left->AddFrame(sprite175, 100);

	Animation* ani_sitattack_right = new Animation();
	ani_sitattack_right->AddFrame(sprite61, 50);
	ani_sitattack_right->AddFrame(sprite62, 50);
	ani_sitattack_right->AddFrame(sprite63, 50);
	ani_sitattack_right->AddFrame(sprite64, 50);
	ani_sitattack_right->AddFrame(sprite65, 50);
	ani_sitattack_right->AddFrame(sprite66, 50);
	ani_sitattack_right->AddFrame(sprite67, 50);

	Animation* ani_sitattack_left = new Animation();
	ani_sitattack_left->AddFrame(sprite176, 50);
	ani_sitattack_left->AddFrame(sprite177, 50);
	ani_sitattack_left->AddFrame(sprite178, 50);
	ani_sitattack_left->AddFrame(sprite179, 50);
	ani_sitattack_left->AddFrame(sprite180, 50);
	ani_sitattack_left->AddFrame(sprite181, 50);
	ani_sitattack_left->AddFrame(sprite182, 50);


	// ani walk 

	Animation* ani_walk_right = new Animation();
	ani_walk_right->AddFrame(sprite39, 100);
	ani_walk_right->AddFrame(sprite40, 100);
	ani_walk_right->AddFrame(sprite41, 100);
	ani_walk_right->AddFrame(sprite42, 100);
	ani_walk_right->AddFrame(sprite43, 100);
	ani_walk_right->AddFrame(sprite44, 100);
	ani_walk_right->AddFrame(sprite45, 100);
	ani_walk_right->AddFrame(sprite46, 100);
	ani_walk_right->AddFrame(sprite47, 100);
	ani_walk_right->AddFrame(sprite48, 100);
	ani_walk_right->AddFrame(sprite49, 100);
	ani_walk_right->AddFrame(sprite50, 100);
	ani_walk_right->AddFrame(sprite51, 100);
	ani_walk_right->SetRepeat(true);

	Animation* ani_walk_left = new Animation();
	ani_walk_left->AddFrame(sprite87, 100);
	ani_walk_left->AddFrame(sprite88, 100);
	ani_walk_left->AddFrame(sprite89, 100);
	ani_walk_left->AddFrame(sprite90, 100);
	ani_walk_left->AddFrame(sprite91, 100);
	ani_walk_left->AddFrame(sprite92, 100);
	ani_walk_left->AddFrame(sprite93, 100);
	ani_walk_left->AddFrame(sprite94, 100);
	ani_walk_left->AddFrame(sprite95, 100);
	ani_walk_left->AddFrame(sprite96, 100);
	ani_walk_left->AddFrame(sprite97, 100);
	ani_walk_left->AddFrame(sprite98, 100);
	ani_walk_left->AddFrame(sprite99, 100);
	ani_walk_left->SetRepeat(true);

	Animation* ani_walkattack_right = new Animation();
	ani_walkattack_right->AddFrame(sprite416, 50);
	ani_walkattack_right->AddFrame(sprite417, 50);
	ani_walkattack_right->AddFrame(sprite418, 50);
	ani_walkattack_right->AddFrame(sprite419, 50);
	ani_walkattack_right->AddFrame(sprite420, 50);
	ani_walkattack_right->AddFrame(sprite421, 50);

	Animation* ani_walkattack_left = new Animation();
	ani_walkattack_left->AddFrame(sprite422, 50);
	ani_walkattack_left->AddFrame(sprite423, 50);
	ani_walkattack_left->AddFrame(sprite424, 50);
	ani_walkattack_left->AddFrame(sprite425, 50);
	ani_walkattack_left->AddFrame(sprite426, 50);
	ani_walkattack_left->AddFrame(sprite427, 50);


	Animation* ani_walkthrow_right = new Animation();
	ani_walkthrow_right->AddFrame(sprite428, 100);
	ani_walkthrow_right->AddFrame(sprite429, 100);
	ani_walkthrow_right->AddFrame(sprite430, 100);
	ani_walkthrow_right->AddFrame(sprite431, 100);
	ani_walkthrow_right->AddFrame(sprite432, 100);
	ani_walkthrow_right->AddFrame(sprite433, 100);

	Animation* ani_walkthrow_left = new Animation();
	ani_walkthrow_left->AddFrame(sprite434, 100);
	ani_walkthrow_left->AddFrame(sprite435, 100);
	ani_walkthrow_left->AddFrame(sprite436, 100);
	ani_walkthrow_left->AddFrame(sprite437, 100);
	ani_walkthrow_left->AddFrame(sprite438, 100);
	ani_walkthrow_left->AddFrame(sprite439, 100);


	// ani climb up
	Animation* ani_climb_idle = new Animation();
	ani_climb_idle->AddFrame(sprite224, 30);
	ani_climb_idle->SetRepeat(true);

	Animation* ani_climb_up = new Animation();

	ani_climb_up->AddFrame(sprite226, 100);
	ani_climb_up->AddFrame(sprite227, 100);
	ani_climb_up->AddFrame(sprite228, 100);
	ani_climb_up->AddFrame(sprite229, 100);
	ani_climb_up->AddFrame(sprite230, 100);
	ani_climb_up->AddFrame(sprite231, 100);
	ani_climb_up->AddFrame(sprite232, 100);
	ani_climb_up->AddFrame(sprite233, 100);
	ani_climb_up->AddFrame(sprite224, 100);//0
	ani_climb_up->AddFrame(sprite225, 100);//1
	ani_climb_up->SetRepeat(true);

	Animation* ani_climb_down = new Animation();
	ani_climb_down->AddFrame(sprite231, 100);
	ani_climb_down->AddFrame(sprite230, 100);
	ani_climb_down->AddFrame(sprite229, 100);
	ani_climb_down->AddFrame(sprite228, 100);
	ani_climb_down->AddFrame(sprite227, 100);
	ani_climb_down->AddFrame(sprite226, 100);
	ani_climb_down->AddFrame(sprite225, 100);
	ani_climb_down->AddFrame(sprite224, 100);
	ani_climb_down->AddFrame(sprite233, 100);//0
	ani_climb_down->AddFrame(sprite232, 100);//1
	ani_climb_down->SetRepeat(true);

	Animation* ani_climb_jump = new Animation();
	ani_climb_jump->AddFrame(sprite244, 30);
	ani_climb_jump->AddFrame(sprite245, 30);
	ani_climb_jump->AddFrame(sprite246, 30);
	ani_climb_jump->AddFrame(sprite247, 30);
	ani_climb_jump->AddFrame(sprite248, 30);
	ani_climb_jump->AddFrame(sprite249, 30);
	ani_climb_jump->AddFrame(sprite250, 80);
	ani_climb_jump->AddFrame(sprite251, 80);
	ani_climb_jump->AddFrame(sprite252, 80);

	//Ani drop down
	Animation* ani_dropdown = new Animation();
	ani_dropdown->AddFrame(sprite244, 50);
	ani_dropdown->AddFrame(sprite245, 50);
	ani_dropdown->AddFrame(sprite246, 50);
	ani_dropdown->AddFrame(sprite247, 50);
	ani_dropdown->AddFrame(sprite248, 50);
	ani_dropdown->AddFrame(sprite249, 50);
	ani_dropdown->AddFrame(sprite250, 50);
	ani_dropdown->AddFrame(sprite250, 50);
	ani_dropdown->AddFrame(sprite250, 50);
	ani_dropdown->SetRepeat(8, 8);

	//Ani fall
	Animation* ani_fall_right = new Animation();
	ani_fall_right->AddFrame(sprite262, 100);
	ani_fall_right->AddFrame(sprite263, 100);
	ani_fall_right->AddFrame(sprite264, 100);
	ani_fall_right->AddFrame(sprite265, 100);
	ani_fall_right->AddFrame(sprite266, 100);
	ani_fall_right->AddFrame(sprite267, 100);
	ani_fall_right->AddFrame(sprite268, 100);
	ani_fall_right->AddFrame(sprite269, 100);
	ani_fall_right->AddFrame(sprite270, 100);
	ani_fall_right->AddFrame(sprite271, 100);
	ani_fall_right->AddFrame(sprite272, 100);
	ani_fall_right->AddFrame(sprite273, 100);

	Animation* ani_fall_left = new Animation();
	ani_fall_left->AddFrame(sprite274, 100);
	ani_fall_left->AddFrame(sprite275, 100);
	ani_fall_left->AddFrame(sprite276, 100);
	ani_fall_left->AddFrame(sprite277, 100);
	ani_fall_left->AddFrame(sprite278, 100);
	ani_fall_left->AddFrame(sprite279, 100);
	ani_fall_left->AddFrame(sprite280, 100);
	ani_fall_left->AddFrame(sprite281, 100);
	ani_fall_left->AddFrame(sprite282, 100);
	ani_fall_left->AddFrame(sprite283, 100);
	ani_fall_left->AddFrame(sprite284, 100);
	ani_fall_left->AddFrame(sprite285, 100);


	//Ani stop
	Animation* ani_stop_right = new Animation();
	ani_stop_right->AddFrame(sprite286, 100);
	ani_stop_right->AddFrame(sprite287, 100);
	ani_stop_right->AddFrame(sprite288, 100);
	ani_stop_right->AddFrame(sprite289, 100);
	ani_stop_right->AddFrame(sprite290, 100);
	ani_stop_right->AddFrame(sprite291, 100);
	ani_stop_right->AddFrame(sprite292, 100);
	ani_stop_right->AddFrame(sprite293, 100);
	ani_stop_right->AddFrame(sprite294, 100);

	Animation* ani_stop_left = new Animation();
	ani_stop_left->AddFrame(sprite295, 100);
	ani_stop_left->AddFrame(sprite296, 100);
	ani_stop_left->AddFrame(sprite297, 100);
	ani_stop_left->AddFrame(sprite298, 100);
	ani_stop_left->AddFrame(sprite299, 100);
	ani_stop_left->AddFrame(sprite300, 100);
	ani_stop_left->AddFrame(sprite301, 100);
	ani_stop_left->AddFrame(sprite302, 100);
	ani_stop_left->AddFrame(sprite303, 100);


	//Ani hurt
	Animation* ani_hurt_right = new Animation();
	ani_hurt_right->AddFrame(sprite304, 100);
	ani_hurt_right->AddFrame(sprite305, 100);
	ani_hurt_right->AddFrame(sprite306, 100);
	ani_hurt_right->AddFrame(sprite307, 100);
	ani_hurt_right->AddFrame(sprite308, 100);
	ani_hurt_right->AddFrame(sprite309, 100);

	Animation* ani_hurt_left = new Animation();
	ani_hurt_left->AddFrame(sprite310, 100);
	ani_hurt_left->AddFrame(sprite311, 100);
	ani_hurt_left->AddFrame(sprite312, 100);
	ani_hurt_left->AddFrame(sprite313, 100);
	ani_hurt_left->AddFrame(sprite314, 100);
	ani_hurt_left->AddFrame(sprite315, 100);


	//Ani die
	Animation* ani_die_right = new Animation();
	ani_die_right->AddFrame(sprite316, 100);
	ani_die_right->AddFrame(sprite317, 100);
	ani_die_right->AddFrame(sprite318, 100);
	ani_die_right->AddFrame(sprite319, 100);
	ani_die_right->AddFrame(sprite320, 100);
	ani_die_right->AddFrame(sprite321, 100);
	ani_die_right->AddFrame(sprite322, 100);
	ani_die_right->AddFrame(sprite323, 100);
	ani_die_right->AddFrame(sprite324, 100);
	ani_die_right->AddFrame(sprite325, 100);
	ani_die_right->AddFrame(sprite326, 100);
	ani_die_right->AddFrame(sprite327, 100);
	ani_die_right->AddFrame(sprite328, 100);
	ani_die_right->AddFrame(sprite329, 100);
	ani_die_right->AddFrame(sprite330, 100);
	ani_die_right->AddFrame(sprite331, 100);
	ani_die_right->AddFrame(sprite332, 100);
	ani_die_right->AddFrame(sprite333, 100);
	ani_die_right->AddFrame(sprite334, 100);
	ani_die_right->AddFrame(sprite335, 100);
	ani_die_right->AddFrame(sprite336, 100);
	ani_die_right->AddFrame(sprite337, 100);
	ani_die_right->AddFrame(sprite338, 100);
	ani_die_right->AddFrame(sprite339, 100);
	ani_die_right->AddFrame(sprite340, 100);
	ani_die_right->AddFrame(sprite341, 100);
	ani_die_right->AddFrame(sprite342, 100);
	ani_die_right->AddFrame(sprite343, 100);

	Animation* ani_die_left = new Animation();
	ani_die_left->AddFrame(sprite344, 100);
	ani_die_left->AddFrame(sprite345, 100);
	ani_die_left->AddFrame(sprite346, 100);
	ani_die_left->AddFrame(sprite347, 100);
	ani_die_left->AddFrame(sprite348, 100);
	ani_die_left->AddFrame(sprite349, 100);
	ani_die_left->AddFrame(sprite350, 100);
	ani_die_left->AddFrame(sprite351, 100);
	ani_die_left->AddFrame(sprite352, 100);
	ani_die_left->AddFrame(sprite353, 100);
	ani_die_left->AddFrame(sprite354, 100);
	ani_die_left->AddFrame(sprite355, 100);
	ani_die_left->AddFrame(sprite356, 100);
	ani_die_left->AddFrame(sprite357, 100);
	ani_die_left->AddFrame(sprite358, 100);
	ani_die_left->AddFrame(sprite359, 100);
	ani_die_left->AddFrame(sprite360, 100);
	ani_die_left->AddFrame(sprite361, 100);
	ani_die_left->AddFrame(sprite362, 100);
	ani_die_left->AddFrame(sprite363, 100);
	ani_die_left->AddFrame(sprite364, 100);
	ani_die_left->AddFrame(sprite365, 100);
	ani_die_left->AddFrame(sprite366, 100);
	ani_die_left->AddFrame(sprite367, 100);
	ani_die_left->AddFrame(sprite368, 100);
	ani_die_left->AddFrame(sprite369, 100);
	ani_die_left->AddFrame(sprite370, 100);
	ani_die_left->AddFrame(sprite371, 100);


	//Ani revival
	Animation* ani_revival_right = new Animation();
	ani_revival_right->AddFrame(sprite372, 100);
	ani_revival_right->AddFrame(sprite373, 100);
	ani_revival_right->AddFrame(sprite374, 100);
	ani_revival_right->AddFrame(sprite375, 100);
	ani_revival_right->AddFrame(sprite376, 100);
	ani_revival_right->AddFrame(sprite377, 100);
	ani_revival_right->AddFrame(sprite378, 100);
	ani_revival_right->AddFrame(sprite379, 100);
	ani_revival_right->AddFrame(sprite380, 100);
	ani_revival_right->AddFrame(sprite381, 100);
	ani_revival_right->AddFrame(sprite382, 100);
	ani_revival_right->AddFrame(sprite383, 100);
	ani_revival_right->AddFrame(sprite384, 100);
	ani_revival_right->AddFrame(sprite385, 100);

	Animation* ani_revival_left = new Animation();
	ani_revival_left->AddFrame(sprite386, 100);
	ani_revival_left->AddFrame(sprite387, 100);
	ani_revival_left->AddFrame(sprite388, 100);
	ani_revival_left->AddFrame(sprite389, 100);
	ani_revival_left->AddFrame(sprite390, 100);
	ani_revival_left->AddFrame(sprite391, 100);
	ani_revival_left->AddFrame(sprite392, 100);
	ani_revival_left->AddFrame(sprite393, 100);
	ani_revival_left->AddFrame(sprite394, 100);
	ani_revival_left->AddFrame(sprite395, 100);
	ani_revival_left->AddFrame(sprite396, 100);
	ani_revival_left->AddFrame(sprite397, 100);
	ani_revival_left->AddFrame(sprite398, 100);
	ani_revival_left->AddFrame(sprite399, 100);

	// ani look up
	Animation* ani_up_right = new Animation();
	ani_up_right->AddFrame(sprite161, 100);
	ani_up_right->AddFrame(sprite162, 100);
	ani_up_right->AddFrame(sprite163, 100);
	ani_up_right->SetRepeat(2, 2);

	Animation* ani_up_left = new Animation();
	ani_up_left->AddFrame(sprite164, 100);
	ani_up_left->AddFrame(sprite165, 100);
	ani_up_left->AddFrame(sprite166, 100);
	ani_up_left->SetRepeat(2, 2);
	
	GetAnimations()->AddAnimation(ani_idle_right, Aladin::ANIMATIONS::idleright);
	GetAnimations()->AddAnimation(ani_idle_left, Aladin::ANIMATIONS::idleleft);
	GetAnimations()->AddAnimation(ani_idlethrow_right, Aladin::ANIMATIONS::idlethrowright);
	GetAnimations()->AddAnimation(ani_idlethrow_left, Aladin::ANIMATIONS::idlethrowleft);
	GetAnimations()->AddAnimation(ani_idleattack_right, Aladin::ANIMATIONS::idleattackright);
	GetAnimations()->AddAnimation(ani_idleattack_left, Aladin::ANIMATIONS::idleattackleft);

	GetAnimations()->AddAnimation(ani_jumpup_right, Aladin::ANIMATIONS::jumpupright);
	GetAnimations()->AddAnimation(ani_jumpup_left, Aladin::ANIMATIONS::jumpupleft);
	GetAnimations()->AddAnimation(ani_jump_right, Aladin::ANIMATIONS::jumpright);
	GetAnimations()->AddAnimation(ani_jump_left, Aladin::ANIMATIONS::jumpleft);
	GetAnimations()->AddAnimation(ani_jumpupthrow_right, Aladin::ANIMATIONS::jumpupthrowright);
	GetAnimations()->AddAnimation(ani_jumpupthrow_left, Aladin::ANIMATIONS::jumpupthrowleft);
	GetAnimations()->AddAnimation(ani_jumpupattack_right, Aladin::ANIMATIONS::jumpupattackright);
	GetAnimations()->AddAnimation(ani_jumpupattack_left, Aladin::ANIMATIONS::jumpupattackleft);
	GetAnimations()->AddAnimation(ani_jumpattack_right, Aladin::ANIMATIONS::jumpattackright);
	GetAnimations()->AddAnimation(ani_jumpattack_left, Aladin::ANIMATIONS::jumpattackleft);

	GetAnimations()->AddAnimation(ani_sit_right, Aladin::ANIMATIONS::sitright);
	GetAnimations()->AddAnimation(ani_sit_left, Aladin::ANIMATIONS::sitleft);
	GetAnimations()->AddAnimation(ani_sitthrow_right, Aladin::ANIMATIONS::sitthrowright);
	GetAnimations()->AddAnimation(ani_sitthrow_left, Aladin::ANIMATIONS::sitthrowleft);
	GetAnimations()->AddAnimation(ani_sitattack_right, Aladin::ANIMATIONS::sitattackright);
	GetAnimations()->AddAnimation(ani_sitattack_left, Aladin::ANIMATIONS::sitattackleft);

	GetAnimations()->AddAnimation(ani_walk_right, Aladin::ANIMATIONS::walkright);
	GetAnimations()->AddAnimation(ani_walk_left, Aladin::ANIMATIONS::walkleft);
	GetAnimations()->AddAnimation(ani_walkattack_right, Aladin::ANIMATIONS::walkattackright);
	GetAnimations()->AddAnimation(ani_walkattack_left, Aladin::ANIMATIONS::walkattackleft);
	GetAnimations()->AddAnimation(ani_walkthrow_right, Aladin::ANIMATIONS::walkthrowright);
	GetAnimations()->AddAnimation(ani_walkthrow_left, Aladin::ANIMATIONS::walkthrowleft);

	GetAnimations()->AddAnimation(ani_climb_up, Aladin::ANIMATIONS::climbup);
	GetAnimations()->AddAnimation(ani_climb_down, Aladin::ANIMATIONS::climbdown);
	GetAnimations()->AddAnimation(ani_climb_jump, Aladin::ANIMATIONS::climbjump);
	GetAnimations()->AddAnimation(ani_dropdown, Aladin::ANIMATIONS::climbdropdown);

	GetAnimations()->AddAnimation(ani_fall_right, Aladin::ANIMATIONS::fallright);
	GetAnimations()->AddAnimation(ani_fall_left, Aladin::ANIMATIONS::fallleft);

	GetAnimations()->AddAnimation(ani_stop_right, Aladin::ANIMATIONS::stopright);
	GetAnimations()->AddAnimation(ani_stop_left, Aladin::ANIMATIONS::stopleft);

	GetAnimations()->AddAnimation(ani_hurt_right, Aladin::ANIMATIONS::hurtright);
	GetAnimations()->AddAnimation(ani_hurt_left, Aladin::ANIMATIONS::hurtleft);

	GetAnimations()->AddAnimation(ani_die_right, Aladin::ANIMATIONS::dieright);
	GetAnimations()->AddAnimation(ani_die_left, Aladin::ANIMATIONS::dieleft);

	GetAnimations()->AddAnimation(ani_revival_right, Aladin::ANIMATIONS::revivalright);
	GetAnimations()->AddAnimation(ani_revival_left, Aladin::ANIMATIONS::revivalleft);

	GetAnimations()->AddAnimation(ani_up_right, Aladin::ANIMATIONS::upright);
	GetAnimations()->AddAnimation(ani_up_left, Aladin::ANIMATIONS::upleft);

	GetAnimations()->AddAnimation(ani_climb_idle, Aladin::ANIMATIONS::idleclimb);
	this->GetAnimations()->Start(0);
	
	for (int i = 0; i < ALADDIN_APPLE_COUNT_ONE_TIME; i++) {
		apples[i]->Init(d3dd9);
		apples[i]->SetExist(false);
	}
}

void Aladin::Render(LPCAMERA camera, LPD3DXSPRITE spriteHandler)
{
	if (this->exist==true) {
		if (animations != nullptr) {
			animations->Render(*BottomPosition(), camera, spriteHandler, (statushurt ? ALADDIN_OPACITY : 1.0f));
		}

		for each (LPAPPLE apple in apples)
		{
			if (apple->GetExist() == true)
				apple->Render(camera, spriteHandler);
		}
	}
}

void Aladin::Update(DWORD dt, vector<LPOBJECT>* objs)
{
	//DebugOut(L"freID: %d\n", this->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID());

	if (this->exist == true) {
		vector<LPCOEVENT> coEvents;
		vector<LPCOEVENT> coEventsResult;

		coEvents.clear();
		Colision* a = new  Colision(this);
		a->CalcPotentialCollisions(objs, coEvents, dt);

		if (coEvents.size() == 0)
		{
			float x = this->BottomPosition()->x + this->wV.x * dt;
			float y = this->BottomPosition()->y + this->wV.y * dt;
			SetBottomPosition(D3DXVECTOR2(x, y));
			this->wV.y += wG * dt;
			//DebugOut(L"ahihihihihi");
		}
		else
		{
			Idle();

			float min_tx, min_ty, nx = 0, ny = 0;
			a->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			//DebugOut(L"%d\n", coEventsResult.size());
			for (int i = 0; i < coEventsResult.size(); i++) {
				
				if (coEventsResult.at(i)->obj->GetTypeObj() != 15) {
					float x = this->bottomPos->x + this->Velocity().x * dt * min_tx;
					float y = this->bottomPos->y + this->Velocity().y * dt * min_ty;

					SetBottomPosition(D3DXVECTOR2(x, y));

					int a = coEvents.at(i)->obj->CollisionBox().top;
					int b = coEventsResult.at(i)->obj->CollisionBox().top;
					if (nx != 0) this->SetVelocity(D3DXVECTOR2(0, this->wV.y));//this->wV.y
					if (ny != 0) this->SetVelocity(D3DXVECTOR2(this->wV.x, 0));
				}
				//va cham voi rock
				else if (coEventsResult.at(i)->obj->GetTypeObj() == 15)
				{
					if (coEventsResult.at(i)->obj->GetAnimations()->GetCurrentAnimation()->GetCurrentFrameID() != 4) {
						float x = this->BottomPosition()->x + this->wV.x * dt;
						float y = this->BottomPosition()->y + this->wV.y * dt;
						SetBottomPosition(D3DXVECTOR2(x, y));
						this->wV.y += wG * dt;
					}
					else
					{
						float x = this->bottomPos->x + this->Velocity().x * dt * min_tx;
						float y = this->bottomPos->y + this->Velocity().y * dt * min_ty;


						SetBottomPosition(D3DXVECTOR2(x, y));

						int a = coEvents.at(i)->obj->CollisionBox().top;
						int b = coEventsResult.at(i)->obj->CollisionBox().top;

						if (nx != 0) this->SetVelocity(D3DXVECTOR2(0, this->wV.y));//this->wV.y
						if (ny != 0) this->SetVelocity(D3DXVECTOR2(this->wV.x, 0));
					}
				}
				
			}
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
		if (this->animations->GetCurrentAnimationID() == Aladin::ANIMATIONS::dieright && this->animations->GetCurrentAnimation()->GetCurrentFrameID() == 27)
		{
			this->SetExist(false);

			////kiem tra dieu kien restart
			if (this->solanchoi > 0)
			{
				this->SetExist(true);
				this->SetBottomPosition(this->posrestart);
				this->solanchoi--;
				this->SetHP(12);
				this->IdleRight();
			}
		}
		if (animations != nullptr) {

			animations->Update(dt);
		}
		if (statushurt == true)
		{
			timenotdie -= dt;
			if (timenotdie <= 0) {
				statushurt = false;
				timenotdie = 2000;
			}
		}

		dx = wV.x * dt;
		dy = wV.y * dt;
		throwtime -= dt;

	}
	for each (LPAPPLE apple in apples)
	{
		if (apple->GetExist() == true)
			apple->Update(dt, objs);
	}

	Interact(dt, objs);
}


void Aladin::Interact(DWORD dt, vector<LPOBJECT>* objs)
{
	for (int i = 0; i < objs->size(); i++)
	{
		if (objs->at(i)->GetTypeObj() == Object::TYPEOBJECT::swordGuard)
		{
			InteractAladinWithSword(objs->at(i));
		}
		if (objs->at(i)->GetTypeObj() == Object::TYPEOBJECT::staffguard)
		{
			InteractAladinWithStaff(objs->at(i));
		}
		if (objs->at(i)->GetTypeObj() == Object::TYPEOBJECT::jafar)
		{
			InteractAladinWithJafar(objs->at(i));
		}
	}
}


void Aladin::InteractAladinWithSkeleton(LPOBJECT Skele)
{
	/*for (int i = 0; i < apples.size(); i++)
	{
		if (isColliding(apples.at(i), Skele))
		{
			if (Skele->GetTypeObj() == Object::TYPEOBJECT::skeleton)
			{
				Skeleton* a = (Skeleton*)(Skele);
				a->Die();
			}
			this->apples.at(i)->SetExist(false);
		}
	}*/
}



void Aladin::InteractAladinWithSword(LPOBJECT Sword)
{
	for (int i = 0; i < ALADDIN_APPLE_COUNT_ONE_TIME; i++)
	{
		if (isColliding(apples[i], Sword)&&apples[i]->GetExist()==true)
		{
			SwordGuard* a = (SwordGuard*)(Sword);
			if (a->GetHP() <= 0)
			{
				a->Die();
			}
			else
			{
				a->Hunt(1);
			}
			this->apples[i]->Destroy();
		}
	}

}



void Aladin::InteractAladinWithStaff(LPOBJECT Staff)
{
	for (int i = 0; i < ALADDIN_APPLE_COUNT_ONE_TIME; i++)
	{
		if (isColliding(apples[i], Staff) && apples[i]->GetExist() == true)
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
			this->apples[i]->Destroy();
		}
	}
}


void Aladin::InteractAladinWithJafar(LPOBJECT Jafar)
{
	JaFar* a = (JaFar*)(Jafar);
	for (int i = 0; i < ALADDIN_APPLE_COUNT_ONE_TIME; i++)
	{
		if (isColliding(apples[i], Jafar) && apples[i]->GetExist()&&a->GetExist()==true)
		{
			
			int hp = a->GetHP();
			a->SetHP(hp - 1);
			if (a->GetHP() <= 0)
			{
				a->SetExist(false);
			}
			
			this->apples[i]->Destroy();
			DebugOut(L"HP jafar tao: %d\n", a->GetHP());
		}
	}
}



bool Aladin::isColliding(LPOBJECT object, LPOBJECT other)
{
	RECT r_obj; RECT r_other;
	r_obj = object->CollisionBox();
	r_other = other->CollisionBox();

	float left = r_other.left - r_obj.right;
	float top = r_other.bottom - r_obj.top;
	float right = r_other.right - r_obj.left;
	float bottom = r_other.top - r_obj.bottom;
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}
void Aladin::AddApples(LPAPPLE apple)
{
	this->ApplesCount++;
}



void Aladin::Idle()
{
	if (IsAni(ANIMATIONS::climbdropdown))
	{
		if (Direction == 1)
			IdleRight();
		else
			IdleLeft();
	}
}


void Aladin::IdleRight()
{	
	Direction = 1;
	wG = 0.00096f;
	this->wV.x = 0.0f;
	this->animations->Start(ANIMATIONS::idleright);
}

void Aladin::IdleLeft()
{
	wG = 0.00096f;
	this->wV.x = 0.0f;
	this->animations->Start(ANIMATIONS::idleleft);	
}

void Aladin::IdleThrowRight()
{	
	this->wV.x = 0.0f;
	this->animations->Start(ANIMATIONS::idlethrowright);
	this->ThrowApple();
}

void Aladin::IdleThrowLeft()
{
	this->wV.x = 0.0f;
	this->animations->Start(ANIMATIONS::idlethrowleft);
	this->ThrowApple();
}

void Aladin::IdleAttackRight()
{
	this->wV.x = 0.0f;
	this->animations->Start(ANIMATIONS::idleattackright);
}

void Aladin::IdleAttackLeft()
{
	this->wV.x = 0.0f;
	this->animations->Start(ANIMATIONS::idleattackleft);
}

void Aladin::JumpUpRight()
{	
	if (this->animations->GetCurrentAnimationID() != ANIMATIONS::jumpupright) {
		/*wV.y = -140.0 / 600.0f;
		wG = 140.0f / (600 * 600);*/
		wV.y = -0.39f;
		wG = 0.00096f;
		this->animations->Start(ANIMATIONS::jumpupright);
	}
}

void Aladin::JumpUpLeft()
{
	if (this->animations->GetCurrentAnimationID() != ANIMATIONS::jumpupleft) {
		wV.y = -0.39f;
		wG = 0.00096f;
		this->animations->Start(ANIMATIONS::jumpupleft);
	}
}


void Aladin::JumpRight()
{
	this->Direction = 1;
	wV.y = -0.4f;
	wG = 0.001125f;
	this->animations->Start(ANIMATIONS::jumpright);
}


void Aladin::JumpLeft()
{
	this->Direction = 0;
	if (this->animations->GetCurrentAnimationID() != ANIMATIONS::jumpleft) {
		wV.y = -0.4f;
		wG = 0.001125f;
		this->animations->Start(ANIMATIONS::jumpleft);
	}
}

void Aladin::JumpUpThrowRight()
{
	this->animations->Start(ANIMATIONS::jumpupthrowright);
	this->ThrowApple();
}

void Aladin::JumpUpThrowLeft()
{
	this->animations->Start(ANIMATIONS::jumpupthrowleft);
	this->ThrowApple();
}

void Aladin::JumpUpAttackRight()
{
	this->animations->Start(ANIMATIONS::jumpupattackright);
}

void Aladin::JumpUpAttackLeft()
{
	this->animations->Start(ANIMATIONS::jumpupattackleft);
}

void Aladin::JumpAttackRight()
{
	this->animations->Start(ANIMATIONS::jumpattackright);
}

void Aladin::JumpAttackLeft()
{
	this->animations->Start(ANIMATIONS::jumpattackleft);
}

void Aladin::SitRight()
{
	this->Direction = 1;
	this->animations->Start(ANIMATIONS::sitright);
}

void Aladin::SitLeft()
{
	this->Direction = 0;
	this->animations->Start(ANIMATIONS::sitleft);
}

void Aladin::SitThrowRight()
{
	this->Direction = 1;
	this->animations->Start(ANIMATIONS::sitthrowright);
}

void Aladin::SitThrowLeft()
{
}

void Aladin::SitAttackRight()
{
	this->animations->Start(ANIMATIONS::sitattackright);
}

void Aladin::SitAttackLeft()
{
	this->animations->Start(ANIMATIONS::sitattackleft);
}


void Aladin::WalkRight()
{
	Direction = 1;
	if (this->animations->GetCurrentAnimationID() != (ANIMATIONS::jumpupright)) {
		this->animations->Start(ANIMATIONS::walkright);
		wV.x = 0.15f;
	}
}

void Aladin::WalkLeft()
{
	this->Direction = 0;
	if (this->animations->GetCurrentAnimationID() != (ANIMATIONS::jumpupleft)) {
		this->animations->Start(ANIMATIONS::walkleft);
		wV.x = -0.15f;
	}
}

void Aladin::WalkAttackRight()
{
	Direction = 1;
	this->animations->Start(ANIMATIONS::walkattackright);
	wV.x = 0.15f;
}

void Aladin::WalkAttackLeft()
{
	Direction = 0;
	this->animations->Start(ANIMATIONS::walkattackleft);
	wV.x = -0.15f;
}

void Aladin::WalkThrowRight()
{
	this->wV.x = 0.15f;
	this->animations->Start(ANIMATIONS::walkthrowright);
	this->ThrowApple();
}

void Aladin::WalkThrowLeft()
{
	this->wV.x = -0.15f;
	this->animations->Start(ANIMATIONS::walkthrowleft);
	this->ThrowApple();
}

void Aladin::ClimbUp()
{
	this->wV.y = -0.15f;
	this->animations->Start(ANIMATIONS::climbup);
}

void Aladin::ClimbDown()
{
	this->wV.y = 0.15f;
	this->animations->Start(ANIMATIONS::climbdown);
}

void Aladin::ClimbJump()
{
	this->wV.y = -0.4f;
	this->wG = 0.001125f;
	this->animations->Start(ANIMATIONS::climbjump);
}

void Aladin::ClimbDropDown()
{
	if (this->IsAni(ANIMATIONS::climbjump)) {
		this->animations->Start(ANIMATIONS::climbdropdown, this->animations->GetCurrentAnimation()->GetCurrentFrameID());
	}
	else {
		this->wG = 0.000525f;
		this->animations->Start(ANIMATIONS::climbdropdown);
	}
}


void Aladin::FallRight()
{
	this->animations->Start(ANIMATIONS::fallright);
}

void Aladin::FallLeft()
{
	this->animations->Start(ANIMATIONS::fallleft);
}

void Aladin::StopRight()
{
}

void Aladin::StopLeft()
{
}

void Aladin::HurtRight()
{
}

void Aladin::HurtLeft()
{
}

void Aladin::DieRight()
{
}

void Aladin::DieLeft()
{
}

void Aladin::RevivalRight()
{
}

void Aladin::RevivalLeft()
{
	this->animations->Start(ANIMATIONS::revivalleft);
}

void Aladin::UpRight()
{
	this->animations->Start(ANIMATIONS::upright);
}

void Aladin::UpLeft()
{
	this->animations->Start(ANIMATIONS::upleft);
}

void Aladin::IdleClimb()
{
	this->wV.y = 0;
	this->wV.x = 0;
	this->wG = 0.0f;
	this->animations->Start(ANIMATIONS::idleclimb);
}

void Aladin::MoveRight()
{
	this->Direction = 1;
	wV.x = 0.15f;
}

void Aladin::MoveLeft()
{
	this->Direction = 0;
	wV.x = -0.15f;
}




bool Aladin::IsGround()
{
	//return isGround;
	return 0;
}

void Aladin::SetIsGround(bool _isGround)
{
	//isGround = _isGround;
}

void Aladin::ThrowApple()
{
	if (ApplesCount > 0) {
		for (int i = 0; i < ALADDIN_APPLE_COUNT_ONE_TIME; i++) {
			if (apples[i]->GetExist() == false) {
				ApplesCount--;
				apples[i]->SetExist(true);
				apples[i]->GetAnimations()->Start(Apple::ANIMATIONS::idle);
				D3DXVECTOR2 applePos = D3DXVECTOR2(this->BottomPosition()->x, this->BottomPosition()->y - this->Height() * 2);
				apples[i]->SetCenterPosition(applePos);
				apples[i]->SetG(0.0005f);
				if (this->Direction == 1)
					apples[i]->SetVelocity(D3DXVECTOR2(0.4f, 0.0f));
				else
					apples[i]->SetVelocity(D3DXVECTOR2(-0.4f, 0.0f));
				break;
			}
		}
	}
}

void Aladin::Hurt(int damage)
{
	
	if (this->animations->GetCurrentAnimationID() !=ANIMATIONS::hurtright)
	{
		if (this->statushurt == false)
		{	
			sound->LoadSound("Sounds/Aladdin_Hurt.wav", "Aladdin_Hurt");
			sound->Play("Aladdin_Hurt", 0, 1);
			this->wV.x = 0.0f;
			this->SetHP(this->HP - damage);
			this->GetAnimations()->Start(ANIMATIONS::hurtright);
			this->statushurt = true;
		}
		
		/*this->GetAnimations()->Start(ANIMATIONS::hurtright);*/
	}
	
}

void Aladin::Die()
{
	if (sound != nullptr) {
		sound->LoadSound("Sounds/Aladdin_Die.wav", "Aladdin_Die");
		sound->Play("Aladdin_Die", 0, 1);
	}
	
	this->GetAnimations()->Start(ANIMATIONS::dieright);
	//this->SetExist(false);
	
}


