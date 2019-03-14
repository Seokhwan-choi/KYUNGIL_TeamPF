#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "Crab.h"
#define SPEED 6

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_jumppower = 0.0f;								//�÷��̾� ������ 
	_gravity = 0.02;								//�÷��̾� �߷� 
	_isJump = false;								//���� �����ȵȻ��� 
	_playerboomFire = false;						//�÷��̾� ��ź���� false�ϋ��� ����ְ� true�Ͻ� ��ź���Ұ��ϴ� 
	_time = 0;										//�׻�update�ǰ� �غ�ӽŰǹ߻�� 4������ ������ �ֱ����Ͽ� 
	_count = 0;										//�غ�ӽŰ��� �߻������ count�� 4���Ǹ� fire�� false�� ����� ���Ͽ� 
	_hfire = false;									//Ű�� ������ true���ǰ� �غ�ӽŰ��� �߻簡�ȴ� 
	_crab = ((Crab*)OBJECTMANAGER->FindObject(ObjectType::ENEMY, "crab"));
	
	//###########################�÷��̾� �浹��Ʈ#################
	//collisionplayer = RectMakeCenter(_position.x, _position.y, 100, 100);


	// ================= �÷��̾� �Ѿ� ============================= 
	_playerbullet = new Bullet1("�÷��̾� �����Ѿ�");
	_playerbullet->Init(800);//�������̹��� range�Ÿ��� ���� 

	
	//===============�غ�ӽŰ� 
	_heavyBullet = new Bullet("�÷��̾� �غ�");
	_heavyBullet->Init(800);

	//====================�÷��̾� �ȼ�=============================
    _pixely = _position.y + 190;//�ǾƷ��� �÷��̾�y�� �浹��Ʈ 
	//_pixelx= _position.x + 
	//====================���� �÷��̾� ��Ʈ=========================

	// ================= �÷��̾� ��ź =============================
	_playerboom = new Boom("�÷��̾� ��ź");
	_playerboom->Init("�÷��̾�/����ź.bmp", 720, 89, 2,WINSIZEY);

	//_InterPlayerRc = RectMakeCenter(_position.x + 75, _position.y + 130, 60, 95);//�浹��Ʈ�� �׽ɿ����δ� 

	_bullet = BULLET::RIGHTFIRE;					//�÷��̾� ���ʻ��´� �����ʺ��� �Ѿ˽�»��� 
	//_weapon = WEAPON::NORMAL;
	_weapon = DATA->getWeapon();						//�÷��̾��� �⺻ �ѻ��´� ���ѻ����̴� 
	_sword = SWORD::RIGHTATTACK;					//Į�� �⺻������ �����ʸ�Ǹ������õǾ��ִ� 
	_state = STATE::IDLE;
	PlayerRealSwordState = false;					//��¥ �浹�� Į�� bool �� 
	SwordCount = 0;									//Į �p�ʵڿ� ���ְ��ҷ���  				
	_playerbulletfire = false;						//�Ѿ� �߻� ������?
	_frameCount = 0;								//������ ī��Ʈ �ʱ�ȭ
	_frameIndex = 0;								//������ �ε��� �ʱ�ȭ
	_isLeft = false;
	_normalangle = 0.0f; 
	_boomfire = false;                               //��ź �߻�̳�?
													// ========================================== �÷��̾� �̹��� =======================================================
	IMAGEMANAGER->addFrameImage("�÷��̾��", "�÷��̾�/�÷��̾��.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾���Ѱ���", "�÷��̾�/�⺻���Ѱ���.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵�", "�÷��̾�/�÷��̾��̵�.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾������Ѱ���", "�÷��̾�/���⺻���Ѱ���.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�⺻����", "�÷��̾�/�÷��̾�⺻����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��������", "�÷��̾�/�÷��̾��������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��ޱ׷�", "�÷��̾�/�÷��̾��ޱ׷�.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��ޱ׷����̵�", "�÷��̾�/�÷��̾��ޱ׷����̵�.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��ޱ׷�����", "�÷��̾�/�÷��̾��ޱ׷�����.bmp", 3200, 805, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��¿��̵��ϸ�����", "�÷��̾�/�÷��̾��¿��̵��ϸ�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵��ϸ����", "�÷��̾�/�÷��̾��̵��ϸ����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾����������", "�÷��̾�/�÷��̾����������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�", "�÷��̾�/�÷��̾��̵��ϸ鼭�����ϰ��������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));//�߻��ϴ°� 
	IMAGEMANAGER->addFrameImage("�÷��̾������ϸ鼭����","�÷��̾�/�÷��̾������ϸ鼭����.bmp", 1920, 805,6,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("�÷��̾�������������", "�÷��̾�/�÷��̾�������������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵��ϸ���������", "�÷��̾�/�÷��̾��̵��ϸ���������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾�������߾Ʒ�����", "�÷��̾�/�÷��̾�������߾Ʒ�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾��̵������߾Ʒ�����", "�÷��̾�/�÷��̾��̵������߾Ʒ�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
    
	//����ź
	IMAGEMANAGER->addFrameImage("�÷��̾��̵�����ź", "�÷��̾�/�÷��̾��̵�����ź.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾������ź������", "�÷��̾�/�÷��̾������ź������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�÷��̾����������ź", "�÷��̾�/�÷��̾����������ź.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));


	//�غ�ӽŰ�   // 160���� �����Ѵ� 
	IMAGEMANAGER->addFrameImage("�غ񰡸�", "�÷��̾�/�غ񰡸�.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));//�����Ⱦ� render�� �������� 
	IMAGEMANAGER->addFrameImage("�غ��̵��ϸ����", "�÷��̾�/�غ��̵��ϸ����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ񰡸���������", "�÷��̾�/�غ񰡸���������.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ񰡸�����", "�÷��̾�/�غ񰡸�����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ��̵���������", "�÷��̾�/�غ��̵���������.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ񰡸�����", "�÷��̾�/�غ񰡸�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ�Ʒ�����", "�÷��̾�/�غ�Ʒ�����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ�Ʒ�����", "�÷��̾�/�غ�Ʒ�����.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ�Ʒ��̵�", "�÷��̾�/�غ�Ʒ��̵�.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ��̵��ϸ�����", "�÷��̾�/�غ��̵��ϸ�����.bmp", 1600, 805, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ��̵�", "�÷��̾�/�غ��̵�.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ��̵�����", "�÷��̾�/�غ��̵�����.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ񰡸�����","�÷��̾�/�غ񰡸�����.bmp", 1920,805,6,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("�غ������", "�÷��̾�/�غ������.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�غ񰡸��Ʒ���������", "�÷��̾�/�غ񰡸��Ʒ���������.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ������߾Ʒ�������", "�÷��̾�/�غ������߾Ʒ�������.bmp", 1920, 402, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�غ�ɾƼ�����ź", "�÷��̾�/�غ�ɾƼ�����ź.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
     
	IMAGEMANAGER->addImage("���ϻ�", "�÷��̾�/���ϻ�.bmp", 320, 403, true, RGB(255, 0, 255));

	_lifelive = false; 

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
	//_playerboom->release();
	//SAFE_DELETE(_playerboom);
	//
	//_heavyBullet->release();
	//SAFE_DELETE(_heavyBullet);
	//
	//_playerbullet->release();
	//SAFE_DELETE(_playerbullet);
}
//�����������ϰ� walk_shot�� �ϸ� �̻� 
void Player::Update()
{
	
	if (_lifelive == false)
	{
		SwordCount++;								//Į�浹������ �p�ʵڿ� �浹�ڽ� Ŀ�ִ� ���� 
		_time++;									//�غ�ӽŰǿ� time���� �׽� update 

		//################���ϻ�#####################################
		//�÷��̾� ����߷� 
		_position.y -= _jumppower;
		_jumppower -= _gravity;



													// ========================================================================
													// ####################### �÷��̾� �ȱ�(WALK) ##############################
													// ========================================================================
	
		if (_state != STATE::FLY)
		{

			if (CAMERA->GetWall() > _rc.left   - 175 )
			{
				_position.x =   _position.x+ CAMERA->GetWall() - (_rc.left - 175);
			}



			if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//�÷��̾� ����Ű �������� 
			{
				//	_bullet = BULLET::LEFTFIRE;				//���ʻ��¿����� �Ѿ� �������� ������ 
															//_state = STATE::CROUCHWALK
															//�÷��̾� ������ 
				if (_bullet != BULLET::UPFIRE && _bullet != BULLET::DOWNFIRE)
					_bullet = BULLET::LEFTFIRE;
				// && _bullet != BULLET::DOWNFIRE)
						//�����U���¿����� �Ѿ� ���������� ������ 
			/*	else if (_bullet != BULLET::LEFTFIRE)
					_bullet = BULLET::DOWNFIRE;
				else if (_bullet != BULLET::DOWNFIRE)
					_bullet = BULLET::UPFIRE;*/

				_isLeft = true;							//���ʴ����� isLeft�� true 
														//if (_isJump == true)
														//{
														//	_wstate = WALKSTATE::JUMPWALK;		//�÷��̾� ��ü ���� �����ȱ�(JUMPWALK)
														//	_state = STATE::JUMPWALK; 
														//	_position.x -= 3.0f; 
														//}
				if (_isJump == true)
				{
					if (_state == STATE::JUMP_SHOT)                   //�����ϸ鼭 �ѽ��
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_SHOT;
					}
					else if (_state == STATE::JUMPWALK_UPSHOT)
					{
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK_UPSHOT;
					}
					else if (_state == STATE::JUMP)
					{
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK;
					}
					else if (_state == STATE::JUMPWALK) {
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK;
					}
					else if (_state == STATE::JUMP_DOWNSTARE)
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_DOWNSTARE;
					}
					//else if (_state == STATE::JUMP_UPSHOT)
					//{
					//	_wstate = WALKSTATE::JUMP;
					//	_state = STATE::JUMP_UPSHOT; //�����߿� ���� �����ϴ°�
					//}
					_position.x -= 3.0f;
				}


				else if (_state == STATE::CROUCHWALK)
				{
					//_state = STATE::CROUCHWALK;
					_position.x -= 1.0f;
				}
				else if (_state == STATE::CROUCHBOOM)
				{
					_wstate = WALKSTATE::CROUCH;
					_state = STATE::CROUCHBOOM;
				}

				else
				{                                       //���� ���°� �̵��ϸ鼭 ��� ������ 
					if (_state == STATE::WALK_SHOT)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_SHOT;      //���´� �̵��ϸ鼭 ��»��·� 
					}
					/*	else if (_state == STATE::WALK_UPSHOT )
						{
							_bullet = BULLET::UPFIRE;
							_angle = 3.14f;

							_angle -= 0.125f;
								if (_angle < PI / 2.0f)
								{
									_angle = PI / 2.0f;
								}
								if (_angle == PI / 2)
								{
									_wstate = WALKSTATE::IDLE;
									_state = STATE::WLAK_UPSTARE;
									_angle = PI / 2;
								}


							_wstate = WALKSTATE::WALK;
							_state = STATE::WALK_UPSHOT;


						}*/
					else if (_state == STATE::WALK_BOOM)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_BOOM;
					}
					else if (_state == STATE::WALK_UPSHOT)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_UPSHOT;
					}

					//if (_isLeft == true)					//���ʺ��������ÿ��� 
					//{
					//	_angle -= 0.125f;
					//	if (_angle < PI / 2.0f)
					//	{
					//		_angle = PI / 2.0f;
					//	}
					//	if (_angle == PI / 2)
					//	{
					//		_wstate = WALKSTATE::IDLE;
					//		_state = STATE::WLAK_UPSTARE;
					//		_angle = PI / 2;
					//	}

					//}

				/*	_angle -= 0.125f;
					if (_angle < PI / 2.0f)
					{
						_angle = PI / 2.0f;
					}
					if (_angle == PI / 2)
					{
						_wstate = WALKSTATE::IDLE;
						_state = STATE::WLAK_UPSTARE;
						_angle = PI / 2;
					}*/
					/*	else if (_state == STATE::JUMPWALK) {
							_wstate = WALKSTATE::JUMPWALK;
							_state = STATE::JUMPWALK;
						}*/
						/*	else if (_state == STATE::IDLE_BOOM)
							{
								_wstate = WALKSTATE::IDLE;
								_state = STATE::IDLE_BOOM;
							}*/

					else
					{
						_wstate = WALKSTATE::WALK;      //�׷��������� �׳� �ȴ»��·� 
						_state = STATE::WALK;
					}
					_position.x -= 3.0f;
				}
				if (_state == STATE::WALK_UPSHOT)
				{
					//_angle -= 0.5f;
					_wstate = WALKSTATE::WALK;
					_state = STATE::WALK_UPSHOT;
				}
				else if (_state == STATE::JUMPWALK_DOWNSHOT)
				{
					_wstate = WALKSTATE::JUMPWALK;
					_state = STATE::JUMPWALK_DOWNSHOT;
				}
				else
				{
					_angle = 3.14f;							//���Ȯ�ο�ޱ� ������ ����϶��� ������� ������ ����� upŰ ������ 
					_angle1 = -3.14f;						//����Ȯ�ο�ޱ� ������ �����϶��� �������� ������ �������Ѵ� �����ϰ� �Ʒ����鼭��
				}
				_normalangle = PI;
			}
			// �����ؾߴ�

			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	//�÷��̾� ������Ű �������� 
			{

				_normalangle = 0.0f;
				if (_bullet != BULLET::UPFIRE && _bullet != BULLET::DOWNFIRE)
					_bullet = BULLET::RIGHTFIRE;		//�����U���¿����� �Ѿ� ���������� ������ 
														//�÷��̾� ���������� ������ 
			/*	if (_bullet == BULLET::UPFIRE)
				{
					_bullet = BULLET::UPFIRE
				}
				else if (_bullet == BULLET::DOWNFIRE)
				{
					_bullet = BULLET::DOWNFIRE;
				}*/
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
					else if (_state == STATE::JUMPWALK) {
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK;
					}
					else if (_state == STATE::JUMPWALK_UPSHOT)
					{
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK_UPSHOT;
					}
					else if (_state == STATE::JUMP_DOWNSTARE)
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_DOWNSTARE;
					}
					/*else if (_state == STATE::JUMP_UPSHOT)
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_UPSHOT;
					}*/
					//else if (_state == STATE::JUMP_UPSHOT)
					//{
					//	_wstate = WALKSTATE::JUMP;
					//	_state = STATE::JUMP_UPSHOT; //�����߿� ���� �����ϴ°�
					//}


					/*	_wstate = WALKSTATE::JUMPWALK;
					_state = STATE::JUMPWALK;*/
					_position.x += 13.0f;
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
					else if (_state == STATE::WALK_UPSHOT)
					{


						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_UPSHOT;
					}
					else if (_state == STATE::WALK_BOOM)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_BOOM;
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
				if (_state == STATE::WALK_UPSHOT)
				{
					_wstate = WALKSTATE::WALK;
					_state = STATE::WALK_UPSHOT;
					//_angle -= 0.5f;
					//�ƹ��͵��Ⱦ��� 
					//�̰� ��ü�� bullet up���´ϱ� ���Ⱑ �ڵ����� �����Ǵϱ� 
				}
				else if (_state == STATE::JUMPWALK_DOWNSHOT)
				{
					_wstate = WALKSTATE::JUMPWALK;
					_state = STATE::JUMPWALK_DOWNSHOT;
				}
				else
				{
					_angle = 0.0f;							//�����ʱ����̴ϱ� ���angel=0�̴� 
					_angle1 = 0.0f;							//�����ʱ����̶� ������angle�� 0�̴� 
				}

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
				_frameIndex = -1; 							//������ �ε��� �ʱ�ȭ
			}

			// ========================================================================
			// ###################### �÷��̾� �Ʒ� ������ �� ############################
			// ========================================================================
			if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _isJump == false)		//�÷��̾� �Ʒ���Ű �������� 
			{
				//_normalangle = PI + PI / 2;

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
			if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _isJump == false)		//�ɾ� �ִٰ� �Ͼ��
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


				//if (_state == STATE::IDLE_UPSHOT ) 
				//{
				//	/*_wstate = WALKSTATE::IDLE;
				//	_state = STATE::IDLE_UPSHOT;*/
				//}
				switch (_weapon)
				{
				case WEAPON::NORMAL:
					if (_state == STATE::IDLE_UPSHOT)
					{
						_wstate = WALKSTATE::IDLE;
						_state = STATE::IDLE_UPSHOT;
					}
					break;
				case WEAPON::HEAVY:
					if (_state == STATE::IDLE_UPSHOT)
					{
						_wstate = WALKSTATE::IDLE;
						_state = STATE::WLAK_UPSTARE;
					}
					break;

				default:
					break;
				}

				_normalangle = PI / 2;
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
					if (_angle < PI / 2.0f)
					{
						_angle = PI / 2.0f;
					}
					if (_angle == PI / 2)
					{
						//_wstate = WALKSTATE::IDLE;
						//_state = STATE::WLAK_UPSTARE;
						_angle = PI / 2;
					}

				}
				else
				{
					_angle += 0.125f;
					if (_angle > PI / 2.0f)
					{
						_angle = PI / 2.0f;
					}
					if (_angle == PI / 2)
					{
						//_wstate = WALKSTATE::IDLE;
						//_state = STATE::WLAK_UPSTARE;
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
					if (_angle < 0.0f)
					{
						_angle = 0.0f;
					}
				}
			}
			if (KEYMANAGER->isOnceKeyUp(VK_UP))		//�÷��̾� upŰ�� ������ 
			{
				_bullet = BULLET::IDLE;
				_wstate = WALKSTATE::IDLE;
				_state = STATE::IDLE;
			}
			// ========================================================================
			// ###################### �÷��̾� ����(A) ������ �� #########################
			// ========================================================================
			if (KEYMANAGER->isOnceKeyDown('A'))//AŰ�� �������� 
			{
				_playerbulletfire = true;// ������ �����ϰٴ� 
				if (_weapon == WEAPON::HEAVY)
				{
					_hfire = true;
				}

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
						_heavyBullet->fire(_position.x + 530, RND->range(_position.y +146, _position.y + 166) /*_position.y*/, _angle, 12.5f);  //20������ ���� 
						break;
					case BULLET::RIGHTFIRE://�����ʸ� ���� ���ӽŰ� 
						_heavyBullet->fire(_position.x + 900, RND->range(_position.y +146, _position.y+166 ), _angle, 12.5f);
						break;
					case BULLET::UPFIRE://�������鼭 �¸������°� 

						switch (_state)
						{
						case STATE::WALK_UPSHOT:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 675, _position.x +695), _position.y+100 , _angle, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 695, _position.x + 715), _position.y+100 , _angle, 12.5f);
							}
							break;
						case STATE::WLAK_UPSTARE:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 695, _position.x + 715), _position.y-15 , _angle, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 690, _position.x + 710), _position.y-15, _angle, 12.5f);
							}
							break;
						}

						break;
					case BULLET::DOWNFIRE://���������ϋ� �Ʒ����鼭 ��°� 
						switch (_state)
						{
						case STATE::JUMP_DOWNSHOT:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 675, _position.x + 695), _position.y + 270, _angle1, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 700, _position.x + 720), _position.y + 270, _angle1, 12.5f);
							}
							break;
						case STATE::JUMPWALK_DOWNSHOT:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 675, _position.x + 695), _position.y + 270, _angle1, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 700, _position.x + 720), _position.y + 270, _angle1, 12.5f);
							}
							break;
						}

						break;
					case BULLET::DOWNATTACK://�׳� �ɾƼ� ��°� 

						if (!_isLeft)
						{
							_heavyBullet->fire(_position.x + 890, RND->range(_position.y + 160, _position.y+180 ), _angle, 12.5f);
						}
						else {
							_heavyBullet->fire(_position.x + 510, RND->range(_position.y + 160, _position.y+180 ), _angle, 12.5f);
						}
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
				_gravity = 0.3f;					//�߷°��� 0.5

													// �Ȱ� �����鼭 JUMP�� ������ WLAKJUMP
													// �׳� ������ JUMP




				if (_wstate != WALKSTATE::JUMPWALK)
					_wstate = WALKSTATE::JUMP;

				//	_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMP;

				//_wstate = WALKSTATE::JUMPWALK;
				//_state = STATE::JUMPWALK_DOWNSHOT;

			}



			// ========================================================================
			// ###################### �÷��̾� ����(JUMP) ó�� ##########################
			// ========================================================================
			if (_isJump == true)
			{
				_position.y -= _jumppower;			//�÷��̾� y���� ��������ŭ ���ش�  
				_jumppower -= _gravity;				//�������� �߷°���ŭ ������ 

				//	_wstate = WALKSTATE::JUMP; 
				//_state = STATE::JUMP_UPSHOT;

													// ------- ���� �� �Ʒ��� ������ -------
				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{//�ɾ��ձ� �ɾƼ� ��� �ɾƼ� `` �ɾƼ� �̵� 
				 //�÷��̾� �Ѿ˹����� �Ʒ����̵ȴ� 
					_bullet = BULLET::DOWNFIRE;

					if (_state == STATE::JUMPWALK_DOWNSHOT)
					{
						_state = STATE::JUMPWALK_DOWNSHOT;
						_wstate = WALKSTATE::JUMPWALK;
					}
					else if (_state == STATE::JUMP_DOWNSHOT)

					{
						_state = STATE::JUMP_DOWNSHOT;
						_wstate = WALKSTATE::JUMP;
					}
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
			//**********************�ȼ� 

			//if (_position.y > 400 && _isJump == true)		//�÷��̾� ������ 400���� Ŀ���� 
			//{
			//	_isJump = false;		//�������´� false�� �ٱ��ش� 
			//	_wstate = WALKSTATE::IDLE;
			//	_state = STATE::IDLE;
			//}
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
				_boomfire = true;
				if (_isLeft)
				{
					_frameIndex = 0;
				}
				else {
					_frameIndex = -1;
				}
				//���࿡ ����ź�� �ٴ��̶� �浹�ϸ�
				/*if (_isLeft == true)
				{
					_playerboom->fire(_position.x, _position.y, PI - 1.1f, 0.5f, 7.5f);
				}
				else
				{
					_playerboom->fire(_position.x, _position.y, 1.14f, 0.5f, 7.5f);
				}
		*///�غ�ɾƼ�����ź
				switch (_weapon)
				{
				case WEAPON::NORMAL:
					switch (_wstate)
					{
					case WALKSTATE::IDLE:
						_state = STATE::IDLE_BOOM;
						break;
					case WALKSTATE::WALK:
						_state = STATE::WALK_BOOM;
						break;
					case WALKSTATE::JUMP:
						_state = STATE::JUMP_BOOM;
						break;
					case WALKSTATE::JUMPWALK:
						_state = STATE::JUMPWALK_BOOM;
						break;
					case WALKSTATE::CROUCH:
						_state = STATE::CROUCHBOOM;

						break;
					default:
						break;
					}
					break;
				case WEAPON::HEAVY:
					switch (_wstate)
					{
					case WALKSTATE::IDLE:
						_state = STATE::IDLE_BOOM;
						break;
					case WALKSTATE::WALK:
						_state = STATE::WALK_BOOM;
						break;
					case WALKSTATE::JUMP:
						_state = STATE::JUMP_BOOM;
						break;
					case WALKSTATE::JUMPWALK:
						_state = STATE::JUMPWALK_BOOM;
						break;
					case WALKSTATE::CROUCH:
						_state = STATE::CROUCHBOOM;

						break;
					default:
						break;
					}
					break;
				case WEAPON::SWORD:
					break;
				case WEAPON::GRENADE:
					break;

				}


			}

		}
		if (_playerboom->GetPlayerBoomMax() <= 0)//�÷��̾� ����ź���� �����°� ó���� bulletŬ����boom���� ó���Ѵ� 
		{
			_playerboomFire = true;//true�� �Ǹ� ������������ 
		}


		check = RectMakeCenter(_position.x, _position.y + 52, 30, 30);
		this->UpdateRectByPivot();//��Ʈ�� �ٽñ׷��ִ°� �� ������Ʈ���� �׽ÿ����Ϸ���  


								  //PlayerLeftSword = RectMake(_rc.left - 20, _rc.top, 20, 20);//�Ⱥ������� ���� �ֶ��浹�Ǹ� weaponstate�� Į�ιٲ��
								  //PlayerRightSword = RectMake(_rc.right, _rc.top, 20, 20);//�Ⱥ������� ���� �ֶ��浹�Ǹ� weaponstate�� Į�ιٲ��


								  //==============�̹���
		this->PlayerMotionState();
		this->PlayerBulletMotion();
		this->PlayerBoomMotion();
		this->PixelMapCollision();
		_playerbullet->move();//�÷��̾� �Ѿ��� �׽� �����̰� 
		// ó������ _playerboom->move() ����.
		// �ε��� ���ϴ°� Update()�� �־
		// ��ź�� �Ѱ��� ������θ� ������.
		_playerboom->Update();//�÷��̾� ��ź�� �׽� �����δ�  
		_heavyBullet->move();
		collisionplayer = RectMakeCenter(_position.x, _position.y+40, 100, 130);
		_colb = RectMakeCenter(_position.x, _position.y + _size.y / 2 - 100, 10, 10);
		_colr = RectMakeCenter(_position.x + _size.x / 2 - 120, _position.y + 35, 10, 10);
		//�÷��̾� �浹��Ʈ�� �׽ɿ����δ� 
		//_InterPlayerRc = RectMakeCenter(_position.x+75, _position.y+130, 60, 95);//�浹��Ʈ�� �׽ɿ����δ� 

	}
	
