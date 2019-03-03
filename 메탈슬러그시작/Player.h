#pragma once
#include "GameObject.h"
#include "Bullet.h"


enum class PLAYERBULLETSTATE//플레이어 총알의 방향상태 
{
	LEFTFIRE,RIGHTFIRE ,UPFIRE,DOWNFIRE , IDLE 
};

enum class PLAYERHEAVYSTATE//플레이어 해비머신건일떄 
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, IDLE
};


class Player : public GameObject
{
private:
	PLAYERBULLETSTATE _playerbulletstate;//플레이어 총알 방향 
	PLAYERHEAVYSTATE _playerheavystate; //플레이어 해비머신건일떄 
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






public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();
	

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	
};

