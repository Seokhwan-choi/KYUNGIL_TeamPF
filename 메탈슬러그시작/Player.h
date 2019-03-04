#pragma once
#include "GameObject.h"
#include "Bullet.h"


enum class PLAYERBULLETSTATE//플레이어 기본총알의 방향상태 
{
	LEFTFIRE,RIGHTFIRE ,UPFIRE,DOWNFIRE ,DOWNATTACK, IDLE 
};

enum class PLAYERHEAVYSTATE//플레이어 해비머신건일떄 
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, DOWNATTACK, IDLE
};

enum class PLAYERWEAPONSTATE//플레이어의 무기 뭐들고잇는가? 
{
	NORMAL,HEAVY 
};  //기본총알과 헤비머신건을 들고있다 

class Player : public GameObject
{
private:
	PLAYERBULLETSTATE _playerbulletstate;//플레이어 총알 방향 
	PLAYERHEAVYSTATE _playerheavystate; //플레이어 해비머신건일떄 
	PLAYERWEAPONSTATE _playerweaponstate;//플레이어 무기 뭐들고잇나 상태값
   //플레이어 총알 
	Bullet*_playerbullet;//플레이어의 공용총알 
	Boom* _playerboom; //플레이어의 폭탄 

	//플레이어 점프 
	float _jumppower;//플레이어 점프힘
	float _gravity;//플레이어 중력 
	bool _isJump; //플레이어 점프상태냐? 

	
	//프레임이미지 
	int _frameCount;//플레이어 이미지 시간변수 
	int _frameIndex; //플레이어 이미지 인댁스 
	bool _isLeft;//왼쪽상태냐?

	int _count;		// 헤비머신건 4발쏘고 _fire를 false로 바꾼다 0으로 초기화하고 
	float _angle;	// 확인용 angle
	bool _fire;		// 확인용 fire
	int _time;		// 확인용 time
	float _angle1;//음수확인용앵글 각도가 음수일때는 음수전용 변수를 만들어야한다 

	int _playerboomMax;//플레이어 폭탄 최대갯수 
	bool _playerboomFire;//0발이하가 되면 폭탄을 사용할수가없다 


public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();
	

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	
};

