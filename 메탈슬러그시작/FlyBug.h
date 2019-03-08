#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class FlyBug : public GameObject
{
private:
	//����
	STATE _state;
	//���� ������ ó���� ���� ����
	int _move;
	bool _isUp;
	//���� ó���� ���� ����
	int _gauge;
	float _attackAngle;
	bool _isAttack;
	POINTFLOAT _tempPt;
	//���� ó���� ���� ����
	int _deathTimer;
	//ī�޶� ����ü
	CAM _cam;
	//�浹 ����ü
	COL _col;
	//��üó�� ����ü
	PART _part[3];
	//�÷��̾���� ����
	float _angle;
	//���콺 ��ǥ �ؽ�Ʈ
	char msg1[128];
	POINT _pt;
	//�÷��̾� Ŭ����
	class Player* _player;
public:
	FlyBug(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~FlyBug();

	//�浹���� get
	bool getIsCrush() { return _col.isCrush; }
	//�浹���� set
	void setIsCrush(bool crush) { _col.isCrush = crush; }
	//�÷��̾� ���ӿ��� get
	bool getIsKill() { return _col.isKill; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

class Flybug :
	public GameObject
{
public:
	Flybug();
	~Flybug();
};

