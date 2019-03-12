#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "enumClaas.h"
// =========================================
// ############ �÷��̾� ���� ###########
// =========================================
//upŰ �����鼭 ���Ѱ����ϸ� �̻� 


// =========================================
// ############ �÷��̾� �Ѿ� ���� ###########
// =========================================
enum class BULLET : int
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, DOWNATTACK, IDLE

};

// =========================================
// ############ �÷��̾� Į�� ���� ###########
// =========================================
enum class SWORD : int
{
	LEFTATTACK, RIGHTATTACK, IDLE //�⺻Į������ ���ʰ� �����ʸ��ִ� 
};
// =========================================
// ############ �÷��̾� ���� ���� ###########
// =========================================
//enum class WEAPON : int
//{
//	NORMAL, HEAVY, SWORD, GRENADE
//};
// =========================================
// ############ �÷��̾� ���� ���� ###########
// =========================================
//enum class WEAPON : int
//{
//	NORMAL, HEAVY, SWORD, GRENADE
//};

// =========================================
// ############ �÷��̾� ��ü ���� ############
// =========================================
enum class WALKSTATE : int
{
	IDLE, WALK, JUMP, JUMPWALK, CROUCH
};


class Player : public GameObject
{
private:
	enum class STATE : int
	{
		// �⺻, �⺻_��, �⺻_����, �⺻_Į��, �⺻_��ź, �⺻_������ ( 6���� )
		IDLE, IDLE_SHOT, IDLE_UPSHOT, IDLE_SWORD, IDLE_BOOM, IDLE_UPSTARE,

		// �ȱ�, �ȱ�_��, �ȱ�_����, �ȱ�_Į��, �ȱ�_��ź, �ȱ�_������ ( 6���� )
		WALK, WALK_SHOT, WALK_UPSHOT, WALK_SWORD, WALK_BOOM, WLAK_UPSTARE,
	

		// ����, ����_��, ����_����, ����_�ٿ, ����_Į��, ����_��ź, ����_������, ����_�Ʒ����� ( 8���� )
		JUMP, JUMP_SHOT, JUMP_UPSHOT, JUMP_DOWNSHOT, JUMP_SWORD, JUMP_BOOM, JUMP_UPSTARE, JUMP_DOWNSTARE,
	               

		// �����ȱ�, �����ȱ�_��, �����ȱ�_����, �����ȱ�_�ٿ, �����ȱ�_Į�� ( 6���� )
		JUMPWALK, JUMPWALK_SHOT, JUMPWALK_UPSHOT, JUMPWALK_DOWNSHOT, JUMPWALK_SWORD,
		
		// �����ȱ�_��ź, �����ȱ�_������, �����ȱ�_�Ʒ����� ( 3����)
		JUMPWALK_BOOM, JUMPWALK_UPSTARE, JUMPWALK_DOWNSTARE,

		// �ɱ�, �ɾưȱ�, �ɾ���, �ɾ�Į��, �ɾ���ź ( 5���� )
		CROUCH, CROUCHWALK, CROUCHSHOT, CROUCHSWORD, CROUCHBOOM
		 
		// �� 34���� ����
	};
private:
	BULLET _bullet;						//�÷��̾� �Ѿ� ���� 
	SWORD _sword;						//�÷��̾� Į���� ���ʰ� �������ϋ� enum�� 
	WEAPON _weapon;						//�÷��̾� ���� ������ճ� ���°�
	STATE _state;						//�÷��̾� ����
	WALKSTATE _wstate;					//�÷��̾� ��ü ����

	Bullet*_playerbullet;				//�÷��̾��� �����Ѿ� 

	Bullet* _heavyBullet;         //�÷��̾��� �غ�ӽŰ� 

	Boom* _playerboom;					//�÷��̾��� ��ź 

		
										
										//===================# �÷��̾� Į�� ���� #======================
	RECT PlayerRealLeftSword;			//��¥ �浹�� ���� Į
	RECT PlayerRealRightSword;			//��¥ �浹�� ������ Į
	bool PlayerRealSwordState;			//��¥ �浹�� Į�� bool �� 
	int SwordCount;						//Į �p�ʵڿ� ���ְ��ҷ��� 
										//============================================================

										//===================# �÷��̾� ���� ���� #======================
	float _jumppower;						//�÷��̾� ������
	float _gravity;						//�÷��̾� �߷� 
	bool _isJump;						//�÷��̾� �������³�? 
										//============================================================

										//===================# ������ ���� ���� #=======================
	int _frameCount;						//�÷��̾� �̹��� �ð����� 
	int _frameIndex;						//�÷��̾� �̹��� �δ콺 
	bool _isLeft;						//���ʻ��³�?
										//============================================================


