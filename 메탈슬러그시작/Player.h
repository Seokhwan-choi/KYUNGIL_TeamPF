#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "enumClaas.h"
// =========================================
// ############ 플레이어 버그 ###########
// =========================================
//up키 누르면서 딱총공격하면 이상 


// =========================================
// ############ 플레이어 총알 방향 ###########
// =========================================
enum class BULLET : int
{
	LEFTFIRE, RIGHTFIRE, UPFIRE, DOWNFIRE, DOWNATTACK, IDLE

};

// =========================================
// ############ 플레이어 칼질 방향 ###########
// =========================================
enum class SWORD : int
{
	LEFTATTACK, RIGHTATTACK, IDLE //기본칼공격은 왼쪽과 오른쪽만있다 
};
// =========================================
// ############ 플레이어 무기 상태 ###########
// =========================================
//enum class WEAPON : int
//{
//	NORMAL, HEAVY, SWORD, GRENADE
//};
// =========================================
// ############ 플레이어 무기 상태 ###########
// =========================================
//enum class WEAPON : int
//{
//	NORMAL, HEAVY, SWORD, GRENADE
//};

// =========================================
// ############ 플레이어 하체 상태 ############
// =========================================
enum class WALKSTATE : int
{
	IDLE, WALK, JUMP, JUMPWALK, CROUCH
};


class Player : public GameObject
{
private:
	enum class STATE : int
	{
		// 기본, 기본_총, 기본_업샷, 기본_칼질, 기본_폭탄, 기본_위보기 ( 6가지 )
		IDLE, IDLE_SHOT, IDLE_UPSHOT, IDLE_SWORD, IDLE_BOOM, IDLE_UPSTARE,

		// 걷기, 걷기_총, 걷기_업샷, 걷기_칼질, 걷기_폭탄, 걷기_위보기 ( 6가지 )
		WALK, WALK_SHOT, WALK_UPSHOT, WALK_SWORD, WALK_BOOM, WLAK_UPSTARE,
	

		// 점프, 점프_총, 점프_업샷, 점프_다운샷, 점프_칼질, 점프_폭탄, 점프_위보기, 점프_아래보기 ( 8가지 )
		JUMP, JUMP_SHOT, JUMP_UPSHOT, JUMP_DOWNSHOT, JUMP_SWORD, JUMP_BOOM, JUMP_UPSTARE, JUMP_DOWNSTARE,
	               

		// 점프걷기, 점프걷기_총, 점프걷기_업샷, 점프걷기_다운샷, 점프걷기_칼질 ( 6가지 )
		JUMPWALK, JUMPWALK_SHOT, JUMPWALK_UPSHOT, JUMPWALK_DOWNSHOT, JUMPWALK_SWORD,
		
		// 점프걷기_폭탄, 점프걷기_위보기, 점프걷기_아래보기 ( 3가지)
		JUMPWALK_BOOM, JUMPWALK_UPSTARE, JUMPWALK_DOWNSTARE,

		// 앉기, 앉아걷기, 앉아총, 앉아칼질, 앉아폭탄 ( 5가지 )
		CROUCH, CROUCHWALK, CROUCHSHOT, CROUCHSWORD, CROUCHBOOM
		 
		// 총 34가지 동작
	};
private:
	BULLET _bullet;						//플레이어 총알 방향 
	SWORD _sword;						//플레이어 칼공격 왼쪽과 오른쪽일떄 enum문 
	WEAPON _weapon;						//플레이어 무기 뭐들고잇나 상태값
	STATE _state;						//플레이어 상태
	WALKSTATE _wstate;					//플레이어 하체 상태

	Bullet*_playerbullet;				//플레이어의 공용총알 

	Bullet* _heavyBullet;         //플레이어의 해비머신건 

	Boom* _playerboom;					//플레이어의 폭탄 

		
										
										//===================# 플레이어 칼질 변수 #======================
	RECT PlayerRealLeftSword;			//진짜 충돌할 왼쪽 칼
	RECT PlayerRealRightSword;			//진짜 충돌할 오른쪽 칼
	bool PlayerRealSwordState;			//진짜 충돌할 칼의 bool 값 
	int SwordCount;						//칼 몆초뒤에 꺼주게할려고 
										//============================================================

										//===================# 플레이어 점프 변수 #======================
	float _jumppower;						//플레이어 점프힘
	float _gravity;						//플레이어 중력 
	bool _isJump;						//플레이어 점프상태냐? 
										//============================================================

										//===================# 프레임 랜더 변수 #=======================
	int _frameCount;						//플레이어 이미지 시간변수 
	int _frameIndex;						//플레이어 이미지 인댁스 
	bool _isLeft;						//왼쪽상태냐?
										//============================================================


