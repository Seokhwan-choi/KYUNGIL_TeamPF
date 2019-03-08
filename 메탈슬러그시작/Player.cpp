#include "stdafx.h"
#include "Player.h"


Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	//==============�⺻��ӹ޴º��� 
	_name = name;				// Ŭ���� �̸� ���� ���ش�.
	_position = pos;			// ��ǥ �ʱ�ȭ ���ش�.
	_size = size;				// ������ �ʱ�ȭ ���ش�.
	_pivot = Pivot::Center;	// �ǹ� ��ġ ����ش�.
	this->UpdateRectByPivot();	// RECT �׷��ش�.
	_isActive = true;			// Ȱ��ȭ �Ǿ��ִ�. 
	_isLive = true;				// ��� �ִ�.
	
	//========================�÷��̾���� 
	_jumppower = 0.0f; //�÷��̾� ������ 
	_gravity = 0.0f; //�÷��̾� �߷� 
	_isJump = false; //���� �����ȵȻ��� 

	_angle = 0.0f;
	_time = 0;
	_count = 0;
	_fire = false;

	//=================�÷��̾� �����Ѿ� 
	_playerbullet = new Bullet("�÷��̾� �����Ѿ�");
	_playerbullet->Init("�Լ�.bmp",10,10,100,800);

	_playerboom = new Boom("�÷��̾� ��ź");
	_playerboom->Init("�Լ�.bmp",10,10,800);

	_playerbulletstate = PLAYERBULLETSTATE::IDLE;//�÷��̾� ���ʻ��´� �����ʺ��� �Ѿ˽�»��� 
	_playerheavystate = PLAYERHEAVYSTATE::IDLE;//�÷��̾� �غ�ӽŰ����ʻ���


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
	//�̻��� ���� 
	//_playerbullet->Release();
	//SAFE_DELETE(_playerbullet);
}

void Player::Update()
{
	_time++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;//���ʻ��¿����� �Ѿ� �������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;
		_position.x -= 3.0f;
		_angle += 0.125f;
		if (_angle > PI) _angle = PI;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;//�����U���¿����� �Ѿ� ���������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;
		_position.x += 20.0f;
		_angle -= 0.125f;
		if (_angle < 0.0f) _angle = 0.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerbulletstate = PLAYERBULLETSTATE::UPFIRE; //���ʻ��¿����� �Ѿ� �������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::UPFIRE;
		_angle += 0.125f;
		if (_angle > PI / 2.0f) _angle = PI / 2.0f;
	}
	else
	{
		_angle -= 0.125f;
		if (_angle < 0.0f) _angle = 0.0f;
	}

	if (_isJump == true)//������ true�ϋ�  
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{//�Ʒ���Ű�� ������ 
			_playerbulletstate = PLAYERBULLETSTATE::DOWNFIRE;
			_playerheavystate = PLAYERHEAVYSTATE::DOWNFIRE;
			//�÷��̾� �Ѿ˹����� �Ʒ����̵ȴ� 
		}
	}
	
	if (_isJump == false  && _playerbulletstate == PLAYERBULLETSTATE::DOWNFIRE)
	{//�������°� �ƴϰ� �Ѿ˹����� �Ʒ����ϋ��� 
		_playerbulletstate = PLAYERBULLETSTATE::IDLE;
	}//�Ѿ˹����� �ƹ��͵� �ȳ����� ���ƇJ�� 

	if (_isJump == false && _playerheavystate == PLAYERHEAVYSTATE::DOWNFIRE)
	{
		_playerheavystate = PLAYERHEAVYSTATE::IDLE;
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_fire = true;
	}

	// =======================================================================
	// ########################## ��� �ӽŰ� ���� #############################
	// =======================================================================
	// �ѹ��� 5�߾� �߻��Ѵ�.
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

	if (KEYMANAGER->isOnceKeyDown('S') && _isJump==false)//�������� �ƴҋ� SŰ ������ 
	{
		_isJump = true; //������ true���ǰ� 
		_jumppower = 7.5f; //�������� 7.5
		_gravity = 0.5f; //�߷°��� 0.5
	}
	if (_isJump == true)//�������°� true��� 
	{
		_position.y -= _jumppower;//�÷��̾� y���� ��������ŭ ���ش�  
		_jumppower -= _gravity;//�������� �߷°���ŭ ������ 
	}

	if (_position.y > 650)//�÷��̾� ������ 400���� Ŀ���� 
	{
		_isJump = false;		//�������´� false�� �ٱ��ش� 
	}

	if (KEYMANAGER->isOnceKeyDown('A'))//AŰ�� �������� 
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

	_playerbullet->move();//�÷��̾� �Ѿ��� �׽� �����̰� 
	_playerboom->move(); 
	
	if ( _rc.right > 6550)
	{
		_rc.right -= _rc.right - 6550;
		_rc.left -= _rc.right - 6550;
	}
	
	this->UpdateRectByPivot();
	// �÷��̾ �߽����� ī�޶� ����
	CAMERA->SetCamera(_position);
}

void Player::Render()
{
	RECT _playerRC = CAMERA->Relative(_rc);
	Rectangle(getMemDC(), _playerRC);
	_playerbullet->Render();
	_playerboom->Render();

	char str[30];
	wsprintf(str, " X ��ǥ : %d", _position.x);
	TextOut(getMemDC(), 50, 50, str, strlen(str));
}



