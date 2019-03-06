#include "stdafx.h"
#include "Player.h"
#include "Monster.h"

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	//==============�⺻��ӹ޴º��� =====================================
	_name = name;				// Ŭ���� �̸� ���� ���ش�.
	_position = pos;			// ��ǥ �ʱ�ȭ ���ش�.
	_size = size;				// ������ �ʱ�ȭ ���ش�.
	_pivot = Pivot::Center;	// �ǹ� ��ġ ����ش�.
	this->UpdateRectByPivot();	// RECT �׷��ش�.
	_isActive = true;			// Ȱ��ȭ �Ǿ��ִ�. 
	_isLive = true;				// ��� �ִ�.
	
	//========================�÷��̾���� ================================
	_jumppower = 0.0f; //�÷��̾� ������ 
	_gravity = 0.0f; //�÷��̾� �߷� 
	_isJump = false; //���� �����ȵȻ��� 



	_playerboomFire = false;//�÷��̾� ��ź���� false�ϋ��� ����ְ� true�Ͻ� ��ź���Ұ��ϴ� 

	//==================================�÷��̾� �غ�ӽŰ� ���� =================================
	_time = 0;//�׻�update�ǰ� �غ�ӽŰǹ߻�� 4������ ������ �ֱ����Ͽ� 
	_count = 0;//�غ�ӽŰ��� �߻������ count�� 4���Ǹ� fire�� false�� ����� ���Ͽ� 
	_fire = false;//Ű�� ������ true���ǰ� �غ�ӽŰ��� �߻簡�ȴ� 

	//=================�÷��̾� �����Ѿ� 
	_playerbullet = new Bullet("�÷��̾� �����Ѿ�");
	_playerbullet->Init("�Լ�.bmp",10,10,100,800);

	_playerboom = new Boom("�÷��̾� ��ź");
	_playerboom->Init("�Լ�.bmp",10,10,2,WINSIZEY);

	_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;//�÷��̾� ���ʻ��´� �����ʺ��� �Ѿ˽�»��� 
	_playerheavystate = PLAYERHEAVYSTATE::IDLE;//�÷��̾� �غ�ӽŰ����ʻ���
	_playerweaponstate = PLAYERWEAPONSTATE::NORMAL; //�÷��̾��� �⺻ �ѻ��´� ���ѻ����̴� 
	_playersword = PLAYERSWORD::RIGHTATTACK;//Į�� �⺻������ �����ʸ�Ǹ������õǾ��ִ� 


	//==============����Į��Ʈ�� ������Į��Ʈ =====================================
	//PlayerLeftSword = RectMakeCenter(_rc.left,_rc.top+25,20,20);
	//PlayerRightSword = RectMakeCenter(_rc.right, _rc.bottom, 20, 20);

	PlayerRealSwordState = false;  //��¥ �浹�� Į�� bool �� 
	SwordCount = 0; //Į �p�ʵڿ� ���ְ��ҷ���  

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
	SwordCount++;//Į�浹������ �p�ʵڿ� �浹�ڽ� Ŀ�ִ� ���� 
	_time++;//�غ�ӽŰǿ� time���� �׽� update 

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))//�÷��̾� ����Ű �������� 
	{
		_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;//���ʻ��¿����� �Ѿ� �������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;//���ʻ��¿����� �غ�ӽŰ� �������γ����� 
		
		_position.x -= 3.0f;//�÷��̾� ������ 

		_isLeft = true; //���ʴ����� isLeft�� true 
		_angle = 3.14f;//���Ȯ�ο�ޱ� ������ ����϶��� ������� ������ ����� upŰ ������ 
		_angle1 = -3.14f; //����Ȯ�ο�ޱ� ������ �����϶��� �������� ������ �������Ѵ� �����ϰ� �Ʒ����鼭��

		
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))//�÷��̾� ������Ű �������� 
	{
		_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;//�����U���¿����� �Ѿ� ���������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;//�����ʻ��¿����� �غ�ӽŰ� ���������γ����� 

		_position.x += 3.0f; //�÷��̾� ���������� ������ 

		_isLeft = false;//������Ű������ isleft�� false 
		_angle = 0.0f;//�����ʱ����̴ϱ� ���angel=0�̴� 
		_angle1 = 0.0f;//�����ʱ����̶� ������angle�� 0�̴� 
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) //�÷��̾� �Ʒ���Ű �������� 
	{
		_playerheavystate = PLAYERHEAVYSTATE::DOWNATTACK; //�Ʒ���Ű�� ������ ������ �ޱ׷��� ��� 
		_playerbulletstate = PLAYERBULLETSTATE::DOWNATTACK;//�Ʒ���Ű�� ������ ������ �ޱ׷��� ��� 
	}

	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))//�Ʒ��ʽ�ٰ� Ű�� ������ ���ݻ��� �������� �����ҷ��� 
	{
		if (_isLeft == true)//�غ�ӽŰǻ��°� ���ʻ��¿��� Ű�������� ���ʰ��ݳ����� 
		{
			_playerheavystate = PLAYERHEAVYSTATE::LEFTFIRE;
		}

		else if (_isLeft == false)//�غ�ӽŰǻ��°� �����ʻ��¿��� Ű�������� �����ʰ��ݳ����� 
		{
			_playerheavystate = PLAYERHEAVYSTATE::RIGHTFIRE;
		}

		if (_isLeft == true)//�⺻���ѻ��°� ���ʻ��¿��� Ű�������� ���ʰ��ݳ����� 
		{
			_playerbulletstate = PLAYERBULLETSTATE::LEFTFIRE;
		}

		else if (_isLeft == false)//�⺻���ѻ��°� �����ʻ��¿��� Ű�������� �����ʰ��ݳ����� 
		{
			_playerbulletstate = PLAYERBULLETSTATE::RIGHTFIRE;
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))//�÷��̾� upŰ�� ������ 
	{
		_playerbulletstate = PLAYERBULLETSTATE::UPFIRE; //���ʻ��¿����� �Ѿ� �������� ������ 
		_playerheavystate = PLAYERHEAVYSTATE::UPFIRE; //�ع̸ӽŰ� ������ ������ �ȴ� 

		if (_isLeft == true)//���ʺ��������ÿ��� 
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

	 //�������°� �ƴϰ� �Ѿ˹����� �Ʒ����ϋ���
	if (_isJump == false && _playerheavystate == PLAYERHEAVYSTATE::DOWNFIRE)
	{
		_playerheavystate = PLAYERHEAVYSTATE::IDLE;
	}//�Ѿ˹����� �ƹ��͵� �ȳ����� ���ƇJ�� 


	// =======================================================================
	// ########################## ��� �ӽŰ� ���� #############################
	// =======================================================================
	// �ѹ��� 4�߾� �߻��Ѵ�.
	if (_fire == true) 
	{
		if (_time % 3 == 0) //0.03�ʸ��� �غ�ӽŰ��� �߻�ȴ� 
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
			_count++;//�߻�ǰ� count��� ������ 1�� ������Ų��
		}
	}

	if (_count == 4)//4�� �̴ٸ� �߻縦 ���ϰ��Ѵ�  
	{
		_fire = false;
		_count = 0;//�ٽ� count�� 0�����ʱ�ȭ�Ѵ� 
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
			_fire = true;//fire�߻簡�Ǹ�  
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
	//================================================Į�浹������=========================
	RECT temp;
	if (IntersectRect(&temp, &PlayerRightSword,
		&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "����")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "����")->GetActive())
	{//�÷��̾�� �����ʷ�Ʈ�� ��Ÿ�� �浹������ Į���¸� �ҵ�� �ٱ��ش� 
		_playerweaponstate = PLAYERWEAPONSTATE::SWORD;
		_playersword = PLAYERSWORD::RIGHTATTACK;
	}

	else if (IntersectRect(&temp, &PlayerLeftSword,
		&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "����")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "����")->GetActive())
	{//�÷��̾�� ���ʷ�Ʈ�� ��Ÿ�� �浹������ Į���¸� �ҵ�� �ٱ��ش� 
		_playerweaponstate = PLAYERWEAPONSTATE::SWORD;
		_playersword = PLAYERSWORD::LEFTATTACK;
	}

	else
	{//���߿� ����� ����� �ٱ��ٲ��� 
		_playerweaponstate = PLAYERWEAPONSTATE::HEAVY;
	}
	if (SwordCount % 100 == 0)//Į����̳����� 1�ʵڿ� false�ιٱ� �Ⱥ��̰��ҷ��� 
	{
		PlayerRealSwordState = false;
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


	if (KEYMANAGER->isOnceKeyDown('D') &&_playerboomFire ==false)//boomfire�� false�϶��� ����ź���������ִ� 
	{
		//���࿡ ����ź�� �ٴ��̶� �浹�ϸ���� 
		if (_isLeft == true)
		{
			_playerboom->fire(_position.x, _position.y, PI - 1.1f, 0.5f, 7.5f);	
		}
		else if (_isLeft == false )
		{
			_playerboom->fire(_position.x, _position.y, 1.14f, 0.5f, 7.5f);
		}	
	}
	if (_playerboom->GetPlayerBoomMax() <= 0)//�÷��̾� ����ź���� �����°� ó���� bulletŬ����boom���� ó���Ѵ� 
	{
		_playerboomFire = true;//true�� �Ǹ� ������������ 
	}
	
	_playerbullet->move();//�÷��̾� �Ѿ��� �׽� �����̰� 
	_playerboom->move();//�÷��̾� ��ź�� �׽� �����δ�  

	this->UpdateRectByPivot();//��Ʈ�� �ٽñ׷��ִ°� �� ������Ʈ���� �׽ÿ����Ϸ���  
	PlayerLeftSword = RectMake(_rc.left-20 , _rc.top , 20, 20);//�Ⱥ������� ���� �ֶ��浹�Ǹ� weaponstate�� Į�ιٲ��
	PlayerRightSword = RectMake(_rc.right, _rc.top , 20, 20);//�Ⱥ������� ���� �ֶ��浹�Ǹ� weaponstate�� Į�ιٲ��

}

