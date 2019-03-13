#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class FlyBug : public GameObject
{
private:
	//상태
	STATE _state;
	//상하 움직임 처리를 위한 변수
	int _move;
	bool _isUp;
	//공격 처리를 위한 변수
	int _gauge;
	float _attackAngle;
	bool _isAttack;
	POINTFLOAT _tempPt;
	//죽음 처리를 위한 변수
	int _deathTimer;
	//카메라 구조체
	CAM _cam;
	//충돌 구조체
	COL _col;
	//시체처리 구조체
	PART _part[3];
	//플레이어와의 각도
	float _angle;
	//마우스 좌표 텍스트
	char msg1[128];
	POINT _pt;
	//플레이어 클래스
	class Player* _player;
public:
	FlyBug(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~FlyBug();

	//충돌여부 get
	bool getIsCrush() { return _col.isCrush; }
	//충돌여부 set
	void setIsCrush(bool crush) { _col.isCrush = crush; }
	//플레이어 죽임여부 get
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

