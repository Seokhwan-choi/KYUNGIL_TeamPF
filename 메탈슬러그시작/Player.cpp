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



	
	_playerboomMax = 10; //�÷��̾� ��ź�ִ밹���� 10���� 
	_playerboomFire = true; 

	_time = 0;
	_count = 0;
	_fire = false;

	//=================�÷��̾� �����Ѿ� 
	_playerbullet = new Bullet("�÷��̾� �����Ѿ�");
	_playerbullet->Init("�Լ�.bmp",10,10,100,800);

	_playerboom = new Boom("�÷��̾� ��ź");
	_playerboom->Init("�Լ�.bmp",10,10,2);

	_playerbulletstate = PLAYERBULLETSTATE::IDLE;//�÷��̾� ���ʻ��´� �����ʺ��� �Ѿ˽�»��� 
	_playerheavystate = PLAYERHEAVYSTATE::IDLE;//�÷��̾� �غ�ӽŰ����ʻ���
	_playerweaponstate = PLAYERWEAPONSTATE::NORMAL; 

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
	_time++;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;//���ʻ��¿����� �Ѿ� �������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;
		_position.x -= 3.0f;

		_isLeft = true; 
		_angle = 3.14f;
		_angle1 = -3.14f;
		/*_angle += 0.125f;
		if (_angle > PI) _angle = PI;*/
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;//�����U���¿����� �Ѿ� ���������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;
		_position.x += 3.0f;

		_isLeft = false;
		_angle = 0.0f;
		_angle1 = 0.0f; 
		/*_angle -= 0.125f;
		if (_angle < 0.0f) _angle = 0.0f;*/
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_playerheavystate = PLAYERHEAVYSTATE::DOWNATTACK;
		_playerbulletstate = PLAYERBULLETSTATE::DOWNATTACK;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_isLeft == true)
		{
			_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;
		}
		else if (_isLeft == false)
		{
			_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;
		}

		if (_isLeft == true)
		{
			_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;
		}
		else if (_isLeft == false)
		{
			_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;

		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerbulletstate = PLAYERBULLETSTATE::UPFIRE; //���ʻ��¿����� �Ѿ� �������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::UPFIRE;
		//_angle += 0.125f;
		/*if (_angle > PI / 2.0f) _angle = PI / 2.0f;*/
		if (_isLeft == true)
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

	if (_isJump == true)//������ true�ϋ�  
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{//�Ʒ���Ű�� ������ 
			_playerbulletstate = PLAYERBULLETSTATE::DOWNFIRE;
			_playerheavystate = PLAYERHEAVYSTATE::DOWNFIRE;
			//�÷��̾� �Ѿ˹����� �Ʒ����̵ȴ� 

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
	{//�������°� �ƴϰ� �Ѿ˹����� �Ʒ����ϋ��� 
		_playerbulletstate = PLAYERBULLETSTATE::IDLE;
	}//�Ѿ˹����� �ƹ��͵� �ȳ����� ���ƇJ�� 

	if (_isJump == false && _playerheavystate == PLAYERHEAVYSTATE::DOWNFIRE)
	{
		_playerheavystate = PLAYERHEAVYSTATE::IDLE;
	}


	// =======================================================================
	// ########################## ��� �ӽŰ� ���� #############################
	// =======================================================================
	// �ѹ��� 5�߾� �߻��Ѵ�.
	if (_fire == true) 
	{
		if (_time % 3 == 0) 
		{
			//_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, _angle, 5.5f);
			switch (_playerheavystate)
			{
			case PLAYERHEAVYSTATE::LEFTFIRE://���ʸ� ���� ���ӽŰ� 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, PI, 5.5f);
				break;
			case PLAYERHEAVYSTATE::RIGHTFIRE://�����ʸ� ���� ���ӽŰ� 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10), 0, 5.5f);
				break;
			case PLAYERHEAVYSTATE::UPFIRE://�������鼭 �¸������°� 
				_playerbullet->fire(_position.x, _position.y, _angle, 5.5f);
				break;
			case PLAYERHEAVYSTATE::DOWNFIRE://���������ϋ� �Ʒ����鼭 ��°� 
				_playerbullet->fire(_position.x, _position.y, _angle1, 5.5f);
				break;
			case PLAYERHEAVYSTATE::DOWNATTACK://�׳� �ɾƼ� ��°� 
				_playerbullet->fire(_position.x, RND->range(_position.y +10, _position.y + 30), _angle, 10.5f);
			case PLAYERHEAVYSTATE::IDLE:
				break;
			}
			_count++;
		}
	}

	if (_count == 4) 
	{
		_fire = false;
		_count = 0;
	}
	

	if (KEYMANAGER->isOnceKeyDown('S') &&_isJump==false)//�������� �ƴҋ� SŰ ������ 
	{
		_isJump = true; //������ true���ǰ� 
		_jumppower = 10.5f; //�������� 7.5
		_gravity = 0.5f; //�߷°��� 0.5
	}
	if (_isJump == true)//�������°� true��� 
	{
		_position.y -= _jumppower;//�÷��̾� y���� ��������ŭ ���ش�  
		_jumppower -= _gravity;//�������� �߷°���ŭ ������ 
	}
	if (_position.y > 400)//�÷��̾� ������ 400���� Ŀ���� 
	{
		_isJump = false;		//�������´� false�� �ٱ��ش� 
	}

	if (KEYMANAGER->isOnceKeyDown('A'))//AŰ�� �������� 
	{
		//_playerweaponstate = PLAYERWEAPONSTATE::NORMAL;

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
			_fire = true;
			if (_fire == true)
			{
				if (_time % 3 == 0)
				{
					switch (_playerheavystate)
					{
					case PLAYERHEAVYSTATE::LEFTFIRE://���ʸ� ���� ���ӽŰ� 
						_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, PI, 5.5f);
						break;
					case PLAYERHEAVYSTATE::RIGHTFIRE://�����ʸ� ���� ���ӽŰ� 
						_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10), 0, 5.5f);
						break;
					case PLAYERHEAVYSTATE::UPFIRE://�������鼭 �¸������°� 
						_playerbullet->fire(_position.x, _position.y, _angle, 5.5f);
						break;
					case PLAYERHEAVYSTATE::DOWNFIRE://���������ϋ� �Ʒ����鼭 ��°� 
						_playerbullet->fire(_position.x, _position.y, _angle1, 5.5f);
						break;
					case PLAYERHEAVYSTATE::DOWNATTACK://�׳� �ɾƼ� ��°� 
						_playerbullet->fire(_position.x, RND->range(_position.y + 10, _position.y + 30), _angle, 10.5f);
					case PLAYERHEAVYSTATE::IDLE:
						break;
					}
					_count++;
				}
			}
			if (_count == 4)
			{
				_fire = false;
				_count = 0;
			}
			break;
		}
	}
	//====================����׿� ���ÿ뵵�� Ȯ��===================================================================== 
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		if (_playerweaponstate == PLAYERWEAPONSTATE::NORMAL)
		{
			_playerweaponstate = PLAYERWEAPONSTATE::HEAVY;
		}
		else {
			_playerweaponstate = PLAYERWEAPONSTATE::NORMAL;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		//���࿡ ����ź�� �ٴ��̶� �浹�ϸ���� 
		if (_isLeft == true && _playerboomFire==true)
		{
			_playerboom->fire(_position.x, _position.y, PI - 1.1f, 0.5f, 7.5f);
			_playerboomMax--; 
		}
		else if (_isLeft == false && _playerboomFire == true)
		{
			_playerboom->fire(_position.x, _position.y, 1.14f, 0.5f, 7.5f);
			_playerboomMax--;

		}
		//_playerboom->fire(_position.x,_position.y,PI+1.4f, 1.5f,5.5f);
	}
	if (_playerboomMax < 0)
	{
		_playerboomFire = false; 
	}
	_playerbullet->move();//�÷��̾� �Ѿ��� �׽� �����̰� 
	_playerboom->move();//�÷��̾� ��ź�� �׽� �����δ�  
	

	this->UpdateRectByPivot();//��Ʈ�� �ٽñ׷��ִ°� �� ������Ʈ���� �׽ÿ����Ϸ���  

}

void Player::Render()
{
	Rectangle(getMemDC(), _rc);//�÷��̾� ��Ʈ �����ֱ� 
	_playerbullet->Render(); //bullet���� �޾Ƽ� �⺻�� �����ֱ� 
	_playerboom->Render();   //�÷��̾� ��ź �����ֱ� 
}



