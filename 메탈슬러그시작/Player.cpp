#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#define SPEED 6

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_jumppower = 0.0f;								//플레이어 점프힘 
	_gravity = 0.0f;								//플레이어 중력 
	_isJump = false;								//최초 점프안된상태 
	_playerboomFire = false;						//플레이어 폭탄상태 false일떄만 쏠수있고 true일시 폭탄사용불가하다 
	_time = 0;										//항상update되고 해비머신건발사시 4발정도 간격을 주기위하여 
	_count = 0;										//해비머신건이 발사됫을시 count가 4가되면 fire를 false로 만들기 위하여 
	_hfire = false;									//키를 누르면 true가되고 해비머신건이 발사가된다 

													// ================= 플레이어 총알 ============================= 
	_playerbullet = new Bullet("플레이어 공용총알");
	_playerbullet->Init("플레이어/기본총알.bmp", 25, 10, 1000, 800);

	// ================= 플레이어 폭탄 =============================
	_playerboom = new Boom("플레이어 폭탄");
	_playerboom->Init("플레이어/수류탄.bmp", 720, 89, 2,WINSIZEY);


	_bullet = BULLET::RIGHTFIRE;					//플레이어 최초상태는 오른쪽보고 총알쏘는상태 
	_weapon = WEAPON::NORMAL;						//플레이어의 기본 총상태는 딱총상태이다 
	_sword = SWORD::RIGHTATTACK;					//칼은 기본적으로 오른쪽모션먼저세팅되어있다 
	_state = STATE::IDLE;
	PlayerRealSwordState = false;					//진짜 충돌할 칼의 bool 값 
	SwordCount = 0;									//칼 몆초뒤에 꺼주게할려고  				
	_playerbulletfire = false;						//총알 발사 눌렀냐?
	_frameCount = 0;								//프레임 카운트 초기화
	_frameIndex = 0;								//프레임 인덱스 초기화


													// ========================================== 플레이어 이미지 =======================================================
	IMAGEMANAGER->addFrameImage("플레이어가만", "플레이어/플레이어가만.bmp", 800, 503, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어딱총공격", "플레이어/기본딱총공격.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동", "플레이어/플레이어이동.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어위딱총공격", "플레이어/위기본딱총공격.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어기본점프", "플레이어/플레이어기본점프.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어가만위보기", "플레이어/플레이어가만위보기.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어쭈그려", "플레이어/플레이어쭈그려.bmp", 800, 503, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어쭈그려서이동", "플레이어/플레이어쭈그려서이동.bmp", 1400, 503, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어쭈그려공격", "플레이어/플레이어쭈그려공격.bmp", 2000, 503, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어좌우이동하며점프", "플레이어/플레이어좌우이동하며점프.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동하며공격", "플레이어/플레이어이동하며공격.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어가만점프공격", "플레이어/플레이어가만점프공격.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동하면서점프하고위에발사", "플레이어/플레이어이동하면서점프하고위에모션.bmp", 1200, 503, 6, 2, true, RGB(255, 0, 255));//발사하는것 
}
Player::~Player()
{

}

HRESULT Player::Init()
{
	return S_OK;
}

void Player::Release()
{

}

