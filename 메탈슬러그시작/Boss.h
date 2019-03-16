#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class Boss : public GameObject
{
private:
	STATE _state;					//����
	//---------- ���� ó���� ���� ������ --------------------//
	bool _isStart;					//ó�� ��������
	int _attTimer;					//�������� Ÿ�̸�
	int _attDelay;					//�������� ������
	int _stopDelay;					//�������� �� ���� ������
	int _moveTimer;					//�ڷ� ������ Ÿ�̸�
	int _moveBuffTimer;				//�ڷ� ���� ������ Ÿ�̸�
	int _moveDelay;					//�ڷ� ������ �� ������
	int _delayTimer;				//���� �� ������ Ÿ�̸�
	bool _isMoveAttack;				//���ݿ����� ����
	bool _isAttack;					//���� ����
	bool _isAttackFinish;			//�����Ӱ��� ���� ����
	float _angle;					//�÷��̾���� ����
	float _dist;						//�÷��̾���� �Ÿ�
	int _deathTimer;				//���� ó���� ���� ����
	int _hp;						//���� ü��
	bool _isBuff;					//���� ���� ����
	bool _isBuffStart;				//���� ���� ���� ����
	bool _isBuffStartEnd;			//���� ���� ���� ���� ����

	image* _bridgeImg[22];			//�ٸ� �̹���

	//�浹 ó�� ����ü
	COL _col;
	//���� ����ó�� ����ü
	ATTACK _att;
	//ȭ���� �߻� ����ü
	SHOOT _fShoot[2];
	//��ź �߻� ����ü
	SHOOT _bShoot;

	//�÷��̾� Ŭ����
	class Player* _player;
	//ȭ���� Ŭ����
	class FireCannon* _fireCannon;
	//��ź Ŭ����
	class Bomb* _bomb;
	//�ؽ�Ʈ
	char msg1[128];
	POINT _pt;

	image* _BoassImg[7];
	int _index[7];
	int _deathWaterIndex[5];
	int _countImg[7];
	int speed;
	int _alpha[2];

	image* _deathWater;
	bool _isdeathWaterEnd;


public:
	Boss(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Boss();

	//�浹 ��Ʈ get
	COL getCol() { return _col; }
	//���� ��Ʈ get
	ATTACK getAtt() { return _att; }
	//���� ü�� get
	int getHp() { return _hp; }
	//���� ü�� set
	void setHp(int hp) { _hp = hp; }

	//���� ȭ���� �߻� ���
	void fireShoot();
	//��ź �߻� ���
	void fireBomb();

	void Damage(int att) { _hp -= att;  }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

