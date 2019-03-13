#pragma once
#include "GameObject.h"
#include "Bullet.h"
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
	                           //                             //�ְ� ����� 

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

	//########################################����ü#############################
	
	BULLET _bullet;						//�÷��̾� �Ѿ� ���� 
	SWORD _sword;						//�÷��̾� Į���� ���ʰ� �������ϋ� enum�� 
	WEAPON _weapon;						//�÷��̾� ���� ������ճ� ���°�
	STATE _state;						//�÷��̾� ����
	WALKSTATE _wstate;					//�÷��̾� ��ü ����


	//######################################�Ѿ�####################

	Bullet1*_playerbullet;				//�÷��̾��� �����Ѿ� 
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
	float _normalangle;                  //�⺻�Ѿ� �ޱ�
	

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

	WEAPON GetWeapon() {return _weapon; }						//�÷��̾� ���� ������ճ� ���°�
	
	void SetWeapon(WEAPON Weapon) { _weapon = Weapon; }
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void PlayerMotionState();			//�÷��̾� ���� �ִϸ��̼� 
	void PlayerBulletMotion();			//�Ѿ� ������ ��
	void Checkstate();					//�÷��̾� ���� Ȯ��

	void PlayerBoomMotion();            //�÷��̾���ź���� 
	void PixelMapCollision(); 


	void EnemyCollision();              //�ֳʹ̿� �÷��̾��Ѿ˰� �浹������ 
};
