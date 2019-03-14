#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class BigCrab : public GameObject
{
private:
	//����
	STATE _state;
	//ī�޶� ����ü
	CAM _cam[4];
	//�浹 ����ü
	COL _col[4];
	//����ó�� ����ü
	ATTACK _att[2];
	//�÷��̾� Ŭ����
	class Player* player;
	//�ൿ�� ���� ī��Ʈ
	int count;
	//���� ������
	bool isLeft;
	float _angle;
	float _dist;
	bool _isStop;
	int bubbleMax;
	int _deathTimer;
	//��ǰ����
	bool _isAttack;
	bool _isBubbleShoot;
	bool _isBubbleShootFinish;
	class Bubble* _bubble;
	int _bubbleGauge;
	int _bubblefinishcount;
	//�̹����� ���߱� ���� ī��Ʈ 
	int _imgCount[2];
	//�̹���
	image* _bigCrabImg[6];
	int index[10];
	int countImg[10];
	int _hp;
	int _gauge;
	//�ȼ� �浹
	int _probeY;
	image* _pixelImage;
	RECT _pixelrc;
public:
	BigCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~BigCrab();

	//�浹��Ʈ get
	RECT getCol(int i) { return _col[i].rc; }
	//���ݷ�Ʈ get
	RECT getAtt(int i) { return _att[i].rc; }
	//��ǰ��Ʈ get
	//RECT getbubble(int i) { return _bubble->getVBubble()[i].rc; }
	//������
	void bigCrab_damage(int damage) { _hp = damage; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Attcol();
	void rectmove();
	void Crabpattern();
	
};