										//===================# 헤비머신건 변수 #========================
	int _count;							// 헤비머신건 4발쏘고 _fire를 false로 바꾼다 0으로 초기화하고 
	float _angle;							// 헤비머신건 angle
	bool _hfire;							// 헤비머신건 발사하자
	int _time;							// 헤비머신건 총알 간격 지연시간
	float _angle1;						// 음수확인용앵글 각도가 음수일때는 음수전용 변수를 만들어야한다 
										//============================================================


	bool _boomfire;                      //d눌러서 발사됫냐??
	bool _playerboomFire;				//0발이하가 되면 폭탄을 사용할수가없다 
										//나머지처리는 bullet클래스 boom fire함수에서 처리한다 

	bool _playerbulletfire;				//업데이트에서 총알이 발사됫냐? 


	//==========================픽셀용//////////////////
	float _pixely;//플레이어픽셀용 y값

	//==========================실제충돌할렉트 ==========================
	//RECT _InterPlayerRc; 
	RECT check; 

	//RECT _temp;
public:

	Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Player();

	enum WEAPON getWeapon() { return _weapon; }

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void PlayerMotionState();			//플레이어 동작 애니메이션 
	void PlayerBulletMotion();			//총알 움직일 때
	void Checkstate();					//플레이어 상태 확인

	void PlayerBoomMotion();            //플레이어폭탄상태 
	void PixelMapCollision(); 
	void PlayerHeavy();                 //해비머신건 각도 
};

//
//if (KEYMANAGER->isOnceKeyDown('S') && _isJump == false)
//{
//	_isJump = true;						//점프는 true가되고 
//	_jumppower = 10.5f;					//점프힘에 10.5
//	_gravity = 0.5f;					//중력값은 0.5
//
//										// 걷고 있으면서 JUMP를 누르면 WLAKJUMP
//										// 그냥 누르면 JUMP
//
//
//
//
//	if (_wstate != WALKSTATE::JUMPWALK)
//		_wstate = WALKSTATE::JUMP;
//
//	//	_wstate = WALKSTATE::JUMP;
//	_state = STATE::JUMP;
//
//	//_wstate = WALKSTATE::JUMPWALK;
//	//_state = STATE::JUMPWALK_DOWNSHOT;
//
//}
//
//
//
//// ========================================================================
//// ###################### 플레이어 점프(JUMP) 처리 ##########################
//// ========================================================================
//if (_isJump == true)
//{
//	_position.y -= _jumppower;			//플레이어 y축은 점프힘만큼 빼준다  
//	_jumppower -= _gravity;				//점프힘은 중력값만큼 빠진다 
//
//										//	_wstate = WALKSTATE::JUMP; 
//										//_state = STATE::JUMP_UPSHOT;
//
//										// ------- 점프 중 아래를 누르면 -------
//	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
//	{//앉아잇기 앉아서 쏘기 앉아서 `` 앉아서 이동 
//	 //플레이어 총알방향은 아래쪽이된다 
//		_bullet = BULLET::DOWNFIRE;
//
//		if (_state == STATE::JUMPWALK_DOWNSHOT)
//		{
//			_state = STATE::JUMPWALK_DOWNSHOT;
//			_wstate = WALKSTATE::JUMPWALK;
//		}
//		else if (_state == STATE::JUMP_DOWNSHOT)
//
//		{
//			_state = STATE::JUMP_DOWNSHOT;
//			_wstate = WALKSTATE::JUMP;
//		}
//		if (_isLeft == true)
//		{
//			_angle1 += 0.125f;
//			if (_angle1 > -(PI / 2))
//			{
//				_angle1 = -(PI / 2);
//			}
//		}
//		else if (_isLeft == false)
//		{
//			_angle1 -= 0.125f;
//			if (_angle1 < -(PI / 2))
//			{
//				_angle1 = -(PI / 2);
//			}
//		}
//	}
//	else
//		if (_isLeft == true)
//		{
//			_angle1 -= 0.125f;
//			if (_angle1 < -PI)
//			{
//				_angle1 = -PI;
//			}
//		}
//		else if (_isLeft == false)
//		{
//			_angle1 += 0.125f;
//			if (_angle1 > 0)
//			{
//				_angle1 = 0.0f;
//			}
//		}
//}
////점프상태가 아니고 총알방향이 아래쪽일떄는 
////총알방향은 아무것도 안나가게 막아놧다 
//if (_isJump == false && _bullet == BULLET::DOWNFIRE)
//{
//	_bullet = BULLET::IDLE;
//}