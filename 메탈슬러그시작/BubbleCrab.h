#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class BubbleCrab : public GameObject
{
private:
	//����
	STATE _state;
	//���� ������ ó���� ���� ����
	bool _isUp;
	//���� ó���� ���� ����
	int _isStop;					//ī�޶� ���� ��������
	int _gauge;						//�������� ������ ó��
	int _bubbleGauge;				//��ǰ���� ������ ó��
	float _attackAngle;
	bool _isBubbleShoot;
	bool _isBubbleShootFinish;
	int _moveTimer;
	bool _isAttack;
	bool _isAttackFinish;

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
	//�ؽ�Ʈ
	char msg1[128];
	POINT _pt;
	//�÷��̾� Ŭ����
	class Player* _player;
	//��ǰ Ŭ����
	class Bubble* _bubble;
public:
	BubbleCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~BubbleCrab();

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
};


