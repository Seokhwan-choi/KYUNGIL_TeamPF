#pragma once
#include "GameObject.h"
#include "CommonEnemyFrame.h"

class Boss : public GameObject
{
private:
	STATE _state;					//상태
	//---------- 공격 처리를 위한 변수들 --------------------//
	bool _isStart;					//처음 등장유무
	int _attTimer;					//근접공격 타이머
	int _attDelay;					//근접공격 딜레이
	int _stopDelay;					//근접공격 전 정지 딜레이
	int _moveTimer;					//뒤로 움직임 타이머
	int _moveBuffTimer;				//뒤로 버프 움직임 타이머
	int _moveDelay;					//뒤로 움직임 전 딜레이
	int _delayTimer;				//공격 전 딜레이 타이머
	bool _isMoveAttack;				//공격움직임 유무
	bool _isAttack;					//공격 유무
	bool _isAttackFinish;			//움직임공격 종료 유무
	float _angle;					//플레이어와의 각도
	float _dist;						//플레이어와의 거리
	int _deathTimer;				//죽음 처리를 위한 변수
	int _hp;						//보스 체력
	bool _isBuff;					//보스 버프 유무
	bool _isBuffStart;				//보스 버프 등장 유무
	bool _isBuffStartEnd;			//보스 버프 등장 종료 유무

	//충돌 처리 구조체
	COL _col;
	//근접 공격처리 구조체
	ATTACK _att;
	//화염포 발사 구조체
	SHOOT _fShoot[2];
	//폭탄 발사 구조체
	SHOOT _bShoot;

	//플레이어 클래스
	class Player* _player;
	//화염포 클래스
	class FireCannon* _fireCannon;
	//폭탄 클래스
	class Bomb* _bomb;
	//텍스트
	char msg1[128];
	POINT _pt;
public:
	Boss(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Boss();

	//충돌 렉트 get
	COL getCol() { return _col; }

	//보스 체력 get
	int getHp() { return _hp; }
	//보스 체력 set
	void setHp(int hp) { _hp = hp; }

	//양쪽 화염포 발사 명령
	void fireShoot();
	//폭탄 발사 명령
	void fireBomb();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