										//===================# ���ӽŰ� ���� #========================
	int _count;							// ���ӽŰ� 4�߽�� _fire�� false�� �ٲ۴� 0���� �ʱ�ȭ�ϰ� 
	float _angle;							// ���ӽŰ� angle
	bool _hfire;							// ���ӽŰ� �߻�����
	int _time;							// ���ӽŰ� �Ѿ� ���� �����ð�
	float _angle1;						// ����Ȯ�ο�ޱ� ������ �����϶��� �������� ������ �������Ѵ� 
										//============================================================


	bool _boomfire;                      //d������ �߻�̳�??
	bool _playerboomFire;				//0�����ϰ� �Ǹ� ��ź�� ����Ҽ������� 
										//������ó���� bulletŬ���� boom fire�Լ����� ó���Ѵ� 

	bool _playerbulletfire;				//������Ʈ���� �Ѿ��� �߻�̳�? 


	//==========================�ȼ���//////////////////
	float _pixely;//�÷��̾��ȼ��� y��

	//==========================�����浹�ҷ�Ʈ ==========================
	//RECT _InterPlayerRc; 
	RECT check; 

	//RECT _temp;
public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();

	enum WEAPON getWeapon() { return _weapon; }

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void PlayerMotionState();			//�÷��̾� ���� �ִϸ��̼� 
	void PlayerBulletMotion();			//�Ѿ� ������ ��
	void Checkstate();					//�÷��̾� ���� Ȯ��

	void PlayerBoomMotion();            //�÷��̾���ź���� 
	void PixelMapCollision(); 
	void PlayerHeavy();                 //�غ�ӽŰ� ���� 
};

//
//if (KEYMANAGER->isOnceKeyDown('S') && _isJump == false)
//{
//	_isJump = true;						//������ true���ǰ� 
//	_jumppower = 10.5f;					//�������� 10.5
//	_gravity = 0.5f;					//�߷°��� 0.5
//
//										// �Ȱ� �����鼭 JUMP�� ������ WLAKJUMP
//										// �׳� ������ JUMP
//
//
//
//
//	if (_wstate != WALKSTATE::JUMPWALK)
//		_wstate = WALKSTATE::JUMP;
//
//	//	_wstate = WALKSTATE::JUMP;
//	_state = STATE::JUMP;
//
//	//_wstate = WALKSTATE::JUMPWALK;
//	//_state = STATE::JUMPWALK_DOWNSHOT;
//
//}
//
//
//
//// ========================================================================
//// ###################### �÷��̾� ����(JUMP) ó�� ##########################
//// ========================================================================
//if (_isJump == true)
//{
//	_position.y -= _jumppower;			//�÷��̾� y���� ��������ŭ ���ش�  
//	_jumppower -= _gravity;				//�������� �߷°���ŭ ������ 
//
//										//	_wstate = WALKSTATE::JUMP; 
//										//_state = STATE::JUMP_UPSHOT;
//
//										// ------- ���� �� �Ʒ��� ������ -------
//	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
//	{//�ɾ��ձ� �ɾƼ� ��� �ɾƼ� `` �ɾƼ� �̵� 
//	 //�÷��̾� �Ѿ˹����� �Ʒ����̵ȴ� 
//		_bullet = BULLET::DOWNFIRE;
//
//		if (_state == STATE::JUMPWALK_DOWNSHOT)
//		{
//			_state = STATE::JUMPWALK_DOWNSHOT;
//			_wstate = WALKSTATE::JUMPWALK;
//		}
//		else if (_state == STATE::JUMP_DOWNSHOT)
//
//		{
//			_state = STATE::JUMP_DOWNSHOT;
//			_wstate = WALKSTATE::JUMP;
//		}
//		if (_isLeft == true)
//		{
//			_angle1 += 0.125f;
//			if (_angle1 > -(PI / 2))
//			{
//				_angle1 = -(PI / 2);
//			}
//		}
//		else if (_isLeft == false)
//		{
//			_angle1 -= 0.125f;
//			if (_angle1 < -(PI / 2))
//			{
//				_angle1 = -(PI / 2);
//			}
//		}
//	}
//	else
//		if (_isLeft == true)
//		{
//			_angle1 -= 0.125f;
//			if (_angle1 < -PI)
//			{
//				_angle1 = -PI;
//			}
//		}
//		else if (_isLeft == false)
//		{
//			_angle1 += 0.125f;
//			if (_angle1 > 0)
//			{
//				_angle1 = 0.0f;
//			}
//		}
//}
////�������°� �ƴϰ� �Ѿ˹����� �Ʒ����ϋ��� 
////�Ѿ˹����� �ƹ��͵� �ȳ����� ���ƇJ�� 
//if (_isJump == false && _bullet == BULLET::DOWNFIRE)
//{
//	_bullet = BULLET::IDLE;
//}