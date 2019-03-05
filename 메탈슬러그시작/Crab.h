#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class Crab : public GameObject
{
private:
	//����
	STATE _state;
	//�̹���
	image* crab[4];
	//�̹��� ������ ����
	int index[3], count[3];
	//���� ������ ó���� ���� ����
	int _move;
	bool _isUp;
	//���� ó���� ���� ����
	int _gauge;
	float _attackAngle;
	bool _isAttack;
	bool _isAttackFinish;
	POINTFLOAT _tempPt;
	//���� ó���� ���� ����
	int _deathTimer;
	//ī�޶� ����ü
	CAM _cam;	//�÷��̾ �����ϴ� ���� �߽������� ���� 900
					//�Դٰ��� �����ϴ� ���� �߽������� ���� 300
	//�浹 ����ü
	COL _col[4];	//0 : top, 1: bottom, 2 : left, 3: right
	//��üó�� ����ü
	PART _part[3];	//0 : left, 1 : center, 2 : right 
	//����ó�� ����ü
	ATTACK _att[2];	//0 : left, 1 : right
	//�÷��̾���� ����
	float _angle;
	//�÷��̾���� �Ÿ�
	float _dist;
	//���콺 ��ǥ �ؽ�Ʈ
	char msg1[128];
	POINT _pt;
	//�÷��̾� Ŭ����
	class Player* _player;
public:
	Crab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Crab();

	//�浹���� get
	bool getIsCrush(int i) { return _col[i].isCrush; }
	//�浹���� set
	void setIsCrush(int i, bool crush) { _col[i].isCrush = crush; }
	//�÷��̾� ���ӿ��� get
	bool getIsKill(int i) { return _col[i].isKill; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//�̹��� ������ �Լ�
	void Crabimage();
	void CrabimageRender();


};

