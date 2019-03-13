#pragma once
#include "GameObject.h"
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
	//��ǰ����
	bool _isAttack;
	bool _isBubbleShoot;
	bool _isBubbleShootFinish;
	class Bubble* _bubble;
	int _bubbleGauge;
	int _bubblefinishcount;
public:
	BigCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~BigCrab();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Attcol();
	void rectmove();
};