void Player::Update()
{
	SwordCount++;								//칼충돌됫을시 몆초뒤에 충돌박스 커주는 변수 
	_time++;									//해비머신건용 time변수 항시 update 

												// ========================================================================
												// ####################### 플레이어 걷기(WALK) ##############################
												// ========================================================================
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//플레이어 왼쪽키 눌럿을시 
	{
		_bullet = BULLET::LEFTFIRE;				//왼쪽상태에서는 총알 왼쪽으로 나간다 
												//_state = STATE::CROUCHWALK
												//플레이어 움직임 
		_isLeft = true;							//왼쪽눌르면 isLeft는 true 
												//if (_isJump == true)
												//{
												//	_wstate = WALKSTATE::JUMPWALK;		//플레이어 하체 상태 점프걷기(JUMPWALK)
												//	_state = STATE::JUMPWALK; 
												//	_position.x -= 3.0f; 
												//}
		if (_isJump == true)
		{
			if (_state == STATE::JUMP_SHOT)
			{
				_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMP_SHOT;
			}
			else
			{
				_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMPWALK;
			}
			_position.x -= 3.0f;
		}


		else if (_state == STATE::CROUCHWALK)
		{
			//_state = STATE::CROUCHWALK;
			_position.x -= 1.0f;
		}

		else
		{                                       //만약 상태가 이동하면서 쏘고 잇으면 
			if (_state == STATE::WALK_SHOT)
			{
				_wstate = WALKSTATE::WALK;
				_state = STATE::WALK_SHOT;      //상태는 이동하면서 쏘는상태로 
			}
			else
			{
				_wstate = WALKSTATE::WALK;      //그렇지않으면 그냥 걷는상태로 
				_state = STATE::WALK;
			}
			_position.x -= 3.0f;
		}

		_angle = 3.14f;							//양수확인용앵글 각도가 양수일때는 양수전용 변수를 만든다 up키 누를시 
		_angle1 = -3.14f;						//음수확인용앵글 각도가 음수일때는 음수전용 변수를 만들어야한다 점프하고 아래보면서쏠떄
	}
	// 수정해야댐
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	//플레이어 오른쪽키 눌럿을시 
	{
		if (_bullet != BULLET::UPFIRE)
			_bullet = BULLET::RIGHTFIRE;		//오른쪾상태에서는 총알 오른쪽으로 나간다 
												//플레이어 오른쪽으로 움직임 
		_isLeft = false;						//오른쪽키눌르면 isleft는 false 
		if (_isJump == true)
		{
			if (_state == STATE::JUMP_SHOT)
			{
				_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMP_SHOT;
			}
			else if (_state == STATE::JUMP)
			{
				_wstate = WALKSTATE::JUMPWALK;
				_state = STATE::JUMPWALK;
			}
			else if (_state == STATE::JUMPWALK_UPSHOT)
			{
				_wstate = WALKSTATE::JUMPWALK;
				_state = STATE::JUMPWALK_UPSHOT;
			}


			/*	_wstate = WALKSTATE::JUMPWALK;
			_state = STATE::JUMPWALK;*/
			_position.x += 3.0f;
		}
		else if (_state == STATE::CROUCHWALK)
		{
			_position.x += 1.0f;
		}
		//else if (_state == STATE::WALK_SHOT)
		//{
		//	_wstate= WALKSTATE::
		//}
		else//점프 상태가 아니라면 
		{
			if (_state == STATE::WALK_SHOT)
			{
				_wstate = WALKSTATE::WALK;
				_state = STATE::WALK_SHOT;
			}
			else
			{
				_wstate = WALKSTATE::WALK;
				_state = STATE::WALK;
			}
			_position.x += 3.0f;
		}
		//_wstate = WALKSTATE::WALK;				//플레이어 상태 걷기(WALK)
		//	_state = STATE::WALK;
		_angle = 0.0f;							//오른쪽기준이니까 양수angel=0이다 
		_angle1 = 0.0f;							//오른쪽기준이라 음수용angle도 0이다 
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))		//플레이어 왼쪽키 땟을 때
	{
		_isLeft = true;
		if (_isJump == false)
		{
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}
		else
		{
			_wstate = WALKSTATE::JUMPWALK;
			_state = STATE::JUMPWALK;
		}
		_frameIndex = 0;


	}
	// 수정해야댐
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))		//플레이어 오른쪽키 땟을 때 
	{
		_isLeft = false;
		if (_isJump == false)
		{
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}
		else
		{
			//만약 점프상태일떄는
			_wstate = WALKSTATE::JUMPWALK;
			_state = STATE::JUMPWALK;
		}
		//_wstate = WALKSTATE::IDLE;				//플레이어 상태 기본(IDLE)
		//_state = STATE::IDLE;
		_frameIndex = -1; 						//프레임 인덱스 초기화
	}

	// ========================================================================
	// ###################### 플레이어 아래 눌렀을 때 ############################
	// ========================================================================
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))		//플레이어 아래쪽키 눌럿을시 
	{
		//_bullet = BULLET::DOWNATTACK;			//총알 앉아 쏘기 상태
		//_wstate = WALKSTATE::CROUCH;			//플레이어 상태 앉기(CROUCH)
		//_state = STATE::CROUCH;                 //기본으로 앉는모션


		_bullet = BULLET::DOWNATTACK;
		switch (_wstate)
		{
		case WALKSTATE::IDLE:
			_wstate = WALKSTATE::CROUCH;
			_state = STATE::CROUCH; //가만있는데 앉기 
			break;
		case WALKSTATE::WALK:                   //총쏘는 모션에서 다리모양으로 맞춰나서 
			_wstate = WALKSTATE::CROUCH;
			_state = STATE::CROUCHWALK;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))		//앉아 있다가 일어나면
	{											//플레이어의 isLeft를 확인 총알 상태 초기화
		if (_isLeft == true)
		{
			_bullet = BULLET::LEFTFIRE;
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}
		else
		{
			_bullet = BULLET::RIGHTFIRE;
			_wstate = WALKSTATE::IDLE;
			_state = STATE::IDLE;
		}

	}

	// ========================================================================
	// ###################### 플레이어 위 눌렀을 때 ############################
	// ========================================================================
	if (KEYMANAGER->isStayKeyDown(VK_UP))		//플레이어 up키를 누르면 
	{
		_bullet = BULLET::UPFIRE;				//위쪽상태에서는 총알 위쪽으로 나간다 


												//switch (_wstate)
												//{
												//case WALKSTATE::IDLE:
												//	_state = STATE::IDLE_UPSTARE;
												//	break;
												//case WALKSTATE::WALK:
												//	_state = STATE::WLAK_UPSTARE;
												//	break;
												//case WALKSTATE::JUMP:
												//	_state = STATE::JUMP_UPSTARE;
												//	break;
												//case WALKSTATE::JUMPWALK:
												//	_state = STATE::JUMPWALK_UPSTARE; 
												//	break;
												//
												//}

		if (_isLeft == true)					//왼쪽보고잇을시에는 
		{
			_angle -= 0.125f;
			if (_angle < PI / 2)
			{
				_angle = PI / 2;
			}
		}
		else
		{
			_angle += 0.125f;
			if (_angle > PI / 2)
			{
				_angle = PI / 2;
			}
		}
	}
	else {
		if (_isLeft == true)
		{
			_angle += 0.125f;
			if (_angle > 3.14f)
			{
				_angle = 3.14f;
			}
		}
		else
		{
			_angle -= 0.125f;
			if (_angle < 0)
			{
				_angle = 0.0f;
			}
		}
	}

	// ========================================================================
	// ###################### 플레이어 공격(A) 눌렀을 때 #########################
	// ========================================================================

	if (KEYMANAGER->isOnceKeyDown('A'))//A키를 눌럿을떄 
	{
		_playerbulletfire = true;
		if (_isLeft)
		{
			_frameIndex = 0;
		}
		else {
			_frameIndex = -1;
		}

		switch (_weapon)
		{
			// =====================================================================
			// ########################### 플레이어 딱총 #############################
			// =====================================================================
		case WEAPON::NORMAL:

			// =====================================================================
			// ####################### 플레이어 하체 상태 #############################
			// =====================================================================
			switch (_wstate)
			{

			case WALKSTATE::IDLE:

				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::IDLE_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::IDLE_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::IDLE_UPSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::WALK:
				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::WALK_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::WALK_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::WALK_UPSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::JUMP:
				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::JUMP_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::JUMP_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::JUMP_UPSHOT;
					break;
				case BULLET::DOWNFIRE:
					_state = STATE::JUMP_DOWNSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::JUMPWALK:
				switch (_bullet)
				{
				case BULLET::LEFTFIRE:
					_state = STATE::JUMPWALK_SHOT;
					break;
				case BULLET::RIGHTFIRE:
					_state = STATE::JUMPWALK_SHOT;
					break;
				case BULLET::UPFIRE:
					_state = STATE::JUMPWALK_UPSHOT;
					break;
				case BULLET::DOWNFIRE:
					_state = STATE::JUMPWALK_DOWNSHOT;
					break;
				case BULLET::IDLE:
					break;
				}
				break;

			case WALKSTATE::CROUCH:
				switch (_bullet)
				{
				case BULLET::DOWNATTACK:
					_state = STATE::CROUCHSHOT;
					break;
				}
				break;
			}

			break;


			// 나중에 추가하시면 댐

		case WEAPON::HEAVY:

			break;
		case WEAPON::SWORD:

			break;
		case WEAPON::GRENADE:

			break;
		default:
			break;
		}

	}

	// =======================================================================
	// ######################### 헤비 머신건 발사 ##############################
	// =======================================================================
	// 한번에 4발씩 발사한다.
	if (_hfire == true)
	{
		if (_time % 3 == 0) //0.03초마다 해비머신건이 발사된다 
		{
			switch (_bullet)
			{
			case BULLET::LEFTFIRE://왼쪽만 가는 헤비머신건 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10) /*_position.y*/, PI, 5.5f);
				break;
			case BULLET::RIGHTFIRE://오른쪽만 가는 헤비머신건 
				_playerbullet->fire(_position.x, RND->range(_position.y - 10, _position.y + 10), 0, 5.5f);
				break;
			case BULLET::UPFIRE://위에보면서 좌르륵가는거 
				_playerbullet->fire(_position.x, _position.y, _angle, 5.5f);
				break;
			case BULLET::DOWNFIRE://점프상태일떄 아래보면서 쏘는거 
				_playerbullet->fire(_position.x, _position.y, _angle1, 5.5f);
				break;
			case BULLET::DOWNATTACK://그냥 앉아서 쏘는거 
				_playerbullet->fire(_position.x, RND->range(_position.y + 10, _position.y + 30), _angle, 10.5f);
			case BULLET::IDLE:
				break;
			}
			_count++;//발사되고 count라는 변수를 1씩 증가시킨다
		}
	}
	if (_count == 4)//4번 됫다면 발사를 못하게한다  
	{
		_hfire = false;
		_count = 0;//다시 count는 0으로초기화한다 
	}

	// ========================================================================
	// ###################### 플레이어 점프(S) 눌렀을 때  #########################
	// ========================================================================
	if (KEYMANAGER->isOnceKeyDown('S') && _isJump == false)
	{
		_isJump = true;						//점프는 true가되고 
		_jumppower = 10.5f;					//점프힘에 10.5
		_gravity = 0.5f;					//중력값은 0.5

											// 걷고 있으면서 JUMP를 누르면 WLAKJUMP
											// 그냥 누르면 JUMP
		_wstate = WALKSTATE::JUMP;
		_state = STATE::JUMP;

	}



	// ========================================================================
	// ###################### 플레이어 점프(JUMP) 처리 ##########################
	// ========================================================================
	if (_isJump == true)
	{
		_position.y -= _jumppower;			//플레이어 y축은 점프힘만큼 빼준다  
		_jumppower -= _gravity;				//점프힘은 중력값만큼 빠진다 

											// ------- 점프 중 아래를 누르면 -------
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{//앉아잇기 앉아서 쏘기 앉아서 `` 앉아서 이동 
		 //플레이어 총알방향은 아래쪽이된다 
			_bullet = BULLET::DOWNFIRE;

			if (_isLeft == true)
			{
				_angle1 += 0.125f;
				if (_angle1 > -(PI / 2))
				{
					_angle1 = -(PI / 2);
				}
			}
			else if (_isLeft == false)
			{
				_angle1 -= 0.125f;
				if (_angle1 < -(PI / 2))
				{
					_angle1 = -(PI / 2);
				}
			}
		}
		else
			if (_isLeft == true)
			{
				_angle1 -= 0.125f;
				if (_angle1 < -PI)
				{
					_angle1 = -PI;
				}
			}
			else if (_isLeft == false)
			{
				_angle1 += 0.125f;
				if (_angle1 > 0)
				{
					_angle1 = 0.0f;
				}
			}
	}
	//점프상태가 아니고 총알방향이 아래쪽일떄는 
	//총알방향은 아무것도 안나가게 막아놧다 
	if (_isJump == false && _bullet == BULLET::DOWNFIRE)
	{
		_bullet = BULLET::IDLE;
	}
	// ========================================================
	if (_position.y > 400 && _isJump == true)		//플레이어 중점이 400보다 커지면 
	{
		_isJump = false;		//점프상태는 false로 바까준다 
		_wstate = WALKSTATE::IDLE;
		_state = STATE::IDLE;
	}
	// ========================================================




	//================================================칼충돌햇을시=========================
	//RECT temp;
	//if (IntersectRect(&temp, &PlayerRightSword,
	//	&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "몬스터")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "몬스터")->GetActive())
	//{//플레이어옆에 오른쪽렉트가 몬스타랑 충돌햇을시 칼상태를 소드로 바까준다 
	//	_weapon = WEAPON::SWORD;
	//	_sword = SWORD::RIGHTATTACK;
	//}
	//else if (IntersectRect(&temp, &PlayerLeftSword,
	//	&OBJECTMANAGER->FindObject(ObjectType::ENEMY, "몬스터")->GetRect()) && OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "몬스터")->GetActive())
	//{//플레이어옆에 왼쪽렉트가 몬스타랑 충돌햇을시 칼상태를 소드로 바까준다 
	//	_weapon = WEAPON::SWORD;
	//	_sword = SWORD::LEFTATTACK;
	//}
	//else
	//{//나중에 저장된 무기로 바까줄꺼다 
	//	_weapon = WEAPON::NORMAL;
	//}
	//if (SwordCount % 100 == 0)//칼모션이나가고 1초뒤에 false로바까 안보이게할려고 
	//{
	//	PlayerRealSwordState = false;
	//}


	if (KEYMANAGER->isOnceKeyDown('D') && _playerboomFire == false)//boomfire가 false일때만 수류탄던질수가있다 
	{
		//만약에 수류탄이 바닥이랑 충돌하면
		if (_isLeft == true)
		{
			_playerboom->fire(_position.x, _position.y, PI - 1.1f, 0.5f, 7.5f);
		}
		else
		{
			_playerboom->fire(_position.x, _position.y, 1.14f, 0.5f, 7.5f);
		}
	}
	if (_playerboom->GetPlayerBoomMax() <= 0)//플레이어 수류탄갯수 던지는거 처리는 bullet클래스boom에서 처리한다 
	{
		_playerboomFire = true;//true가 되면 던질수가없다 
	}




	this->UpdateRectByPivot();//렉트를 다시그려주는거 즉 업데이트에서 항시움직일려고  


							  //PlayerLeftSword = RectMake(_rc.left - 20, _rc.top, 20, 20);//안보이지만 실제 애랑충돌되면 weaponstate가 칼로바뀐다
							  //PlayerRightSword = RectMake(_rc.right, _rc.top, 20, 20);//안보이지만 실제 애랑충돌되면 weaponstate가 칼로바뀐다


							  //==============이미지
	this->PlayerMotionState();
	this->PlayerBulletMotion();
	_playerbullet->move();//플레이어 총알은 항시 움직이고 
	_playerboom->move();//플레이어 폭탄도 항심 움직인다  
}
// =====================================================================================================================================
// ####################################################### 플레이어 Render ##############################################################
// =====================================================================================================================================
void Player::Render()
{
	Rectangle(getMemDC(), CAMERA->Relative(_rc));//플레이어 렉트 보여주기 
	_playerbullet->Render(); //bullet에서 받아서 기본총 보여주기 

	_playerboom->Render();   //플레이어 폭탄 보여주기 

							 //Rectangle(getMemDC(), PlayerLeftSword); //실제충돌되는 렉트 확인용
							 //Rectangle(getMemDC(), PlayerRightSword);//실제충돌되는 렉트 확인용

							 //==수류탄갯수 확인용 
							 //char str[256];
							 //sprintf_s(str, "?=%d", _playerboom->GetPlayerBoomMax());
							 //TextOut(getMemDC(), 100, 100, str, strlen(str));

							 //플레이어 레프트모션이고 실제충돌칼이 true일떄만 충돌용소드를 그려준다
	if (_sword == SWORD::LEFTATTACK && PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealLeftSword);
	}
	//플레이어 오른쪽 모션이고 실제충돌칼이 true일떄만 충돌용소드를 그려준다
	if (_sword == SWORD::RIGHTATTACK && PlayerRealSwordState == true)
	{
		Rectangle(getMemDC(), PlayerRealRightSword);
	}

	//===================이미지============================================
	switch (_state)
	{
	case Player::STATE::IDLE:
		IMAGEMANAGER->frameRender("플레이어가만", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::WALK:
		IMAGEMANAGER->frameRender("플레이어이동", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::IDLE_SHOT:
		IMAGEMANAGER->frameRender("플레이어딱총공격", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::IDLE_UPSHOT:
		IMAGEMANAGER->frameRender("플레이어위딱총공격", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMP:
		IMAGEMANAGER->frameRender("플레이어기본점프", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::IDLE_UPSTARE:
		IMAGEMANAGER->frameRender("플레이어가만위보기", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::CROUCH:
		IMAGEMANAGER->frameRender("플레이어쭈그려", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::CROUCHWALK:
		IMAGEMANAGER->frameRender("플레이어쭈그려서이동", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::CROUCHSHOT:
		IMAGEMANAGER->frameRender("플레이어쭈그려공격", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMPWALK:
		IMAGEMANAGER->frameRender("플레이어좌우이동하며점프", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::WALK_SHOT:
		IMAGEMANAGER->frameRender("플레이어이동하며공격", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMP_SHOT:
		IMAGEMANAGER->frameRender("플레이어가만점프공격", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	case STATE::JUMPWALK_UPSHOT:
		IMAGEMANAGER->frameRender("플레이어이동하면서점프하고위에발사", getMemDC(), _rc.left - CAMERA->GetCamera().left, _rc.top - CAMERA->GetCamera().top);
		break;
	}
	// =====================================================================

	//====================디버그용 예시용도다 확인=============================
	//if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
	//	if (_weapon == WEAPON::NORMAL)
	//	{
	//		_weapon = WEAPON::HEAVY;
	//	}
	//	else {
	//		_weapon = WEAPON::NORMAL;
	//	}
	//}
	// =====================================================================
}

// =====================================================================================================================================
// ###################################################### 플레이어 모션 처리 ##############################################################
// =====================================================================================================================================
void Player::PlayerMotionState()
{
	switch (_state)
	{
	case STATE::IDLE:
		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("플레이어가만")->setFrameY(0);
			if (_frameCount % SPEED == 0) {
				_frameIndex++;
				if (_frameIndex > 3) {
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("플레이어가만")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("플레이어가만")->setFrameY(1);
			if (_frameCount % SPEED == 0) {
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 3;
				}

				IMAGEMANAGER->findImage("플레이어가만")->setFrameX(_frameIndex);
			}
		}
		//플레이어이동하면서점프하고위에발사
		break;
	case STATE::WALK:
		IMAGEMANAGER->findImage("플레이어이동")->setFrameY(0);
		_frameCount++;
		if (!_isLeft) {
			if (_frameCount % SPEED == 0) {
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 0;
				}
				IMAGEMANAGER->findImage("플레이어이동")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("플레이어이동")->setFrameY(1);
			if (_frameCount % SPEED == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("플레이어이동")->setFrameX(_frameIndex);
			}
		}
		break;
	case STATE::JUMP:
		IMAGEMANAGER->findImage("플레이어기본점프")->setFrameY(0);
		_frameCount++;
		if (!_isLeft)
		{
			if (_frameCount % 10 == 0) {
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("플레이어기본점프")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("플레이어기본점프")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("플레이어기본점프")->setFrameX(_frameIndex);
			}
		}
		break;
	case STATE::IDLE_UPSTARE:

		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("플레이어가만위보기")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("플레이어가만위보기")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("플레이어가만위보기")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("플레이어가만위보기")->setFrameX(_frameIndex);
			}
		}

		break;
		//플레이어쭈그려
	case STATE::CROUCH:

		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("플레이어쭈그려")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 3)
				{
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("플레이어쭈그려")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("플레이어쭈그려")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 3;
				}

				IMAGEMANAGER->findImage("플레이어쭈그려")->setFrameX(_frameIndex);
			}
		}
		break;

		//	플레이어쭈그려서이동
	case STATE::CROUCHWALK:

		_frameCount++;
		if (!_isLeft)
		{
			IMAGEMANAGER->findImage("플레이어쭈그려서이동")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 7)
				{
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("플레이어쭈그려서이동")->setFrameX(_frameIndex);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("플레이어쭈그려서이동")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0) {
					_frameIndex = 7;
				}

				IMAGEMANAGER->findImage("플레이어쭈그려서이동")->setFrameX(_frameIndex);
			}
		}
		break;
		//플레이어좌우이동하며점프
	case STATE::JUMPWALK:
		_frameCount++;
		if (_isLeft == false)
		{
			IMAGEMANAGER->findImage("플레이어좌우이동하며점프")->setFrameY(0);
			if (_frameCount % 10 == 0)
			{
				_frameIndex++;
				if (_frameIndex > 5)
				{
					_frameIndex = 0;
				}
				IMAGEMANAGER->findImage("플레이어좌우이동하며점프")->setFrameX(_frameIndex);
			}
		}//플레이어이동하면서점프하고위에발사
		else
		{
			IMAGEMANAGER->findImage("플레이어좌우이동하며점프")->setFrameY(1);
			if (_frameCount % 10 == 0)
			{
				_frameIndex--;
				if (_frameIndex < 0)
				{
					_frameIndex = 5;
				}

				IMAGEMANAGER->findImage("플레이어쭈그려서이동")->setFrameX(_frameIndex);
			}
		}
		break;
		//플레이어이동하며공격
	default:
		break;
	}
}


// =====================================================================================================================================
// ###################################################### 플레이어 (공격)모션 처리 ########################################################
// =====================================================================================================================================
void Player::PlayerBulletMotion()
{
	// A(공격) 눌렀을 때
	if (_playerbulletfire == true)
	{
		switch (_weapon)
		{
		case WEAPON::NORMAL:
			switch (_bullet)
			{
			case BULLET::RIGHTFIRE:
				switch (_wstate)
				{
				case WALKSTATE::WALK:
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어이동하며공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어이동하며공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, 0, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
						break;
					}
					break;
				case WALKSTATE::IDLE:
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어딱총공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{

							_frameIndex++;
							if (_frameIndex  >5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어딱총공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, 0, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}break;
					//============점프=====================
				case WALKSTATE::JUMP:
					_frameCount++;
					{
						if (_isLeft == false)
						{
							IMAGEMANAGER->findImage("플레이어가만점프공격")->setFrameY(0);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex++;
								if (_frameIndex > 5)
								{
									_frameIndex = 0;
								}
								IMAGEMANAGER->findImage("플레이어가만점프공격")->setFrameX(_frameIndex);
								if (_frameIndex == 0)
								{
									_playerbullet->fire(_position.x, _position.y, 0, 12.5f);
								}
								if (_frameIndex == 5)
								{
									_state = STATE::IDLE;
									_playerbulletfire = false;
								}
							}
							break;
						}
					}
					break;
				}
				break;
			case BULLET::LEFTFIRE:
				switch (_wstate)
				{
				case WALKSTATE::IDLE:
					_frameCount++;
					IMAGEMANAGER->findImage("플레이어딱총공격")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("플레이어딱총공격")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerbullet->fire(_position.x, _position.y, PI, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;
						}
					}
					break;
				case WALKSTATE::WALK:
					_frameCount--;
					if (_isLeft == true)
					{
						IMAGEMANAGER->findImage("플레이어이동하며공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어이동하며공격")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}

					}
					break;

				case WALKSTATE::JUMP:
					_frameCount--;
					if (_isLeft == true)
					{
						IMAGEMANAGER->findImage("플레이어가만점프공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어가만점프공격")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					break;
				}
				break;
			case BULLET::UPFIRE://점프 
				switch (_wstate)
				{
				case WALKSTATE::IDLE:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어위딱총공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어위딱총공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else//왼쪽모션
					{

						if (_frameCount % SPEED == 0)
						{
							IMAGEMANAGER->findImage("플레이어위딱총공격")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어위딱총공격")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}



					break;

				case WALKSTATE::JUMPWALK:
					//여기서 쓴다 플레이어이동하면서점프하고위에발사
					_frameCount++;
					IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameY(0);
					if (_isLeft == false)
					{
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::JUMPWALK;
								_playerbulletfire = false;
							}
						}
					}
				/*	else
					{
						_frameCount++; 
						IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5; 
							}
							IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameX(_frameIndex);
                     	   
						}
					}*/




					break;



				}


				break;
			case BULLET::DOWNFIRE:
				_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 12.5f);
				break;
			case BULLET::DOWNATTACK://플레이어쭈그려공격
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("플레이어쭈그려공격")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 9)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("플레이어쭈그려공격")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerbullet->fire(_position.x, _position.y + 20, _angle, 12.5f);
						}
						if (_frameIndex == 9)
						{
							_state = STATE::CROUCH;
							_playerbulletfire = false;
						}
					}
				}
				else//왼쪽모션
				{

					if (_frameCount % SPEED == 0)
					{
						IMAGEMANAGER->findImage("플레이어쭈그려공격")->setFrameY(1);
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 9;
						}
						IMAGEMANAGER->findImage("플레이어쭈그려공격")->setFrameX(_frameIndex);
						if (_frameIndex == 9)
						{
							_playerbullet->fire(_position.x, _position.y + 20, _angle, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::CROUCH;
							_playerbulletfire = false;
						}
					}
				}
				break;

				//_playerbullet->fire(_position.x, _position.y + 20, _angle, 12.5f);
			case BULLET::IDLE:
				break;
			}
			break;

		case WEAPON::HEAVY:
			_hfire = true;//fire발사가되면  
			break;

		case WEAPON::SWORD:

			switch (_sword)
			{
			case SWORD::LEFTATTACK:
				PlayerRealSwordState = true;
				PlayerRealLeftSword = RectMakeCenter(_rc.left - 20, _rc.top - 10, 40, 40);
				break;
			case SWORD::RIGHTATTACK:
				PlayerRealSwordState = true;
				PlayerRealRightSword = RectMakeCenter(_rc.right, _rc.top - 10, 20, 20);
				break;
			}
			break;
		}
	}

}

