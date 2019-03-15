#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

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
	int _deathTimer;
	//거품공격
	bool _isAttack;
	bool _isBubbleShoot;
	bool _isBubbleShootFinish;
	class Bubble* _bubble;
	int _bubbleGauge;
	int _bubblefinishcount;
	//이미지랑 맞추기 위한 카운트 
	int _imgCount[2];
	//이미지
	image* _bigCrabImg[6];
	int index[10];
	int countImg[10];
	int _hp;
	int _gauge;
	//픽셀 충돌
	int _probeY;
	image* _pixelImage;
	RECT _pixelrc;
public:
	BigCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~BigCrab();

	//충돌렉트 get
	RECT getCol(int i) { return _col[i].rc; }
	//공격렉트 get
	RECT getAtt(int i) { return _att[i].rc; }
	//거품렉트 get
	//RECT getbubble(int i) { return _bubble->getVBubble()[i].rc; }
	//데미지
	void bigCrab_damage(int damage) { _hp = damage; }

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void Attcol();
	void rectmove();
	void Crabpattern();
	
};

