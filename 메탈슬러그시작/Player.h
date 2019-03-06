#pragma once
#include "GameObject.h"
#include "Bullet.h"


enum class PLAYERBULLETSTATE//플레이어 기본총알의 방향상태 
{
	LEFTFIRE,RIGHTFIRE ,UPFIRE,DOWNFIRE ,DOWNATTACK, IDLE 
};//downattack은 쭈그려쏘기다 

enum class PLAYERHEAVYSTATE//플레이어 해비머신건일떄 
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, DOWNATTACK, IDLE
};//downattack은 쭈그려쏘기다 
enum class PLAYERSWORD
{
	LEFTATTACK,RIGHTATTACK,IDLE //기본칼공격은 왼쪽과 오른쪽만있다 
};

enum class PLAYERWEAPONSTATE//플레이어의 무기 뭐들고잇는가? 
{
	NORMAL,HEAVY,SWORD   
};  //기본총알과 헤비머신건 붙엇을떄쓰는 칼을 들고있다 

class Player : public GameObject
{
private:
	PLAYERBULLETSTATE _playerbulletstate;//플레이어 총알 방향 
	PLAYERHEAVYSTATE _playerheavystate; //플레이어 해비머신건일떄 
	PLAYERSWORD _playersword;//플레이어 칼공격 왼쪽과 오른쪽일떄 enum문 
	PLAYERWEAPONSTATE _playerweaponstate;//플레이어 무기 뭐들고잇나 상태값
   //플레이어 총알 
	Bullet*_playerbullet;//플레이어의 공용총알 
	Boom* _playerboom; //플레이어의 폭탄 

	RECT PlayerLeftSword;//왼쪽모션일떄 칼렉트 
	RECT PlayerRightSword;//오른쪽모션일떄 칼렉트 

	//=================================
	RECT PlayerRealLeftSword; //진짜 충돌할 왼쪽 칼
	RECT PlayerRealRightSword; //진짜 충돌할 오른쪽 칼

	bool PlayerRealSwordState; //진짜 충돌할 칼의 bool 값 
	int SwordCount; //칼 몆초뒤에 꺼주게할려고 


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


	bool _playerboomFire;//0발이하가 되면 폭탄을 사용할수가없다 
	//나머지처리는 bullet클래스 boom fire함수에서 처리한다 

	

public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();
	

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	
};