void Player::Checkstate()
{
	switch (_bullet)
	{
	case BULLET::LEFTFIRE:
		break;
	case BULLET::RIGHTFIRE:
		break;
	case BULLET::UPFIRE:
		break;
	case BULLET::DOWNFIRE:
		break;
	case BULLET::DOWNATTACK:
		break;
	case BULLET::IDLE:
		break;
	default:
		break;
	}
}

void Player::PlayerBoomMotion()
{
	if (_boomfire == true)
	{
		switch (_weapon)
		{
		case WEAPON::NORMAL:
			switch (_wstate)
			{
			case WALKSTATE::IDLE:
				//플레이어가만수류탄던지기
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("플레이어가만수류탄던지기")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("플레이어가만수류탄던지기")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x + 380, _position.y+ 100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}

					}
				}
				else
				{
					IMAGEMANAGER->findImage("플레이어가만수류탄던지기")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("플레이어가만수류탄던지기")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x+360, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
				}
				break;
			case WALKSTATE::WALK:
				//플레이어가만수류탄
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("플레이어이동수류탄")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("플레이어이동수류탄")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x+380, _position.y+100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
					break;
				}
				else
				{
					IMAGEMANAGER->findImage("플레이어이동수류탄")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("플레이어이동수류탄")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x + 360, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
					break;
				}
				break;
			case WALKSTATE::JUMP:
				_frameCount++;

				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("플레이어가만점프수류탄")->setFrameY(0);

					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;

						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("플레이어가만점프수류탄")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x+380, _position.y+100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}

					}
				}
				else
				{
					IMAGEMANAGER->findImage("플레이어가만점프수류탄")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("플레이어가만점프수류탄")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x+360, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_boomfire = false;
						}
					}
				}
				break;
			case WALKSTATE::JUMPWALK:
				break;
			case WALKSTATE::CROUCH:
				break;
			default:
				break;
			}
			break;
		case WEAPON::HEAVY:
			switch (_wstate)
			{
			case WALKSTATE::IDLE:
				//플레이어가만수류탄던지기
			
				break; 
			case WALKSTATE::JUMPWALK:
				break;
			case WALKSTATE::CROUCH:
				_frameCount++;

				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("해비앉아서수류탄")->setFrameY(0);

					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;

						if (_frameIndex > 5)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("해비앉아서수류탄")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerboom->fire(_position.x+370, _position.y+100, PI / 2 - 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 5)
						{
							_state = STATE::CROUCH;
							_boomfire = false;
						}

					}
				}
				else
				{
					IMAGEMANAGER->findImage("해비앉아서수류탄")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("해비앉아서수류탄")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerboom->fire(_position.x+370, _position.y+100, PI / 2 + 1.1f, 0.05f, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::CROUCH;
							_boomfire = false;
						}
					}
				}
			//	해비앉아서수류탄


				break;
			default:
				break;
			}
			break;
		case WEAPON::SWORD:
			break;
		case WEAPON::GRENADE:
			break;
		default:
			break;
		}

		
	}

}



void Player::PixelMapCollision()
{
	//

	_pixely = _position.y + 190; //여기가 애니메이션 맨아래부분 
	
	for (int i = _pixely- 5; i < _pixely + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 255 && b == 0) && _jumppower <= 0)
		{
			_jumppower = 0.0f; 
			_position.y = i-190;
			

			if (_isJump)
			{
				_state = STATE::IDLE;
				_isJump = false;
			}
		
			break; 
		}
	}

}

void Player::EnemyCollision()      //플레이어 기본딱총 
{
	RECT temp; 
	//for (int i = 0; i < _playerbullet->getVBullet().size(); i++)
	//{
	//	if(IntersectRect(&temp, &_playerbullet->getVBullet()[i].rc, &//몬스터 ))
	//}
}

