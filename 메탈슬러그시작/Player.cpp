#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#define SPEED 6

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_jumppower = 0.0f;								//�÷��̾� ������ 
	_gravity = 0.0f;								//�÷��̾� �߷� 
	_isJump = false;								//���� �����ȵȻ��� 
	_playerboomFire = false;						//�÷��̾� ��ź���� false�ϋ��� ����ְ� true�Ͻ� ��ź���Ұ��ϴ� 
	_time = 0;										//�׻�update�ǰ� �غ�ӽŰǹ߻�� 4������ ������ �ֱ����Ͽ� 
	_count = 0;										//�غ�ӽŰ��� �߻������ count�� 4���Ǹ� fire�� false�� ����� ���Ͽ� 
	_hfire = false;									//Ű�� ������ true���ǰ� �غ�ӽŰ��� �߻簡�ȴ� 

													// ================= �÷��̾� �Ѿ� ============================= 
	_playerbullet = new Bullet("�÷��̾� �����Ѿ�");
	_playerbullet->Init("�÷��̾�/�⺻�Ѿ�.bmp", 25, 10, 1000, 800);

	// ================= �÷��̾� ��ź =============================
	_playerboom = new Boom("�÷��̾� ��ź");
	_playerboom->Init("�÷��̾�/����ź.bmp", 720, 89, 2,WINSIZEY);


	_bullet = BULLET::RIGHTFIRE;					//�÷��̾� ���ʻ��´� �����ʺ��� �Ѿ˽�»��� 
	_weapon = WEAPON::NORMAL;						//�÷��̾��� �⺻ �ѻ��´� ���ѻ����̴� 
	_sword = SWORD::RIGHTATTACK;					//Į�� �⺻������ �����ʸ�Ǹ������õǾ��ִ� 
	_state = STATE::IDLE;
	PlayerRealSwordState = false;					//��¥ �浹�� Į�� bool �� 
	SwordCount = 0;									//Į �p�ʵڿ� ���ְ��ҷ���  				
	_playerbulletfire = false;						//�Ѿ� �߻� ������?
	_frameCount = 0;								//������ ī��Ʈ �ʱ�ȭ
	_frameIndex = 0;								//������ �ε��� �ʱ�ȭ


													// ========================================== �÷��̾� �̹��� =======================================================
	IMAGEMANAGER->addFrameImage("�÷��̾��", "�÷��̾�/�÷��̾��.bmp", 800, 503, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾���Ѱ���", "�÷��̾�/�⺻���Ѱ���.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵�", "�÷��̾�/�÷��̾��̵�.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾������Ѱ���", "�÷��̾�/���⺻���Ѱ���.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�⺻����", "�÷��̾�/�÷��̾�⺻����.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��������", "�÷��̾�/�÷��̾��������.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��ޱ׷�", "�÷��̾�/�÷��̾��ޱ׷�.bmp", 800, 503, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��ޱ׷����̵�", "�÷��̾�/�÷��̾��ޱ׷����̵�.bmp", 1400, 503, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��ޱ׷�����", "�÷��̾�/�÷��̾��ޱ׷�����.bmp", 2000, 503, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��¿��̵��ϸ�����", "�÷��̾�/�÷��̾��¿��̵��ϸ�����.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵��ϸ����", "�÷��̾�/�÷��̾��̵��ϸ����.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾����������", "�÷��̾�/�÷��̾����������.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�", "�÷��̾�/�÷��̾��̵��ϸ鼭�����ϰ��������.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));//�߻��ϴ°� 
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
	SwordCount++;								//Į�浹������ �p�ʵڿ� �浹�ڽ� Ŀ�ִ� ���� 
	_time++;									//�غ�ӽŰǿ� time���� �׽� update 

												// ========================================================================
												// ####################### �÷��̾� �ȱ�(WALK) ##############################
												// ========================================================================
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//�÷��̾� ����Ű �������� 
	{
		_bullet = BULLET::LEFTFIRE;				//���ʻ��¿����� �Ѿ� �������� ������ 
												//_state = STATE::CROUCHWALK
												//�÷��̾� ������ 
		_isLeft = true;							//���ʴ����� isLeft�� true 
												//if (_isJump == true)
												//{
												//	_wstate = WALKSTATE::JUMPWALK;		//�÷��̾� ��ü ���� �����ȱ�(JUMPWALK)
												//	_state = STATE::JUMPWALK; 
												//	_position.x -= 3.0f; 
												//}
		if (_isJump == true)
		{
			if (_state == STATE::JUMP_SHOT)
			{
				_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMP_SHOT;
			}
			else
			{
				_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMPWALK;
			}
			_position.x -= 3.0f;
		}


		else if (_state == STATE::CROUCHWALK)
		{
			//_state = STATE::CROUCHWALK;
			_position.x -= 1.0f;
		}

		else
		{                                       //���� ���°� �̵��ϸ鼭 ��� ������ 
			if (_state == STATE::WALK_SHOT)
			{
				_wstate = WALKSTATE::WALK;
				_state = STATE::WALK_SHOT;      //���´� �̵��ϸ鼭 ��»��·� 
			}
			else
			{
				_wstate = WALKSTATE::WALK;      //�׷��������� �׳� �ȴ»��·� 
				_state = STATE::WALK;
			}
			_position.x -= 3.0f;
		}

		_angle = 3.14f;							//���Ȯ�ο�ޱ� ������ ����϶��� ������� ������ ����� upŰ ������ 
		_angle1 = -3.14f;						//����Ȯ�ο�ޱ� ������ �����϶��� �������� ������ �������Ѵ� �����ϰ� �Ʒ����鼭��
	}
	// �����ؾߴ�
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	//�÷��̾� ������Ű �������� 
	{
		if (_bullet != BULLET::UPFIRE)
			_bullet = BULLET::RIGHTFIRE;		//�����U���¿����� �Ѿ� ���������� ������ 
												//�÷��̾� ���������� ������ 
		_isLeft = false;						//������Ű������ isleft�� false 
		if (_isJump == true)
		{
			if (_state == STATE::JUMP_SHOT)
			{
				_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMP_SHOT;
			}
			else if (_state == STATE::JUMP)
			{
				_wstate = WALKSTATE::JUMPWALK;
				_state = STATE::JUMPWALK;
			}
			else if (_state == STATE::JUMPWALK_UPSHOT)
			{
				_wstate = WALKSTATE::JUMPWALK;
				_state = STATE::JUMPWALK_UPSHOT;
			}


			/*	_wstate = WALKSTATE::JUMPWALK;
			_state = STATE::JUMPWALK;*/
			_position.x += 3.0f;
		}
		else if (_state == STATE::CROUCHWALK)
		{
			_position.x += 1.0f;
		}
		//else if (_state == STATE::WALK_SHOT)
		//{
		//	_wstate= WALKSTATE::
		//}
		else//���� ���°� �ƴ϶�� 
		{
			if (_state == STATE::WALK_SHOT)
			{
				_wstate = WALKSTATE::WALK;
				_state = STATE::WALK_SHOT;
			}
			else
			{
				_wstate = WALKSTATE::WALK;
				_state = STATE::WALK;
			}
			_position.x += 3.0f;
		}
		//_wstate = WALKSTATE::WALK;				//�÷��̾� ���� �ȱ�(WALK)
		//	_state = STATE::WALK;
		_angle = 0.0f;							//�����ʱ����̴ϱ� ���angel=0�̴� 
		_angle1 = 0.0f;							//�����ʱ����̶� ������angle�� 0�̴� 
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))		//�÷��̾� ����Ű ���� ��
	{
		_isLeft = true;
		if (_isJump == false)
		{
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}
		else
		{
			_wstate = WALKSTATE::JUMPWALK;
			_state = STATE::JUMPWALK;
		}
		_frameIndex = 0;


	}
	// �����ؾߴ�
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))		//�÷��̾� ������Ű ���� �� 
	{
		_isLeft = false;
		if (_isJump == false)
		{
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}
		else
		{
			//���� ���������ϋ���
			_wstate = WALKSTATE::JUMPWALK;
			_state = STATE::JUMPWALK;
		}
		//_wstate = WALKSTATE::IDLE;				//�÷��̾� ���� �⺻(IDLE)
		//_state = STATE::IDLE;
		_frameIndex = -1; 						//������ �ε��� �ʱ�ȭ
	}

	// ========================================================================
	// ###################### �÷��̾� �Ʒ� ������ �� ############################
	// ========================================================================
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))		//�÷��̾� �Ʒ���Ű �������� 
	{
		//_bullet = BULLET::DOWNATTACK;			//�Ѿ� �ɾ� ��� ����
		//_wstate = WALKSTATE::CROUCH;			//�÷��̾� ���� �ɱ�(CROUCH)
		//_state = STATE::CROUCH;                 //�⺻���� �ɴ¸��


		_bullet = BULLET::DOWNATTACK;
		switch (_wstate)
		{
		case WALKSTATE::IDLE:
			_wstate = WALKSTATE::CROUCH;
			_state = STATE::CROUCH; //�����ִµ� �ɱ� 
			break;
		case WALKSTATE::WALK:                   //�ѽ�� ��ǿ��� �ٸ�������� ���糪�� 
			_wstate = WALKSTATE::CROUCH;
			_state = STATE::CROUCHWALK;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))		//�ɾ� �ִٰ� �Ͼ��
	{											//�÷��̾��� isLeft�� Ȯ�� �Ѿ� ���� �ʱ�ȭ
		if (_isLeft == true)
		{
			_bullet = BULLET::LEFTFIRE;
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}
		else
		{
			_bullet = BULLET::RIGHTFIRE;
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}

	}

	// ========================================================================
	// ###################### �÷��̾� �� ������ �� ############################
	// ========================================================================
	if (KEYMANAGER->isStayKeyDown(VK_UP))		//�÷��̾� upŰ�� ������ 
	{
		_bullet = BULLET::UPFIRE;				//���ʻ��¿����� �Ѿ� �������� ������ 


												//switch (_wstate)
												//{
												//case WALKSTATE::IDLE:
												//	_state = STATE::IDLE_UPSTARE;
												//	break;
												//case WALKSTATE::WALK:
												//	_state = STATE::WLAK_UPSTARE;
												//	break;
												//case WALKSTATE::JUMP:
												//	_state = STATE::JUMP_UPSTARE;
												//	break;
												//case WALKSTATE::JUMPWALK:
												//	_state = STATE::JUMPWALK_UPSTARE; 
												//	break;
												//
												//}

		if (_isLeft == true)					//���ʺ��������ÿ��� 
		{
			_angle -= 0.125f;
			if (_angle < PI / 2)
			{
				_angle = PI / 2;
			}
		}
		else
		{
			_angle += 0.125f;
			if (_angle > PI / 2)
			{
				_angle = PI / 2;
			}
		}
	}
	else {
		if (_isLeft == true)
		{
			_angle += 0.125f;
			if (_angle > 3.14f)
			{
				_angle = 3.14f;
			}
		}
		else
		{
			_angle -= 0.125f;
			if (_angle < 0)
			{
				_angle = 0.0f;
			}
		}
	}

	// ========================================================================
	// ###################### �÷��̾� ����(A) ������ �� #########################
	// ========================================================================

	if (KEYMANAGER->isOnceKeyDown('A'))//AŰ�� �������� 
	{
		_playerbulletfire = true;
		if (_isLeft)
		{
			_frameIndex = 0;
		}
		else {
			_frameIndex = -1;
		}

		switch (_weapon)
		{
			// =====================================================================
			// ########################### �÷��̾� ���� #############################
			// =====================================================================
		case WEAPON::NORMAL:

			// =====================================================================
			// ####################### �÷��̾� ��ü ���� #############################
			// =====================================================================
			switch (_wstate)
			{

			case WALKSTATE::IDLE:

				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::IDLE_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::IDLE_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::IDLE_UPSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::WALK:
				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::WALK_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::WALK_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::WALK_UPSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::JUMP:
				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::JUMP_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::JUMP_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::JUMP_UPSHOT;
					break;
				case BULLET::DOWNFIRE:
					_state = STATE::JUMP_DOWNSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::JUMPWALK:
				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::JUMPWALK_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::JUMPWALK_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::JUMPWALK_UPSHOT;
					break;
				case BULLET::DOWNFIRE:
					_state = STATE::JUMPWALK_DOWNSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::CROUCH:
				switch (_bullet)
				{
				case BULLET::DOWNATTACK:
					_state = STATE::CROUCHSHOT;
					break;
				}
				break;
			}

			break;


			// ���߿� �߰��Ͻø� ��

		case WEAPON::HEAVY:

			break;
		case WEAPON::SWORD:

			break;
		case WEAPON::GRENADE:

			break;
		default:
			break;
		}

	}

	// =======================================================================
	// ######################### ��� �ӽŰ� �߻� ##############################
	// =======================================================================
	// �ѹ��� 4�߾� �߻��Ѵ�.
	if (_hfire == true)
	{
		if (_time % 3 == 0) //0.03�ʸ��� �غ�ӽŰ��� �߻�ȴ� 
		{
			switch (_bullet)
			{
			case BULLET::LEFTFIRE://���ʸ� ���� ���ӽŰ� 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, PI, 5.5f);
				break;
			case BULLET::RIGHTFIRE://�����ʸ� ���� ���ӽŰ� 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10), 0, 5.5f);
				break;
			case BULLET::UPFIRE://�������鼭 �¸������°� 
				_playerbullet->fire(_position.x, _position.y, _angle, 5.5f);
				break;
			case BULLET::DOWNFIRE://���������ϋ� �Ʒ����鼭 ��°� 
				_playerbullet->fire(_position.x, _position.y, _angle1, 5.5f);
				break;
			case BULLET::DOWNATTACK://�׳� �ɾƼ� ��°� 
				_playerbullet->fire(_position.x, RND->range(_position.y + 10, _position.y + 30), _angle, 10.5f);
			case BULLET::IDLE:
				break;
			}
			_count++;//�߻�ǰ� count��� ������ 1�� ������Ų��
		}
	}
	if (_count == 4)//4�� �̴ٸ� �߻縦 ���ϰ��Ѵ�  
	{
		_hfire = false;
		_count = 0;//�ٽ� count�� 0�����ʱ�ȭ�Ѵ� 
	}

	// ========================================================================
	// ###################### �÷��̾� ����(S) ������ ��  #########################
	// ========================================================================
	if (KEYMANAGER->isOnceKeyDown('S') && _isJump == false)
	{
		_isJump = true;						//������ true���ǰ� 
		_jumppower = 10.5f;					//�������� 10.5
		_gravity = 0.5f;					//�߷°��� 0.5

											// �Ȱ� �����鼭 JUMP�� ������ WLAKJUMP
											// �׳� ������ JUMP
		_wstate = WALKSTATE::JUMP;
		_state = STATE::JUMP;

	}



	// ========================================================================
	// ###################### �÷��̾� ����(JUMP) ó�� ##########################
	// ========================================================================
	if (_isJump == true)
	{
		_position.y -= _jumppower;			//�÷��̾� y���� ��������ŭ ���ش�  
		_jumppower -= _gravity;				//�������� �߷°���ŭ ������ 

											// ------- ���� �� �Ʒ��� ������ -------
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{//�ɾ��ձ� �ɾƼ� ��� �ɾƼ� `` �ɾƼ� �̵� 
		 //�÷��̾� �Ѿ˹����� �Ʒ����̵ȴ� 
			_bullet = BULLET::DOWNFIRE;

			if (_isLeft == true)
			{
				_angle1 += 0.125f;
				if (_angle1 > -(PI / 2))
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
	//�������°� �ƴϰ� �Ѿ˹����� �Ʒ����ϋ��� 
	//�Ѿ˹����� �ƹ��͵� �ȳ����� ���ƇJ�� 
	if (_isJump == false && _bullet == BULLET::DOWNFIRE)
	{
		_bullet = BULLET::IDLE;
	}
	// ========================================================
	if (_position.y > 400 && _isJump == true)		//�÷��̾� ������ 400���� Ŀ���� 
	{
		_isJump = false;		//�������´� false�� �ٱ��ش� 
		_wstate = WALKSTATE::IDLE;
		_state = STATE::IDLE;
	}
	// ========================================================




	//================================================Į�浹������=========================
	//RECT temp;
	//if (IntersectRect(&temp, &PlayerRightSword,
	//	&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "����")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "����")->GetActive())
	//{//�÷��̾�� �����ʷ�Ʈ�� ��Ÿ�� �浹������ Į���¸� �ҵ�� �ٱ��ش� 
	//	_weapon = WEAPON::SWORD;
	//	_sword = SWORD::RIGHTATTACK;
	//}
	//else if (IntersectRect(&temp, &PlayerLeftSword,
	//	&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "����")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "����")->GetActive())
	//{//�÷��̾�� ���ʷ�Ʈ�� ��Ÿ�� �浹������ Į���¸� �ҵ�� �ٱ��ش� 
	//	_weapon = WEAPON::SWORD;
	//	_sword = SWORD::LEFTATTACK;
	//}
	//else
	//{//���߿� ����� ����� �ٱ��ٲ��� 
	//	_weapon = WEAPON::NORMAL;
	//}
	//if (SwordCount % 100 == 0)//Į����̳����� 1�ʵڿ� false�ιٱ� �Ⱥ��̰��ҷ��� 
	//{
	//	PlayerRealSwordState = false;
	//}


	if (KEYMANAGER->isOnceKeyDown('D') && _playerboomFire == false)//boomfire�� false�϶��� ����ź���������ִ� 
	{
		//���࿡ ����ź�� �ٴ��̶� �浹�ϸ�
		if (_isLeft == true)
		{
			_playerboom->fire(_position.x, _position.y, PI - 1.1f, 0.5f, 7.5f);
		}
		else
		{
			_playerboom->fire(_position.x, _position.y, 1.14f, 0.5f, 7.5f);
		}
	}
	if (_playerboom->GetPlayerBoomMax() <= 0)//�÷��̾� ����ź���� �����°� ó���� bulletŬ����boom���� ó���Ѵ� 
	{
		_playerboomFire = true;//true�� �Ǹ� ������������ 
	}




	this->UpdateRectByPivot();//��Ʈ�� �ٽñ׷��ִ°� �� ������Ʈ���� �׽ÿ����Ϸ���  


							  //PlayerLeftSword = RectMake(_rc.left - 20, _rc.top, 20, 20);//�Ⱥ������� ���� �ֶ��浹�Ǹ� weaponstate�� Į�ιٲ��
							  //PlayerRightSword = RectMake(_rc.right, _rc.top, 20, 20);//�Ⱥ������� ���� �ֶ��浹�Ǹ� weaponstate�� Į�ιٲ��


							  //==============�̹���
	this->PlayerMotionState();
	this->PlayerBulletMotion();
	_playerbullet->move();//�÷��̾� �Ѿ��� �׽� �����̰� 
	_playerboom->move();//�÷��̾� ��ź�� �׽� �����δ�  
}
// =====================================================================================================================================
// ####################################################### �÷��̾� Render ##############################################################
// =====================================================================================================================================
void Player::Render()
{
	Rectangle(getMemDC(), CAMERA->Relative(_rc));//�÷��̾� ��Ʈ �����ֱ� 
	_playerbullet->Render(); //bullet���� �޾Ƽ� �⺻�� �����ֱ� 

	_playerboom->Render();   //�÷��̾� ��ź �����ֱ� 

							 //Rectangle(getMemDC(), PlayerLeftSword); //�����浹�Ǵ� ��Ʈ Ȯ�ο�
							 //Rectangle(getMemDC(), PlayerRightSword);//�����浹�Ǵ� ��Ʈ Ȯ�ο�

							 //==����ź���� Ȯ�ο� 
							 //char str[256];
							 //sprintf_s(str, "?=%d", _playerboom->GetPlayerBoomMax());
							 //TextOut(getMemDC(), 100, 100, str, strlen(str));

							 //�÷��̾� ����Ʈ����̰� �����浹Į�� true�ϋ��� �浹��ҵ带 �׷��ش�
	if (_sword == SWORD::LEFTATTACK && PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealLeftSword);
	}
	//�÷��̾� ������ ����̰� �����浹Į�� true�ϋ��� �浹��ҵ带 �׷��ش�
	if (_sword == SWORD::RIGHTATTACK && PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealRightSword);
	}

	//===================�̹���============================================
	switch (_state)
	{
	case Player::STATE::IDLE:
		IMAGEMANAGER->frameRender("�÷��̾��", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::WALK:
		IMAGEMANAGER->frameRender("�÷��̾��̵�", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::IDLE_SHOT:
		IMAGEMANAGER->frameRender("�÷��̾���Ѱ���", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::IDLE_UPSHOT:
		IMAGEMANAGER->frameRender("�÷��̾������Ѱ���", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMP:
		IMAGEMANAGER->frameRender("�÷��̾�⺻����", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::IDLE_UPSTARE:
		IMAGEMANAGER->frameRender("�÷��̾��������", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::CROUCH:
		IMAGEMANAGER->frameRender("�÷��̾��ޱ׷�", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::CROUCHWALK:
		IMAGEMANAGER->frameRender("�÷��̾��ޱ׷����̵�", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::CROUCHSHOT:
		IMAGEMANAGER->frameRender("�÷��̾��ޱ׷�����", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMPWALK:
		IMAGEMANAGER->frameRender("�÷��̾��¿��̵��ϸ�����", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::WALK_SHOT:
		IMAGEMANAGER->frameRender("�÷��̾��̵��ϸ����", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMP_SHOT:
		IMAGEMANAGER->frameRender("�÷��̾����������", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMPWALK_UPSHOT:
		IMAGEMANAGER->frameRender("�÷��̾��̵��ϸ鼭�����ϰ������߻�", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	}
	// =====================================================================

	//====================����׿� ���ÿ뵵�� Ȯ��=============================
	//if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
	//	if (_weapon == WEAPON::NORMAL)
	//	{
	//		_weapon = WEAPON::HEAVY;
	//	}
	//	else {
	//		_weapon = WEAPON::NORMAL;
	//	}
	//}
	// =====================================================================
}

// =====================================================================================================================================
// ###################################################### �÷��̾� ��� ó�� ##############################################################
// =====================================================================================================================================
void Player::PlayerMotionState()
{
	switch (_state)
	{
	case STATE::IDLE:
		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾��")->setFrameY(0);
			if (_frameCount % SPEED == 0) {
				_frameIndex++;
				if (_frameIndex > 3) {
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("�÷��̾��")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾��")->setFrameY(1);
			if (_frameCount % SPEED == 0) {
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 3;
				}

				IMAGEMANAGER->findImage("�÷��̾��")->setFrameX(_frameIndex);
			}
		}
		//�÷��̾��̵��ϸ鼭�����ϰ������߻�
		break;
	case STATE::WALK:
		IMAGEMANAGER->findImage("�÷��̾��̵�")->setFrameY(0);
		_frameCount++;
		if (!_isLeft) {
			if (_frameCount % SPEED == 0) {
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 0;
				}
				IMAGEMANAGER->findImage("�÷��̾��̵�")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾��̵�")->setFrameY(1);
			if (_frameCount % SPEED == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("�÷��̾��̵�")->setFrameX(_frameIndex);
			}
		}
		break;
	case STATE::JUMP:
		IMAGEMANAGER->findImage("�÷��̾�⺻����")->setFrameY(0);
		_frameCount++;
		if (!_isLeft)
		{
			if (_frameCount % 10 == 0) {
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("�÷��̾�⺻����")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾�⺻����")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("�÷��̾�⺻����")->setFrameX(_frameIndex);
			}
		}
		break;
	case STATE::IDLE_UPSTARE:

		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾��������")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("�÷��̾��������")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾��������")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("�÷��̾��������")->setFrameX(_frameIndex);
			}
		}

		break;
		//�÷��̾��ޱ׷�
	case STATE::CROUCH:

		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾��ޱ׷�")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 3)
				{
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("�÷��̾��ޱ׷�")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾��ޱ׷�")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 3;
				}

				IMAGEMANAGER->findImage("�÷��̾��ޱ׷�")->setFrameX(_frameIndex);
			}
		}
		break;

		//	�÷��̾��ޱ׷����̵�
	case STATE::CROUCHWALK:

		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("�÷��̾��ޱ׷����̵�")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 7)
				{
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("�÷��̾��ޱ׷����̵�")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("�÷��̾��ޱ׷����̵�")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 7;
				}

				IMAGEMANAGER->findImage("�÷��̾��ޱ׷����̵�")->setFrameX(_frameIndex);
			}
		}
		break;
		//�÷��̾��¿��̵��ϸ�����
	case STATE::JUMPWALK:
		_frameCount++;
		if (_isLeft == false)
		{
			IMAGEMANAGER->findImage("�÷��̾��¿��̵��ϸ�����")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 0;
				}
				IMAGEMANAGER->findImage("�÷��̾��¿��̵��ϸ�����")->setFrameX(_frameIndex);
			}
		}//�÷��̾��̵��ϸ鼭�����ϰ������߻�
		else
		{
			IMAGEMANAGER->findImage("�÷��̾��¿��̵��ϸ�����")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("�÷��̾��ޱ׷����̵�")->setFrameX(_frameIndex);
			}
		}
		break;
		//�÷��̾��̵��ϸ����
	default:
		break;
	}
}


// =====================================================================================================================================
// ###################################################### �÷��̾� (����)��� ó�� ########################################################
// =====================================================================================================================================
void Player::PlayerBulletMotion()
{
	// A(����) ������ ��
	if (_playerbulletfire == true)
	{
		switch (_weapon)
		{
		case WEAPON::NORMAL:
			switch (_bullet)
			{
			case BULLET::RIGHTFIRE:
				switch (_wstate)
				{
				case WALKSTATE::WALK:
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ����")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ����")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, 0, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
						break;
					}
					break;
				case WALKSTATE::IDLE:
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾���Ѱ���")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{

							_frameIndex++;
							if (_frameIndex  >5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾���Ѱ���")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, 0, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}break;
					//============����=====================
				case WALKSTATE::JUMP:
					_frameCount++;
					{
						if (_isLeft == false)
						{
							IMAGEMANAGER->findImage("�÷��̾����������")->setFrameY(0);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex++;
								if (_frameIndex > 5)
								{
									_frameIndex = 0;
								}
								IMAGEMANAGER->findImage("�÷��̾����������")->setFrameX(_frameIndex);
								if (_frameIndex == 0)
								{
									_playerbullet->fire(_position.x, _position.y, 0, 12.5f);
								}
								if (_frameIndex == 5)
								{
									_state = STATE::IDLE;
									_playerbulletfire = false;
								}
							}
							break;
						}
					}
					break;
				}
				break;
			case BULLET::LEFTFIRE:
				switch (_wstate)
				{
				case WALKSTATE::IDLE:
					_frameCount++;
					IMAGEMANAGER->findImage("�÷��̾���Ѱ���")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("�÷��̾���Ѱ���")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerbullet->fire(_position.x, _position.y, PI, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;
						}
					}
					break;
				case WALKSTATE::WALK:
					_frameCount--;
					if (_isLeft == true)
					{
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ����")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ����")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}

					}
					break;

				case WALKSTATE::JUMP:
					_frameCount--;
					if (_isLeft == true)
					{
						IMAGEMANAGER->findImage("�÷��̾����������")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾����������")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					break;
				}
				break;
			case BULLET::UPFIRE://���� 
				switch (_wstate)
				{
				case WALKSTATE::IDLE:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾������Ѱ���")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾������Ѱ���")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else//���ʸ��
					{

						if (_frameCount % SPEED == 0)
						{
							IMAGEMANAGER->findImage("�÷��̾������Ѱ���")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾������Ѱ���")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}



					break;

				case WALKSTATE::JUMPWALK:
					//���⼭ ���� �÷��̾��̵��ϸ鼭�����ϰ������߻�
					_frameCount++;
					IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameY(0);
					if (_isLeft == false)
					{
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::JUMPWALK;
								_playerbulletfire = false;
							}
						}
					}
				/*	else
					{
						_frameCount++; 
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5; 
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameX(_frameIndex);
                     	   
						}
					}*/




					break;



				}


				break;
			case BULLET::DOWNFIRE:
				_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 12.5f);
				break;
			case BULLET::DOWNATTACK://�÷��̾��ޱ׷�����
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("�÷��̾��ޱ׷�����")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 9)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("�÷��̾��ޱ׷�����")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerbullet->fire(_position.x, _position.y + 20, _angle, 12.5f);
						}
						if (_frameIndex == 9)
						{
							_state = STATE::CROUCH;
							_playerbulletfire = false;
						}
					}
				}
				else//���ʸ��
				{

					if (_frameCount % SPEED == 0)
					{
						IMAGEMANAGER->findImage("�÷��̾��ޱ׷�����")->setFrameY(1);
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 9;
						}
						IMAGEMANAGER->findImage("�÷��̾��ޱ׷�����")->setFrameX(_frameIndex);
						if (_frameIndex == 9)
						{
							_playerbullet->fire(_position.x, _position.y + 20, _angle, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::CROUCH;
							_playerbulletfire = false;
						}
					}
				}
				break;

				//_playerbullet->fire(_position.x, _position.y + 20, _angle, 12.5f);
			case BULLET::IDLE:
				break;
			}
			break;

		case WEAPON::HEAVY:
			_hfire = true;//fire�߻簡�Ǹ�  
			break;

		case WEAPON::SWORD:

			switch (_sword)
			{
			case SWORD::LEFTATTACK:
				PlayerRealSwordState = true;
				PlayerRealLeftSword = RectMakeCenter(_rc.left - 20, _rc.top - 10, 40, 40);
				break;
			case SWORD::RIGHTATTACK:
				PlayerRealSwordState = true;
				PlayerRealRightSword = RectMakeCenter(_rc.right, _rc.top - 10, 20, 20);
				break;
			}
			break;
		}
	}

}

