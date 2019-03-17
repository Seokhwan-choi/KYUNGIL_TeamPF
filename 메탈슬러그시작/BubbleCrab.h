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
	int _hp;

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
	//��ǰ�߻�� �÷��̾���� ����
	float _bubbleAngle;
	//�÷��̾���� �Ÿ�
	float _dist;
	//�ؽ�Ʈ
	char msg1[128];
	POINT _pt;
	//�÷��̾� Ŭ����
	class Player* _player;
	//��ǰ Ŭ����
	class Bubble* _bubble;
	//�̹���
	image* BubblecrabImg[8];
	//�̹��� ������ ����
	int indexImg[6], countImg[6];

	//�ȼ� �浹
	int _probeY;
	image* _pixelImage[2];
	int _pixelGravity;
	RECT _pixelrc;

	bool _bubbleShootSound;	//��ǰ����ݺ��������
	bool _deathSound;	//����ݺ��������
public:
	BubbleCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~BubbleCrab();

	//�浹��Ʈ get
	RECT getCol(int i) { return _col[i].rc; }
	//���ݷ�Ʈ get
	RECT getAtt(int i) { return _att[i].rc; }
	//��ǰ��Ʈ get
	//RECT getbubble(int i) { return _bubble->getVBubble()[i].rc; }
	//ü�� get
	int getHp() { return _hp; }
	//ü�� set
	void setHp(int hp) { _hp = hp; }

	//������
	void bubbleCrab_damage(int damage) { _hp -= damage; }



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

	void bubblecrabImage();
	void bubblecrabImageRender();
};


