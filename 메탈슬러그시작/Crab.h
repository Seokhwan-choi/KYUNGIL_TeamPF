#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class Crab : public GameObject
{
private:
	//����
	STATE _state;
	//�̹���
	image* crabImg[6];
	//�̹��� ������ ����
	int indexImg[5], countImg[5];
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
	//ü��
	int _hp;
	////���콺 ��ǥ �ؽ�Ʈ
	//char msg1[128];
	//POINT _pt;
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
	//�浹��Ʈ get
	RECT getCol(int i) { return _col[i].rc; }
	//���ݷ�Ʈ get
	RECT getAtt(int i) { return _att[i].rc; }
	//ü�� get
	int getHp() { return _hp; }
	//ü�� set
	void setHp(int hp) { _hp = hp; }

	//������
	void crab_damage(int damage) { _hp -= damage; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//�̹��� ������ �Լ�
	void crabImage();
	void crabImageRender();
};

