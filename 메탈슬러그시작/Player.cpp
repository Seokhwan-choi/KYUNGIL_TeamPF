#include "stdafx.h"
#include "Player.h"
#include "Monster.h"

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	//==============기본상속받는변수 =====================================
	_name = name;				// 클래스 이름 설정 해준다.
	_position = pos;			// 좌표 초기화 해준다.
	_size = size;				// 사이즈 초기화 해준다.
	_pivot = Pivot::Center;	// 피벗 위치 잡아준다.
	this->UpdateRectByPivot();	// RECT 그려준다.
	_isActive = true;			// 활성화 되어있다. 
	_isLive = true;				// 살아 있다.
	
	//========================플레이어헤더 ================================
	_jumppower = 0.0f; //플레이어 점프힘 
	_gravity = 0.0f; //플레이어 중력 
	_isJump = false; //최초 점프안된상태 



	_playerboomFire = false;//플레이어 폭탄상태 false일떄만 쏠수있고 true일시 폭탄사용불가하다 

	//==================================플레이어 해비머신건 변수 =================================
	_time = 0;//항상update되고 해비머신건발사시 4발정도 간격을 주기위하여 
	_count = 0;//해비머신건이 발사됫을시 count가 4가되면 fire를 false로 만들기 위하여 
	_fire = false;//키를 누르면 true가되고 해비머신건이 발사가된다 

	//=================플레이어 공용총알 
	_playerbullet = new Bullet("플레이어 공용총알");
	_playerbullet->Init("입술.bmp",10,10,100,800);

	_playerboom = new Boom("플레이어 폭탄");
	_playerboom->Init("입술.bmp",10,10,2,WINSIZEY);

	_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;//플레이어 최초상태는 오른쪽보고 총알쏘는상태 
	_playerheavystate = PLAYERHEAVYSTATE::IDLE;//플레이어 해비머신건최초상태
	_playerweaponstate = PLAYERWEAPONSTATE::NORMAL; //플레이어의 기본 총상태는 딱총상태이다 
	_playersword = PLAYERSWORD::RIGHTATTACK;//칼은 기본적으로 오른쪽모션먼저세팅되어있다 


	//==============왼쪽칼렉트와 오른쪽칼렉트 =====================================
	//PlayerLeftSword = RectMakeCenter(_rc.left,_rc.top+25,20,20);
	//PlayerRightSword = RectMakeCenter(_rc.right, _rc.bottom, 20, 20);

	PlayerRealSwordState = false;  //진짜 충돌할 칼의 bool 값 
	SwordCount = 0; //칼 몆초뒤에 꺼주게할려고  

}
Player::~Player()
{
}

HRESULT Player::Init()
{
	return S_OK;
}

void Player::Release()
{
	
}