void Player::Render()
{
	Rectangle(getMemDC(), _rc);//�÷��̾� ��Ʈ �����ֱ� 
	_playerbullet->Render(); //bullet���� �޾Ƽ� �⺻�� �����ֱ� 
	_playerboom->Render();   //�÷��̾� ��ź �����ֱ� 
	
	//Rectangle(getMemDC(), PlayerLeftSword); //�����浹�Ǵ� ��Ʈ Ȯ�ο�
	//Rectangle(getMemDC(), PlayerRightSword);//�����浹�Ǵ� ��Ʈ Ȯ�ο�

	//==����ź���� Ȯ�ο� 
	//char str[256];
	//sprintf_s(str, "?=%d", _playerboom->GetPlayerBoomMax());
	//TextOut(getMemDC(), 100, 100, str, strlen(str));

	//�÷��̾� ����Ʈ����̰� �����浹Į�� true�ϋ��� �浹��ҵ带 �׷��ش�
	if (_playersword == PLAYERSWORD::LEFTATTACK &&PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealLeftSword);
	}
	//�÷��̾� ������ ����̰� �����浹Į�� true�ϋ��� �浹��ҵ带 �׷��ش�
	if (_playersword == PLAYERSWORD::RIGHTATTACK &&PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealRightSword);
	}

}



