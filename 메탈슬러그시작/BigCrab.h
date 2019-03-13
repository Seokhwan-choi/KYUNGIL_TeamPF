#pragma once
#include "GameObject.h"
class BigCrab : public GameObject
{
private:
	//상태
	STATE _state;
	//카메라 구조체
	CAM _cam[4];
	//충돌 구조체
	COL _col[4];
	//공격처리 구조체
	ATTACK _att[2];
	//플레이어 클래스
	class Player* player;
	//행동을 위한 카운트
	int count;
	//왼쪽 오른쪽
	bool isLeft;
	float _angle;
	float _dist;
	bool _isStop;
	int bubbleMax;
	//거품공격
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