void Player::Update()
{
	SwordCount++;//칼충돌됫을시 몆초뒤에 충돌박스 커주는 변수 
	_time++;//해비머신건용 time변수 항시 update 

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))//플레이어 왼쪽키 눌럿을시 
	{
		_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;//왼쪽상태에서는 총알 왼쪽으로 나간다 
		_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;//왼쪽상태에서는 해비머신건 왼쪽으로나간다 
		
		_position.x -= 3.0f;//플레이어 움직임 

		_isLeft = true; //왼쪽눌르면 isLeft는 true 
		_angle = 3.14f;//양수확인용앵글 각도가 양수일때는 양수전용 변수를 만든다 up키 누를시 
		_angle1 = -3.14f; //음수확인용앵글 각도가 음수일때는 음수전용 변수를 만들어야한다 점프하고 아래보면서쏠떄

		
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))//플레이어 오른쪽키 눌럿을시 
	{
		_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;//오른쪾상태에서는 총알 오른쪽으로 나간다 
		_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;//오른쪽상태에서는 해비머신건 오른쪽으로나간다 

		_position.x += 3.0f; //플레이어 오른쪽으로 움직임 

		_isLeft = false;//오른쪽키눌르면 isleft는 false 
		_angle = 0.0f;//오른쪽기준이니까 양수angel=0이다 
		_angle1 = 0.0f;//오른쪽기준이라 음수용angle도 0이다 
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) //플레이어 아래쪽키 눌럿을시 
	{
		_playerheavystate = PLAYERHEAVYSTATE::DOWNATTACK; //아래쪽키만 눌르면 방향은 쭈그려서 쏜다 
		_playerbulletstate = PLAYERBULLETSTATE::DOWNATTACK;//아래쪽키만 눌르면 방향은 쭈그려서 쏜다 
	}

	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))//아래쪽쏘다가 키를 떗을시 공격상태 위쪽으로 조정할려고 
	{
		if (_isLeft == true)//해비머신건상태가 왼쪽상태에서 키가떄지면 왼쪽공격나가기 
		{
			_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;
		}

		else if (_isLeft == false)//해비머신건상태가 오른쪽상태에서 키가떄지면 오른쪽공격나가기 
		{
			_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;
		}

		if (_isLeft == true)//기본딱총상태가 왼쪽상태에서 키가떄지면 왼쪽공격나가기 
		{
			_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;
		}

		else if (_isLeft == false)//기본딱총상태가 오른쪽상태에서 키가떄지면 오른쪽공격나가기 
		{
			_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))//플레이어 up키를 누르면 
	{
		_playerbulletstate = PLAYERBULLETSTATE::UPFIRE; //위쪽상태에서는 총알 위쪽으로 나간다 
		_playerheavystate = PLAYERHEAVYSTATE::UPFIRE; //해미머신건 방향은 위쪽이 된다 

		if (_isLeft == true)//왼쪽보고잇을시에는 
		{
			_angle -= 0.125f;
			if (_angle < PI / 2)
			{
				_angle = PI / 2;
			}
		}

		else if (_isLeft == false)
		{
			_angle += 0.125f;
			if (_angle > PI / 2)
			{
				_angle = PI / 2;
			}
		}
	}

	else
		if (_isLeft == true)
		{
			_angle += 0.125f;
			if (_angle > 3.14f)
			{
				_angle = 3.14f;
			}
		}

		else if (_isLeft == false)
		{
			_angle -= 0.125f;
			if (_angle < 0)
			{
				_angle = 0.0f;
			}
		}

	if (_isJump == true)//점프가 true일떄  
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{//아래쪽키를 누르면 
			_playerbulletstate = PLAYERBULLETSTATE::DOWNFIRE;
			_playerheavystate = PLAYERHEAVYSTATE::DOWNFIRE;
			//플레이어 총알방향은 아래쪽이된다 

			if (_isLeft == true)
			{
				_angle1 += 0.125f;
				if (_angle1 > -(PI / 2) )
				{
					_angle1 = -(PI / 2);
				}
			}
			else if (_isLeft == false)
			{
				_angle1 -= 0.125f;
				if (_angle1 < -(PI / 2))
				{
					_angle1 = -(PI / 2);
				}
			}
		}
		else
			if (_isLeft == true)
			{
				_angle1 -= 0.125f;
				if (_angle1 < -PI)
				{
					_angle1 = -PI;
				}
			}
			else if (_isLeft == false)
			{
				_angle1 += 0.125f;
				if (_angle1 > 0)
				{
					_angle1 = 0.0f;
				}
			}
	}

	if (_isJump == false  && _playerbulletstate == PLAYERBULLETSTATE::DOWNFIRE)
	{//점프상태가 아니고 총알방향이 아래쪽일떄는 
		_playerbulletstate = PLAYERBULLETSTATE::IDLE;
	}//총알방향은 아무것도 안나가게 막아놧다 

	 //점프상태가 아니고 총알방향이 아래쪽일떄는
	if (_isJump == false && _playerheavystate == PLAYERHEAVYSTATE::DOWNFIRE)
	{
		_playerheavystate = PLAYERHEAVYSTATE::IDLE;
	}//총알방향은 아무것도 안나가게 막아놧다 


	// =======================================================================
	// ########################## 헤비 머신건 예시 #############################
	// =======================================================================
	// 한번에 4발씩 발사한다.
	if (_fire == true) 
	{
		if (_time % 3 == 0) //0.03초마다 해비머신건이 발사된다 
		{
			//_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, _angle, 5.5f);
			switch (_playerheavystate)
			{
			case PLAYERHEAVYSTATE::LEFTFIRE://왼쪽만 가는 헤비머신건 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, PI, 5.5f);
				break;
			case PLAYERHEAVYSTATE::RIGHTFIRE://오른쪽만 가는 헤비머신건 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10), 0, 5.5f);
				break;
			case PLAYERHEAVYSTATE::UPFIRE://위에보면서 좌르륵가는거 
				_playerbullet->fire(_position.x, _position.y, _angle, 5.5f);
				break;
			case PLAYERHEAVYSTATE::DOWNFIRE://점프상태일떄 아래보면서 쏘는거 
				_playerbullet->fire(_position.x, _position.y, _angle1, 5.5f);
				break;
			case PLAYERHEAVYSTATE::DOWNATTACK://그냥 앉아서 쏘는거 
				_playerbullet->fire(_position.x, RND->range(_position.y +10, _position.y + 30), _angle, 10.5f);
			case PLAYERHEAVYSTATE::IDLE:
				break;
			}
			_count++;//발사되고 count라는 변수를 1씩 증가시킨다
		}
	}

	if (_count == 4)//4번 됫다면 발사를 못하게한다  
	{
		_fire = false;
		_count = 0;//다시 count는 0으로초기화한다 
	}
	
	if (KEYMANAGER->isOnceKeyDown('S') &&_isJump==false)//점프상태 아닐떄 S키 누르면 
	{
		_isJump = true; //점프는 true가되고 
		_jumppower = 10.5f; //점프힘에 7.5
		_gravity = 0.5f; //중력값은 0.5
	}

	if (_isJump == true)//점프상태가 true라면 
	{
		_position.y -= _jumppower;//플레이어 y축은 점프힘만큼 빼준다  
		_jumppower -= _gravity;//점프힘은 중력값만큼 빠진다 
	}

	if (_position.y > 400)//플레이어 중점이 400보다 커지면 
	{
		_isJump = false;		//점프상태는 false로 바까준다 
	}

	if (KEYMANAGER->isOnceKeyDown('A'))//A키를 눌럿을떄 
	{
		switch (_playerweaponstate)
		{
		case PLAYERWEAPONSTATE::NORMAL:
			switch (_playerbulletstate)
			{
			case PLAYERBULLETSTATE::LEFTFIRE:
				_playerbullet->fire(_position.x, _position.y, PI, 5.5f);
				break;
			case PLAYERBULLETSTATE::RIGHTFIRE:
				_playerbullet->fire(_position.x, _position.y, 0, 5.5f);
				break;
			case PLAYERBULLETSTATE::UPFIRE:
				_playerbullet->fire(_position.x, _position.y, PI / 2, 5.5f);
				break;
			case PLAYERBULLETSTATE::DOWNFIRE:
				_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 5.5f);
				break;
			case PLAYERBULLETSTATE::DOWNATTACK:
				_playerbullet->fire(_position.x, _position.y + 20, _angle, 5.5f);
			case PLAYERBULLETSTATE::IDLE:
				break;
			}
			break;
	 
		case PLAYERWEAPONSTATE::HEAVY:
			_fire = true;//fire발사가되면  
			break;

		case PLAYERWEAPONSTATE::SWORD:

			switch (_playersword)
			{
			case PLAYERSWORD::LEFTATTACK:	
				PlayerRealSwordState = true;
				PlayerRealLeftSword = RectMakeCenter(_rc.left - 20, _rc.top - 10, 40, 40);
				break;
			case PLAYERSWORD::RIGHTATTACK:
				PlayerRealSwordState = true; 
				PlayerRealRightSword = RectMakeCenter(_rc.right, _rc.top - 10, 20, 20);
				break;
			}
			break;
		}

	}
	//================================================칼충돌햇을시=========================
	RECT temp;
	if (IntersectRect(&temp, &PlayerRightSword,
		&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "몬스터")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "몬스터")->GetActive())
	{//플레이어옆에 오른쪽렉트가 몬스타랑 충돌햇을시 칼상태를 소드로 바까준다 
		_playerweaponstate = PLAYERWEAPONSTATE::SWORD;
		_playersword = PLAYERSWORD::RIGHTATTACK;
	}

	else if (IntersectRect(&temp, &PlayerLeftSword,
		&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "몬스터")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "몬스터")->GetActive())
	{//플레이어옆에 왼쪽렉트가 몬스타랑 충돌햇을시 칼상태를 소드로 바까준다 
		_playerweaponstate = PLAYERWEAPONSTATE::SWORD;
		_playersword = PLAYERSWORD::LEFTATTACK;
	}

	else
	{//나중에 저장된 무기로 바까줄꺼다 
		_playerweaponstate = PLAYERWEAPONSTATE::HEAVY;
	}
	if (SwordCount % 100 == 0)//칼모션이나가고 1초뒤에 false로바까 안보이게할려고 
	{
		PlayerRealSwordState = false;
	}
	//====================디버그용 예시용도다 확인===================================================================== 
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		if (_playerweaponstate == PLAYERWEAPONSTATE::NORMAL)
		{
			_playerweaponstate = PLAYERWEAPONSTATE::HEAVY;
		}
		else {
			_playerweaponstate = PLAYERWEAPONSTATE::NORMAL;
		}
	}


	if (KEYMANAGER->isOnceKeyDown('D') &&_playerboomFire ==false)//boomfire가 false일때만 수류탄던질수가있다 
	{
		//만약에 수류탄이 바닥이랑 충돌하며ㅑㄴ 
		if (_isLeft == true)
		{
			_playerboom->fire(_position.x, _position.y, PI - 1.1f, 0.5f, 7.5f);	
		}
		else if (_isLeft == false )
		{
			_playerboom->fire(_position.x, _position.y, 1.14f, 0.5f, 7.5f);
		}	
	}
	if (_playerboom->GetPlayerBoomMax() <= 0)//플레이어 수류탄갯수 던지는거 처리는 bullet클래스boom에서 처리한다 
	{
		_playerboomFire = true;//true가 되면 던질수가없다 
	}
	
	_playerbullet->move();//플레이어 총알은 항시 움직이고 
	_playerboom->move();//플레이어 폭탄도 항심 움직인다  

	this->UpdateRectByPivot();//렉트를 다시그려주는거 즉 업데이트에서 항시움직일려고  
	PlayerLeftSword = RectMake(_rc.left-20 , _rc.top , 20, 20);//안보이지만 실제 애랑충돌되면 weaponstate가 칼로바뀐다
	PlayerRightSword = RectMake(_rc.right, _rc.top , 20, 20);//안보이지만 실제 애랑충돌되면 weaponstate가 칼로바뀐다

}

void Player::Render()
{
	Rectangle(getMemDC(), _rc);//플레이어 렉트 보여주기 
	_playerbullet->Render(); //bullet에서 받아서 기본총 보여주기 
	_playerboom->Render();   //플레이어 폭탄 보여주기 
	
	//Rectangle(getMemDC(), PlayerLeftSword); //실제충돌되는 렉트 확인용
	//Rectangle(getMemDC(), PlayerRightSword);//실제충돌되는 렉트 확인용

	//==수류탄갯수 확인용 
	//char str[256];
	//sprintf_s(str, "?=%d", _playerboom->GetPlayerBoomMax());
	//TextOut(getMemDC(), 100, 100, str, strlen(str));

	//플레이어 레프트모션이고 실제충돌칼이 true일떄만 충돌용소드를 그려준다
	if (_playersword == PLAYERSWORD::LEFTATTACK &&PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealLeftSword);
	}
	//플레이어 오른쪽 모션이고 실제충돌칼이 true일떄만 충돌용소드를 그려준다
	if (_playersword == PLAYERSWORD::RIGHTATTACK &&PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealRightSword);
	}

}