//	_temp = RectMakeCenter(_InterPlayerRc.left + 75, _InterPlayerRc.bottom, 15, 15);
}
// ====================================================================================================================================
// ####################################################### �÷��̾� Render ##############################################################
// =====================================================================================================================================
void Player::Render()
{
	if (_lifelive == false)
	{
		RECT playerRC = CAMERA->Relative(_rc);
		RECT CHEK = CAMERA->Relative(check);
		
		RECT playercehck= CAMERA->Relative(collisionplayer);
		Rectangle(getMemDC(), CHEK);
		Rectangle(getMemDC(), CAMERA->Relative(_colb));
		Rectangle(getMemDC(), CAMERA->Relative(_colr));
		//�÷��̾� �浹��Ʈ 
		Rectangle(getMemDC(), playercehck);


		//RECT interplayerrc= CAMERA->Relative(_InterPlayerRc);

		FrameRect(getMemDC(), &playerRC, HBRUSH(RGB(255, 0, 0)));
		
		
		//collisionplayer = RectMakeCenter(_position.x, _position.y, 100, 100);

		//FrameRect(getMemDC(), &CAMERA->Relative(_temp), HBRUSH(RGB(255, 0, 0)));
		_playerbullet->Render(); //bullet���� �޾Ƽ� �⺻�� �����ֱ� 
		_heavyBullet->Render(); //�غ�ӽŰ� 

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
		switch (_weapon)
		{
		case WEAPON::NORMAL:
			switch (_state)
			{
			case Player::STATE::IDLE:
				IMAGEMANAGER->frameRender("�÷��̾��", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK:
				//IMAGEMANAGER->frameRender("�÷��̾��̵�", getMemDC(), playerRC.left, playerRC.top);
				IMAGEMANAGER->frameRender("�÷��̾��̵�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_SHOT:
				IMAGEMANAGER->frameRender("�÷��̾���Ѱ���", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_UPSHOT:
				IMAGEMANAGER->frameRender("�÷��̾������Ѱ���", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP:
				IMAGEMANAGER->frameRender("�÷��̾�⺻����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_UPSTARE:
				IMAGEMANAGER->frameRender("�÷��̾��������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCH:
				IMAGEMANAGER->frameRender("�÷��̾��ޱ׷�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHWALK:
				IMAGEMANAGER->frameRender("�÷��̾��ޱ׷����̵�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHSHOT:
				IMAGEMANAGER->frameRender("�÷��̾��ޱ׷�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK:
				IMAGEMANAGER->frameRender("�÷��̾��¿��̵��ϸ�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_SHOT:
				IMAGEMANAGER->frameRender("�÷��̾��̵��ϸ����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_SHOT:
				IMAGEMANAGER->frameRender("�÷��̾����������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_UPSHOT:
				IMAGEMANAGER->frameRender("�÷��̾��̵��ϸ鼭�����ϰ������߻�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_SHOT:
				IMAGEMANAGER->frameRender("�÷��̾������ϸ鼭����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_UPSHOT:
				IMAGEMANAGER->frameRender("�÷��̾�������������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_UPSHOT:
				IMAGEMANAGER->frameRender("�÷��̾��̵��ϸ���������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_DOWNSHOT:
				IMAGEMANAGER->frameRender("�÷��̾�������߾Ʒ�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_DOWNSHOT:
				IMAGEMANAGER->frameRender("�÷��̾��̵������߾Ʒ�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::FLY:
				IMAGEMANAGER->render("���ϻ�",getMemDC(),playerRC.left, playerRC.top);
				break; 

				//����ź +++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			case STATE::WALK_BOOM:
				IMAGEMANAGER->frameRender("�÷��̾��̵�����ź", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_BOOM:
				IMAGEMANAGER->frameRender("�÷��̾������ź������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_BOOM:
				IMAGEMANAGER->frameRender("�÷��̾����������ź", getMemDC(), playerRC.left, playerRC.top);
				break;

			}
			break;
		case WEAPON::HEAVY:
			/*�غ��̵��ϸ����
			�غ񰡸�*/
			switch (_state)
			{
			case STATE::IDLE_SHOT:
				IMAGEMANAGER->frameRender("�غ񰡸�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE:
				IMAGEMANAGER->frameRender("�غ񰡸�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_SHOT:
				IMAGEMANAGER->frameRender("�غ��̵��ϸ����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_SHOT:
				IMAGEMANAGER->frameRender("�غ񰡸���������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_SHOT:
				IMAGEMANAGER->frameRender("�غ��̵���������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP:
				IMAGEMANAGER->frameRender("�غ񰡸�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHSHOT:
				IMAGEMANAGER->frameRender("�غ�Ʒ�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCH:
				IMAGEMANAGER->frameRender("�غ�Ʒ�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHWALK:
				IMAGEMANAGER->frameRender("�غ�Ʒ��̵�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK:
				IMAGEMANAGER->frameRender("�غ��̵��ϸ�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK:
				IMAGEMANAGER->frameRender("�غ��̵�", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_UPSHOT:
				IMAGEMANAGER->frameRender("�غ��̵�����", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_UPSHOT:
				IMAGEMANAGER->frameRender("�غ񰡸�����", getMemDC(), playerRC.left, playerRC.top);
				break;
				//#############################################����############################################
			case STATE::WLAK_UPSTARE:
				IMAGEMANAGER->frameRender("�غ������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_DOWNSHOT:
				IMAGEMANAGER->frameRender("�غ񰡸��Ʒ���������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_DOWNSTARE:
				IMAGEMANAGER->frameRender("�غ������߾Ʒ�������", getMemDC(), playerRC.left, playerRC.top);
				break;

			case STATE::JUMPWALK_DOWNSHOT:
				IMAGEMANAGER->frameRender("�غ񰡸��Ʒ���������", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHBOOM:
				IMAGEMANAGER->frameRender("�غ�ɾƼ�����ź", getMemDC(), playerRC.left, playerRC.top);
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
		//===================�̹���============================================

		// =====================================================================

		//====================����׿� ���ÿ뵵�� Ȯ��=============================
		if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
			if (_weapon == WEAPON::NORMAL)
			{
				_weapon = WEAPON::HEAVY;
			}
			else {
				_weapon = WEAPON::NORMAL;
			}
		}
		// =====================================================================
	

		//char str[128]; 
		//sprintf_s(&str,);
	}
	
//	Rectangle(getMemDC(), interplayerrc/*.left - playerRC.left, _InterPlayerRc.top - playerRC.top, _InterPlayerRc.right - playerRC.right, _InterPlayerRc.bottom - playerRC.bottom*/);
}

// =====================================================================================================================================
// ###################################################### �÷��̾� ��� ó�� ##############################################################
// =====================================================================================================================================
void Player::PlayerMotionState()
{

	switch (_weapon)  //������� �븻�϶� 
	{
	case WEAPON::NORMAL:
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

			_frameCount++;
			if (!_isLeft) {
				IMAGEMANAGER->findImage("�÷��̾��̵�")->setFrameY(0);
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
		break;
		//============================================================================================%%%%%%%%%%%%%%%%%%%%%
		//==================================================�÷��̾� �غ� ����ó��========================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
	case WEAPON::HEAVY:
		switch (_state)
		{
		case STATE ::JUMP_DOWNSTARE:
			//�غ������߾Ʒ�������
			IMAGEMANAGER->findImage("�غ������߾Ʒ�������")->setFrameY(0);
			if (_frameCount % SPEED == 0) {
				_frameIndex++;
				if (_frameIndex > 6) {
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("�غ������߾Ʒ�������")->setFrameX(_frameIndex);
			}
			break;

		case STATE::IDLE:
			_frameCount++;
			if (!_isLeft)
			{
				IMAGEMANAGER->findImage("�غ񰡸�")->setFrameY(0);
				if (_frameCount % SPEED == 0) {
					_frameIndex++;
					if (_frameIndex > 3) {
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("�غ񰡸�")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("�غ񰡸�")->setFrameY(1);
				if (_frameCount % SPEED == 0) {
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 3;
					}

					IMAGEMANAGER->findImage("�غ񰡸�")->setFrameX(_frameIndex);
				}
			}
			//�÷��̾��̵��ϸ鼭�����ϰ������߻�
			break;
		case STATE::WALK:

			_frameCount++;
			if (!_isLeft) {
				IMAGEMANAGER->findImage("�غ��̵�")->setFrameY(0);
				if (_frameCount % SPEED == 0) {
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("�غ��̵�")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("�غ��̵�")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 5;
					}

					IMAGEMANAGER->findImage("�غ��̵�")->setFrameX(_frameIndex);
				}
			}
			break;
		case STATE::JUMP:
			IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameY(0);
			_frameCount++;
			if (!_isLeft)
			{
				if (_frameCount % SPEED == 0) {
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 5;
					}

					IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameX(_frameIndex);
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
				IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 3;
					}

					IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameX(_frameIndex);
				}
			}
			break;

			//	�÷��̾��ޱ׷����̵�
		case STATE::CROUCHWALK:

			_frameCount++;
			if (!_isLeft)
			{
				IMAGEMANAGER->findImage("�غ�Ʒ��̵�")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 6)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("�غ�Ʒ��̵�")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("�غ�Ʒ��̵�")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 6;
					}

					IMAGEMANAGER->findImage("�غ�Ʒ��̵�")->setFrameX(_frameIndex);
				}
			}
			break;
			//�÷��̾��¿��̵��ϸ�����
		case STATE::JUMPWALK:
			_frameCount++;
			if (_isLeft == false)
			{
				IMAGEMANAGER->findImage("�غ��̵��ϸ�����")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("�غ��̵��ϸ�����")->setFrameX(_frameIndex);
				}
			}//�÷��̾��̵��ϸ鼭�����ϰ������߻�
			else
			{
				IMAGEMANAGER->findImage("�غ��̵��ϸ�����")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0)
					{
						_frameIndex = 4;
					}

					IMAGEMANAGER->findImage("�غ��̵��ϸ�����")->setFrameX(_frameIndex);
				}
			}
			break;
			//�÷��̾��̵��ϸ����

		case STATE::WLAK_UPSTARE:        //up������ ����� 
			//_frameCount = 2;


			_frameCount++;
			if (_isLeft == false)
			{
				IMAGEMANAGER->findImage("�غ������")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 2;
					}
					IMAGEMANAGER->findImage("�غ������")->setFrameX(_frameIndex);
				}
			}//�÷��̾��̵��ϸ鼭�����ϰ������߻�
			else
			{
				IMAGEMANAGER->findImage("�غ������")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 1)
					{
						_frameIndex =1;
					}

					IMAGEMANAGER->findImage("�غ������")->setFrameX(_frameIndex);
				}
			}
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
								_playerbullet->fire(_position.x+ 183, _position.y , 0, 12.5f);
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
								_playerbullet->fire(_position.x+ 183, _position.y+15, 0, 12.5f);
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
									_playerbullet->fire(_position.x + 183, _position.y , 0, 12.5f);
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


					//=================jumpwalk right 
				case WALKSTATE::JUMPWALK:
					//�÷��̾������ϸ鼭����
					_frameCount++; 
					IMAGEMANAGER->findImage("�÷��̾������ϸ鼭����")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++; 
						if (_frameIndex > 5)
						{
							_frameIndex = 0; 
						}
						IMAGEMANAGER->findImage("�÷��̾������ϸ鼭����")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerbullet->fire(_position.x + 183, _position.y , 0, 12.5f);
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
			case BULLET::LEFTFIRE:
				switch (_wstate)
				{

				case WALKSTATE::JUMPWALK:
					//�÷��̾������ϸ鼭����
					_frameCount++;
					IMAGEMANAGER->findImage("�÷��̾������ϸ鼭����")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("�÷��̾������ϸ鼭����")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerbullet->fire(_position.x- 120, _position.y+ 15, PI, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;

						}

					}
					break;

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
							_playerbullet->fire(_position.x-120 , _position.y+15, PI, 12.5f);
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
								_playerbullet->fire(_position.x- 120, _position.y+ 15, PI, 12.5f);
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
								_playerbullet->fire(_position.x -120, _position.y+ 15, PI, 12.5f);
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
				case WALKSTATE::WALK:
					//�÷��̾��̵��ϸ���������
					_frameCount++; 
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ���������")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ���������")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x+ 30, _position.y-180, PI / 2, 12.5f);
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
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ���������")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ���������")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x+ 30, _position.y-180, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					break;

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
								_playerbullet->fire(_position.x+30 , _position.y - 180, PI / 2, 12.5f);
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
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
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
					_frameCount++; 
				{
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
						
					}
					else
					{
						IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 30, _position.y -180, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}

				}
					
					break;
				case WALKSTATE::JUMPWALK:
					//���⼭ ���� �÷��̾��̵��ϸ鼭�����ϰ������߻�
					_frameCount++;
					
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameY(0);
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
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::JUMPWALK;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5; 
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
						   }
							if (_frameIndex == 0)
							{
								_state = STATE::JUMPWALK; 
								_playerbulletfire = false; 
							}
						}
					}
					break;
				}
				break;
			case BULLET::DOWNFIRE:
				//�÷��̾�������߾Ʒ�����
				switch (_wstate)
				{
				case WALKSTATE::JUMP:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾�������߾Ʒ�����")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾�������߾Ʒ�����")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x+ 30, _position.y+100, PI2 - (PI / 2), 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("�÷��̾�������߾Ʒ�����")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾�������߾Ʒ�����")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 22, _position.y + 120, PI2 - (PI / 2), 12.5f);
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
					//�÷��̾��̵������߾Ʒ�����
				
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾��̵������߾Ʒ�����")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵������߾Ʒ�����")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x + 41, _position.y + 100, PI2 - (PI / 2), 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("�÷��̾��̵������߾Ʒ�����")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵������߾Ʒ�����")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 11, _position.y + 100, PI2 - (PI / 2), 12.5f);
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
				//_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 12.5f);
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
							_playerbullet->fire(_position.x+150, _position.y+45 , 0, 12.5f);
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
							_playerbullet->fire(_position.x-110, _position.y + 45, PI, 12.5f);
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
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//##################################�غ�ӽŰ� ##################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################


		case WEAPON::HEAVY:
			switch (_bullet)
			{
			case BULLET::RIGHTFIRE:
				switch (_wstate)
				{
				case WALKSTATE::WALK:
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�غ��̵��ϸ����")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 3)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�غ��̵��ϸ����")->setFrameX(_frameIndex);
							if (_frameIndex == 3)
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
						IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 3)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameX(_frameIndex);				
							if (_frameIndex == 3)
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
							IMAGEMANAGER->findImage("�غ񰡸���������")->setFrameY(0);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex++;
								if (_frameIndex > 3)
								{
									_frameIndex = 0;
								}
								IMAGEMANAGER->findImage("�غ񰡸���������")->setFrameX(_frameIndex);
								if (_frameIndex == 3)
								{
									_state = STATE::IDLE;
									_playerbulletfire = false;
								}
							}
							break;
						}
					}




					break;


					//=================jumpwalk right 
				case WALKSTATE::JUMPWALK:
					//�÷��̾������ϸ鼭����
					_frameCount++;
					IMAGEMANAGER->findImage("�غ��̵���������")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 3)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("�غ��̵���������")->setFrameX(_frameIndex);
						if (_frameIndex == 3)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;

						}

					}

					break;
				}

				break;
			case BULLET::LEFTFIRE:
				switch (_wstate)
				{

				case WALKSTATE::JUMPWALK:
					//�÷��̾������ϸ鼭����
					_frameCount++;
					IMAGEMANAGER->findImage("�غ��̵���������")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 3;
						}
						IMAGEMANAGER->findImage("�غ��̵���������")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;

						}

					}
					break;

				case WALKSTATE::IDLE:
					_frameCount++;
					IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 3;
						}
						IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameX(_frameIndex);
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
						IMAGEMANAGER->findImage("�غ��̵��ϸ����")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 3;
							}
							IMAGEMANAGER->findImage("�غ��̵��ϸ����")->setFrameX(_frameIndex);
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
						IMAGEMANAGER->findImage("�غ񰡸���������")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 3;
							}
							IMAGEMANAGER->findImage("�غ񰡸���������")->setFrameX(_frameIndex);
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

				//�غ��̵�����
			case BULLET::UPFIRE://���� 
				switch (_wstate)
				{
				case WALKSTATE::WALK:
					//�÷��̾��̵��ϸ���������
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�غ��̵�����")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�غ��̵�����")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}
					else//���ʸ��
					{
						if (_frameCount % SPEED == 0)
						{
							IMAGEMANAGER->findImage("�غ��̵�����")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�غ��̵�����")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}
					break;

				case WALKSTATE::IDLE:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}
					else//���ʸ��
					{

						if (_frameCount % SPEED == 0)
						{
							IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�غ񰡸�����")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}



					break;

				case WALKSTATE::JUMP:
					_frameCount++;
					{
						if (_isLeft == false)
						{
							IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameY(0);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex++;
								if (_frameIndex > 5)
								{
									_frameIndex = 0;
								}
								IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameX(_frameIndex);
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
						else
						{
							IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameY(1);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex--;
								if (_frameIndex < 0)
								{
									_frameIndex = 5;
								}
								IMAGEMANAGER->findImage("�÷��̾�������������")->setFrameX(_frameIndex);
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

					}

					break;
				case WALKSTATE::JUMPWALK:
					//���⼭ ���� �÷��̾��̵��ϸ鼭�����ϰ������߻�
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameY(0);
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
					else
					{
						IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�÷��̾��̵��ϸ鼭�����ϰ������߻�")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::JUMPWALK;
								_playerbulletfire = false;
							}
						}
					}
					break;
				}
				break;
			case BULLET::DOWNFIRE:
				//�÷��̾�������߾Ʒ�����
				switch (_wstate)
				{
				case WALKSTATE::JUMP:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameX(_frameIndex);

							if (_frameIndex == 5)
							{
								_state = STATE::JUMP_DOWNSTARE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::JUMP_DOWNSTARE;
								_playerbulletfire = false;
							}
						}
					}

					break;
				case WALKSTATE::JUMPWALK:
					//�÷��̾��̵������߾Ʒ�����

					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameX(_frameIndex);

							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("�غ񰡸��Ʒ���������")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}

					break;


				}
				//_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 12.5f);
				break;
			case BULLET::DOWNATTACK://�÷��̾��ޱ׷�����
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 3)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameX(_frameIndex);
						if (_frameIndex == 3)
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
						IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameY(1);
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 3;
						}
						IMAGEMANAGER->findImage("�غ�Ʒ�����")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_state = STATE::CROUCH;
							_playerbulletfire = false;
						}
					}
				}
				break;
			}
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
							_playerboom->fire(_position.x + 170, _position.y+ 150, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+70, _position.y+150, PI / 2 + 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+ 170, _position.y+150, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x + 70, _position.y+150, PI / 2 + 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+ 170, _position.y+150, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+70, _position.y+150, PI / 2 + 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+170, _position.y+180, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+70, _position.y+180, PI / 2 + 1.1f, 0.05f, 12.5f);
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
	//collisionplayer = RectMakeCenter(_position.x + 130, _position.y + 220, 100, 140);
	
	_pixely = _colb.bottom; //���Ⱑ �ִϸ��̼� �ǾƷ��κ� 
	
	for (int i = _pixely; i < _pixely +140; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("����ȼ�")->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 255 && b == 0) && _jumppower <= 0)
		{
			_jumppower = 0.0f; 
			_position.y = i - 240;
			

			if ((_isJump) || _state==STATE::FLY)
			{
				_wstate = WALKSTATE::IDLE;
				_state = STATE::IDLE;
				_isJump = false;
				//_gravity = 0.0f; //�ȼ��浹�ÿ��� gravity��  0.0f���ȴ� 
			}
			break; 
		}

	}

	_pixelx = _colr.right ;
	
	for (int i = _pixelx-15; i < _pixelx + 15; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("����ȼ�")->getMemDC(), i, _position.y+150 );
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 255 && b == 0 && !_isLeft)/* && _jumppower <= 0*/)
		{
			_position.x = i - 50;
			//_gravity = 0.0f; //�ȼ��浹�ÿ��� gravity��  0.0f���ȴ� 
			
			break;
		}
	
	}
}

//void Player::EnemyCollision()      //�÷��̾� �⺻���� 
//{
//	RECT temp; 
//	for (int i = 0; i < _playerbullet->getVBullet().size(); i++)
//	{
//		cout << "���� " << endl;
//		if (IntersectRect(&temp, &_playerbullet->getVBullet()[i].rc, &_crab->getCol(2)  ) )//���� ))
//		{//���࿡ �÷��̾� �⺻�Ѿ˰�  �ֳʹ̰� �浹������ 
//			//buulet1 �⺻�Ѿ��� ���ݷ��� 1�λ��� 
//			//((Crab*)OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "crab"))->setHp(((Crab*)OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "crab"))->getHp() - 1);
//
//			//exit(0);
//			//&((Crab*)OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "crab")).
//		}
//	}
//}
//