void Player::Checkstate()
{
	switch (_bullet)
	{
	case BULLET::LEFTFIRE:
		break;
	case BULLET::RIGHTFIRE:
		break;
	case BULLET::UPFIRE:
		break;
	case BULLET::DOWNFIRE:
		break;
	case BULLET::DOWNATTACK:
		break;
	case BULLET::IDLE:
		break;
	default:
		break;
	}
}

void Player::PlayerBoomMotion()
{
	if (_boomfire == true)
	{
		switch (_weapon)
		{
		case WEAPON::NORMAL:
			switch (_wstate)
			{
			case WALKSTATE::IDLE:
				//�÷��̾������ź������
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("�÷��̾������ź������")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("�÷��̾������ź������")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x + 380, _position.y+ 100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}

					}
				}
				else
				{
					IMAGEMANAGER->findImage("�÷��̾������ź������")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("�÷��̾������ź������")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x+360, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
				}
				break;
			case WALKSTATE::WALK:
				//�÷��̾������ź
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("�÷��̾��̵�����ź")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("�÷��̾��̵�����ź")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x+380, _position.y+100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
					break;
				}
				else
				{
					IMAGEMANAGER->findImage("�÷��̾��̵�����ź")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("�÷��̾��̵�����ź")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x + 360, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
					break;
				}
				break;
			case WALKSTATE::JUMP:
				_frameCount++;

				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("�÷��̾����������ź")->setFrameY(0);

					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;

						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("�÷��̾����������ź")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x+380, _position.y+100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}

					}
				}
				else
				{
					IMAGEMANAGER->findImage("�÷��̾����������ź")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("�÷��̾����������ź")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x+360, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
				}
				break;
			case WALKSTATE::JUMPWALK:
				break;
			case WALKSTATE::CROUCH:
				break;
			default:
				break;
			}
			break;
		case WEAPON::HEAVY:
			switch (_wstate)
			{
			case WALKSTATE::IDLE:
				//�÷��̾������ź������
			
				break; 
			case WALKSTATE::JUMPWALK:
				break;
			case WALKSTATE::CROUCH:
				_frameCount++;

				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("�غ�ɾƼ�����ź")->setFrameY(0);

					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;

						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("�غ�ɾƼ�����ź")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x+370, _position.y+100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::CROUCH;
							_boomfire = false;
						}

					}
				}
				else
				{
					IMAGEMANAGER->findImage("�غ�ɾƼ�����ź")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("�غ�ɾƼ�����ź")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x+370, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::CROUCH;
							_boomfire = false;
						}
					}
				}
			//	�غ�ɾƼ�����ź


				break;
			default:
				break;
			}
			break;
		case WEAPON::SWORD:
			break;
		case WEAPON::GRENADE:
			break;
		default:
			break;
		}

		
	}

}



void Player::PixelMapCollision()
{
	//

	_pixely = _position.y + 190; //���Ⱑ �ִϸ��̼� �ǾƷ��κ� 
	
	for (int i = _pixely- 5; i < _pixely + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("����ȼ�")->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 255 && b == 0) && _jumppower <= 0)
		{
			_jumppower = 0.0f; 
			_position.y = i-190;
			

			if (_isJump)
			{
				_state = STATE::IDLE;
				_isJump = false;
			}
		
			break; 
		}
	}

}

void Player::EnemyCollision()      //�÷��̾� �⺻���� 
{
	RECT temp; 
	//for (int i = 0; i < _playerbullet->getVBullet().size(); i++)
	//{
	//	if(IntersectRect(&temp, &_playerbullet->getVBullet()[i].rc, &//���� ))
	//}
}

