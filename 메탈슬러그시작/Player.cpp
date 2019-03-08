#include "stdafx.h"
#include "Player.h"


Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	//==============기본상속받는변수 
	_name = name;				// 클래스 이름 설정 해준다.
	_position = pos;			// 좌표 초기화 해준다.
	_size = size;				// 사이즈 초기화 해준다.
	_pivot = Pivot::Center;	// 피벗 위치 잡아준다.
	this->UpdateRectByPivot();	// RECT 그려준다.
	_isActive = true;			// 활성화 되어있다. 
	_isLive = true;				// 살아 있다.
	
	//========================플레이어헤더 
	_jumppower = 0.0f; //플레이어 점프힘 
	_gravity = 0.0f; //플레이어 중력 
	_isJump = false; //최초 점프안된상태 

	_angle = 0.0f;
	_time = 0;
	_count = 0;
	_fire = false;

	//=================플레이어 공용총알 
	_playerbullet = new Bullet("플레이어 공용총알");
	_playerbullet->Init("입술.bmp",10,10,100,800);

	_playerboom = new Boom("플레이어 폭탄");
	_playerboom->Init("입술.bmp",10,10,800);

	_playerbulletstate = PLAYERBULLETSTATE::IDLE;//플레이어 최초상태는 오른쪽보고 총알쏘는상태 
	_playerheavystate = PLAYERHEAVYSTATE::IDLE;//플레이어 해비머신건최초상태


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
	//미사일 해제 
	//_playerbullet->Release();
	//SAFE_DELETE(_playerbullet);
}

void Player::Update()
{
	_time++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;//왼쪽상태에서는 총알 왼쪽으로 나간다 
		_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;
		_position.x -= 3.0f;
		_angle += 0.125f;
		if (_angle > PI) _angle = PI;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;//오른쪾상태에서는 총알 오른쪽으로 나간다 
		_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;
		_position.x += 20.0f;
		_angle -= 0.125f;
		if (_angle < 0.0f) _angle = 0.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerbulletstate = PLAYERBULLETSTATE::UPFIRE; //위쪽상태에서는 총알 위쪽으로 나간다 
		_playerheavystate = PLAYERHEAVYSTATE::UPFIRE;
		_angle += 0.125f;
		if (_angle > PI / 2.0f) _angle = PI / 2.0f;
	}
	else
	{
		_angle -= 0.125f;
		if (_angle < 0.0f) _angle = 0.0f;
	}

	if (_isJump == true)//점프가 true일떄  
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{//아래쪽키를 누르면 
			_playerbulletstate = PLAYERBULLETSTATE::DOWNFIRE;
			_playerheavystate = PLAYERHEAVYSTATE::DOWNFIRE;
			//플레이어 총알방향은 아래쪽이된다 
		}
	}
	
	if (_isJump == false  && _playerbulletstate == PLAYERBULLETSTATE::DOWNFIRE)
	{//점프상태가 아니고 총알방향이 아래쪽일떄는 
		_playerbulletstate = PLAYERBULLETSTATE::IDLE;
	}//총알방향은 아무것도 안나가게 막아놧다 

	if (_isJump == false && _playerheavystate == PLAYERHEAVYSTATE::DOWNFIRE)
	{
		_playerheavystate = PLAYERHEAVYSTATE::IDLE;
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_fire = true;
	}

	// =======================================================================
	// ########################## 헤비 머신건 예시 #############################
	// =======================================================================
	// 한번에 5발씩 발사한다.
	if (_fire == true) 
	{
		if (_time % 3 == 0) 
		{
			_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, _angle, 5.5f);
			//switch (_playerheavystate)
			//{
			//case PLAYERHEAVYSTATE::LEFTFIRE:
			//	_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, PI, 5.5f);
			//	break;
			//case PLAYERHEAVYSTATE::RIGHTFIRE:
			//	_playerbullet->fire(_position.x, _position.y, 0, 5.5f);
			//	break;
			//case PLAYERHEAVYSTATE::UPFIRE:
			//	_playerbullet->fire(_position.x, _position.y, PI / 2, 5.5f);
			//	break;
			//case PLAYERHEAVYSTATE::DOWNFIRE:
			//	_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 5.5f);
			//	break;
			//case PLAYERHEAVYSTATE::IDLE:
			//	break;
			//}
			_count++;
		}
	}

	if (_count == 4) 
	{
		_fire = false;
		_count = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('S') && _isJump==false)//점프상태 아닐떄 S키 누르면 
	{
		_isJump = true; //점프는 true가되고 
		_jumppower = 7.5f; //점프힘에 7.5
		_gravity = 0.5f; //중력값은 0.5
	}
	if (_isJump == true)//점프상태가 true라면 
	{
		_position.y -= _jumppower;//플레이어 y축은 점프힘만큼 빼준다  
		_jumppower -= _gravity;//점프힘은 중력값만큼 빠진다 
	}

	if (_position.y > 650)//플레이어 중점이 400보다 커지면 
	{
		_isJump = false;		//점프상태는 false로 바까준다 
	}

	if (KEYMANAGER->isOnceKeyDown('A'))//A키를 눌럿을떄 
	{
		switch (_playerbulletstate)
		{
		case PLAYERBULLETSTATE::LEFTFIRE:
			_playerbullet->fire(_position.x, _position.y, PI , 5.5f);
			break;
		case PLAYERBULLETSTATE::RIGHTFIRE:
			_playerbullet->fire(_position.x, _position.y, 0 , 5.5f);
			break;
		case PLAYERBULLETSTATE::UPFIRE:
			_playerbullet->fire(_position.x, _position.y, PI/2, 5.5f);
			break;
		case PLAYERBULLETSTATE::DOWNFIRE:
			_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 5.5f);
			break;
		case PLAYERBULLETSTATE::IDLE:
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_playerboom->fire(_position.x,_position.y,PI-30, 1.5f,5.5f);
	}

	_playerbullet->move();//플레이어 총알은 항시 움직이고 
	_playerboom->move(); 
	
	if ( _rc.right > 6550)
	{
		_rc.right -= _rc.right - 6550;
		_rc.left -= _rc.right - 6550;
	}
	
	this->UpdateRectByPivot();
	// 플레이어를 중심으로 카메라 셋팅
	CAMERA->SetCamera(_position);
}

void Player::Render()
{
	RECT _playerRC = CAMERA->Relative(_rc);
	Rectangle(getMemDC(), _playerRC);
	_playerbullet->Render();
	_playerboom->Render();

	char str[30];
	wsprintf(str, " X 좌표 : %d", _position.x);
	TextOut(getMemDC(), 50, 50, str, strlen(str));
}



