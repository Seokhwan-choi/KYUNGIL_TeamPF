#include "stdafx.h"
#include "Player.h"
#include "Monster.h"
#include "Crab.h"
#define SPEED 6

Player::Player(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_jumppower = 0.0f;								//플레이어 점프힘 
	_gravity = 0.02;								//플레이어 중력 
	_isJump = false;								//최초 점프안된상태 
	_playerboomFire = false;						//플레이어 폭탄상태 false일떄만 쏠수있고 true일시 폭탄사용불가하다 
	_time = 0;										//항상update되고 해비머신건발사시 4발정도 간격을 주기위하여 
	_count = 0;										//해비머신건이 발사됫을시 count가 4가되면 fire를 false로 만들기 위하여 
	_hfire = false;									//키를 누르면 true가되고 해비머신건이 발사가된다 
	_crab = ((Crab*)OBJECTMANAGER->FindObject(ObjectType::ENEMY, "crab"));
	
	//###########################플레이어 충돌랙트#################
	//collisionplayer = RectMakeCenter(_position.x, _position.y, 100, 100);


	// ================= 플레이어 총알 ============================= 
	_playerbullet = new Bullet1("플레이어 공용총알");
	_playerbullet->Init(800);//프레임이미지 range거리만 쓴다 

	
	//===============해비머신건 
	_heavyBullet = new Bullet("플레이어 해비");
	_heavyBullet->Init(800);

	//====================플레이어 픽셀=============================
    _pixely = _position.y + 190;//맨아래쪽 플레이어y축 충돌렉트 
	//_pixelx= _position.x + 
	//====================실제 플레이어 렉트=========================

	// ================= 플레이어 폭탄 =============================
	_playerboom = new Boom("플레이어 폭탄");
	_playerboom->Init("플레이어/수류탄.bmp", 720, 89, 2,WINSIZEY);

	//_InterPlayerRc = RectMakeCenter(_position.x + 75, _position.y + 130, 60, 95);//충돌렉트는 항심움직인다 

	_bullet = BULLET::RIGHTFIRE;					//플레이어 최초상태는 오른쪽보고 총알쏘는상태 
	//_weapon = WEAPON::NORMAL;
	_weapon = DATA->getWeapon();						//플레이어의 기본 총상태는 딱총상태이다 
	_sword = SWORD::RIGHTATTACK;					//칼은 기본적으로 오른쪽모션먼저세팅되어있다 
	_state = STATE::IDLE;
	PlayerRealSwordState = false;					//진짜 충돌할 칼의 bool 값 
	SwordCount = 0;									//칼 몆초뒤에 꺼주게할려고  				
	_playerbulletfire = false;						//총알 발사 눌렀냐?
	_frameCount = 0;								//프레임 카운트 초기화
	_frameIndex = 0;								//프레임 인덱스 초기화
	_isLeft = false;
	_normalangle = 0.0f; 
	_boomfire = false;                               //폭탄 발사됫냐?
													// ========================================== 플레이어 이미지 =======================================================
	IMAGEMANAGER->addFrameImage("플레이어가만", "플레이어/플레이어가만.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어딱총공격", "플레이어/기본딱총공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동", "플레이어/플레이어이동.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어위딱총공격", "플레이어/위기본딱총공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어기본점프", "플레이어/플레이어기본점프.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어가만위보기", "플레이어/플레이어가만위보기.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어쭈그려", "플레이어/플레이어쭈그려.bmp", 1280, 805, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어쭈그려서이동", "플레이어/플레이어쭈그려서이동.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어쭈그려공격", "플레이어/플레이어쭈그려공격.bmp", 3200, 805, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어좌우이동하며점프", "플레이어/플레이어좌우이동하며점프.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동하며공격", "플레이어/플레이어이동하며공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어가만점프공격", "플레이어/플레이어가만점프공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동하면서점프하고위에발사", "플레이어/플레이어이동하면서점프하고위에모션.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));//발사하는것 
	IMAGEMANAGER->addFrameImage("플레이어점프하면서공격","플레이어/플레이어점프하면서공격.bmp", 1920, 805,6,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("플레이어점프중위공격", "플레이어/플레이어점프중위공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동하며위에공격", "플레이어/플레이어이동하며위에공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어가만점프중아래공격", "플레이어/플레이어가만점프중아래공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어이동점프중아래공격", "플레이어/플레이어이동점프중아래공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
    
	//수류탄
	IMAGEMANAGER->addFrameImage("플레이어이동수류탄", "플레이어/플레이어이동수류탄.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어가만수류탄던지기", "플레이어/플레이어가만수류탄던지기.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어가만점프수류탄", "플레이어/플레이어가만점프수류탄.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));


	//해비머신건   // 160으로 고정한다 
	IMAGEMANAGER->addFrameImage("해비가만", "플레이어/해비가만.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));//아직안씀 render에 적긴적음 
	IMAGEMANAGER->addFrameImage("해비이동하며공격", "플레이어/해비이동하며공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비가만점프공격", "플레이어/해비가만점프공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비가만공격", "플레이어/해비가만공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비이동점프공격", "플레이어/해비이동점프공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비가만점프", "플레이어/해비가만점프.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비아래공격", "플레이어/해비아래공격.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비아래가만", "플레이어/해비아래가만.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비아래이동", "플레이어/해비아래이동.bmp", 2240, 805, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비이동하며점프", "플레이어/해비이동하며점프.bmp", 1600, 805, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비이동", "플레이어/해비이동.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비이동업샷", "플레이어/해비이동업샷.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비가만업샷","플레이어/해비가만업샷.bmp", 1920,805,6,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("해비고정용", "플레이어/해비고정용.bmp", 1280, 804, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("해비가만아래점프공격", "플레이어/해비가만아래점프공격.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비점프중아래보고가만", "플레이어/해비점프중아래보고가만.bmp", 1920, 402, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("해비앉아서수류탄", "플레이어/해비앉아서수류탄.bmp", 1920, 805, 6, 2, true, RGB(255, 0, 255));
     
	IMAGEMANAGER->addImage("낙하산", "플레이어/낙하산.bmp", 320, 403, true, RGB(255, 0, 255));

	_lifelive = false; 

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
	//_playerboom->release();
	//SAFE_DELETE(_playerboom);
	//
	//_heavyBullet->release();
	//SAFE_DELETE(_heavyBullet);
	//
	//_playerbullet->release();
	//SAFE_DELETE(_playerbullet);
}
//점프업샷을하고 walk_shot을 하면 이상 
void Player::Update()
{
	
	if (_lifelive == false)
	{
		SwordCount++;								//칼충돌됫을시 몆초뒤에 충돌박스 커주는 변수 
		_time++;									//해비머신건용 time변수 항시 update 

		//################낙하산#####################################
		//플레이어 상시중력 
		_position.y -= _jumppower;
		_jumppower -= _gravity;



													// ========================================================================
													// ####################### 플레이어 걷기(WALK) ##############################
													// ========================================================================
	
		if (_state != STATE::FLY)
		{

			if (CAMERA->GetWall() > _rc.left   - 175 )
			{
				_position.x =   _position.x+ CAMERA->GetWall() - (_rc.left - 175);
			}



			if (KEYMANAGER->isStayKeyDown(VK_LEFT))		//플레이어 왼쪽키 눌럿을시 
			{
				//	_bullet = BULLET::LEFTFIRE;				//왼쪽상태에서는 총알 왼쪽으로 나간다 
															//_state = STATE::CROUCHWALK
															//플레이어 움직임 
				if (_bullet != BULLET::UPFIRE && _bullet != BULLET::DOWNFIRE)
					_bullet = BULLET::LEFTFIRE;
				// && _bullet != BULLET::DOWNFIRE)
						//오른쪾상태에서는 총알 오른쪽으로 나간다 
			/*	else if (_bullet != BULLET::LEFTFIRE)
					_bullet = BULLET::DOWNFIRE;
				else if (_bullet != BULLET::DOWNFIRE)
					_bullet = BULLET::UPFIRE;*/

				_isLeft = true;							//왼쪽눌르면 isLeft는 true 
														//if (_isJump == true)
														//{
														//	_wstate = WALKSTATE::JUMPWALK;		//플레이어 하체 상태 점프걷기(JUMPWALK)
														//	_state = STATE::JUMPWALK; 
														//	_position.x -= 3.0f; 
														//}
				if (_isJump == true)
				{
					if (_state == STATE::JUMP_SHOT)                   //점프하면서 총쏘기
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_SHOT;
					}
					else if (_state == STATE::JUMPWALK_UPSHOT)
					{
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK_UPSHOT;
					}
					else if (_state == STATE::JUMP)
					{
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK;
					}
					else if (_state == STATE::JUMPWALK) {
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK;
					}
					else if (_state == STATE::JUMP_DOWNSTARE)
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_DOWNSTARE;
					}
					//else if (_state == STATE::JUMP_UPSHOT)
					//{
					//	_wstate = WALKSTATE::JUMP;
					//	_state = STATE::JUMP_UPSHOT; //점프중에 위로 공격하는것
					//}
					_position.x -= 3.0f;
				}


				else if (_state == STATE::CROUCHWALK)
				{
					//_state = STATE::CROUCHWALK;
					_position.x -= 1.0f;
				}
				else if (_state == STATE::CROUCHBOOM)
				{
					_wstate = WALKSTATE::CROUCH;
					_state = STATE::CROUCHBOOM;
				}

				else
				{                                       //만약 상태가 이동하면서 쏘고 잇으면 
					if (_state == STATE::WALK_SHOT)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_SHOT;      //상태는 이동하면서 쏘는상태로 
					}
					/*	else if (_state == STATE::WALK_UPSHOT )
						{
							_bullet = BULLET::UPFIRE;
							_angle = 3.14f;

							_angle -= 0.125f;
								if (_angle < PI / 2.0f)
								{
									_angle = PI / 2.0f;
								}
								if (_angle == PI / 2)
								{
									_wstate = WALKSTATE::IDLE;
									_state = STATE::WLAK_UPSTARE;
									_angle = PI / 2;
								}


							_wstate = WALKSTATE::WALK;
							_state = STATE::WALK_UPSHOT;


						}*/
					else if (_state == STATE::WALK_BOOM)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_BOOM;
					}
					else if (_state == STATE::WALK_UPSHOT)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_UPSHOT;
					}

					//if (_isLeft == true)					//왼쪽보고잇을시에는 
					//{
					//	_angle -= 0.125f;
					//	if (_angle < PI / 2.0f)
					//	{
					//		_angle = PI / 2.0f;
					//	}
					//	if (_angle == PI / 2)
					//	{
					//		_wstate = WALKSTATE::IDLE;
					//		_state = STATE::WLAK_UPSTARE;
					//		_angle = PI / 2;
					//	}

					//}

				/*	_angle -= 0.125f;
					if (_angle < PI / 2.0f)
					{
						_angle = PI / 2.0f;
					}
					if (_angle == PI / 2)
					{
						_wstate = WALKSTATE::IDLE;
						_state = STATE::WLAK_UPSTARE;
						_angle = PI / 2;
					}*/
					/*	else if (_state == STATE::JUMPWALK) {
							_wstate = WALKSTATE::JUMPWALK;
							_state = STATE::JUMPWALK;
						}*/
						/*	else if (_state == STATE::IDLE_BOOM)
							{
								_wstate = WALKSTATE::IDLE;
								_state = STATE::IDLE_BOOM;
							}*/

					else
					{
						_wstate = WALKSTATE::WALK;      //그렇지않으면 그냥 걷는상태로 
						_state = STATE::WALK;
					}
					_position.x -= 3.0f;
				}
				if (_state == STATE::WALK_UPSHOT)
				{
					//_angle -= 0.5f;
					_wstate = WALKSTATE::WALK;
					_state = STATE::WALK_UPSHOT;
				}
				else if (_state == STATE::JUMPWALK_DOWNSHOT)
				{
					_wstate = WALKSTATE::JUMPWALK;
					_state = STATE::JUMPWALK_DOWNSHOT;
				}
				else
				{
					_angle = 3.14f;							//양수확인용앵글 각도가 양수일때는 양수전용 변수를 만든다 up키 누를시 
					_angle1 = -3.14f;						//음수확인용앵글 각도가 음수일때는 음수전용 변수를 만들어야한다 점프하고 아래보면서쏠떄
				}
				_normalangle = PI;
			}
			// 수정해야댐

			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))	//플레이어 오른쪽키 눌럿을시 
			{

				_normalangle = 0.0f;
				if (_bullet != BULLET::UPFIRE && _bullet != BULLET::DOWNFIRE)
					_bullet = BULLET::RIGHTFIRE;		//오른쪾상태에서는 총알 오른쪽으로 나간다 
														//플레이어 오른쪽으로 움직임 
			/*	if (_bullet == BULLET::UPFIRE)
				{
					_bullet = BULLET::UPFIRE
				}
				else if (_bullet == BULLET::DOWNFIRE)
				{
					_bullet = BULLET::DOWNFIRE;
				}*/
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
					else if (_state == STATE::JUMPWALK) {
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK;
					}
					else if (_state == STATE::JUMPWALK_UPSHOT)
					{
						_wstate = WALKSTATE::JUMPWALK;
						_state = STATE::JUMPWALK_UPSHOT;
					}
					else if (_state == STATE::JUMP_DOWNSTARE)
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_DOWNSTARE;
					}
					/*else if (_state == STATE::JUMP_UPSHOT)
					{
						_wstate = WALKSTATE::JUMP;
						_state = STATE::JUMP_UPSHOT;
					}*/
					//else if (_state == STATE::JUMP_UPSHOT)
					//{
					//	_wstate = WALKSTATE::JUMP;
					//	_state = STATE::JUMP_UPSHOT; //점프중에 위로 공격하는것
					//}


					/*	_wstate = WALKSTATE::JUMPWALK;
					_state = STATE::JUMPWALK;*/
					_position.x += 13.0f;
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
					else if (_state == STATE::WALK_UPSHOT)
					{


						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_UPSHOT;
					}
					else if (_state == STATE::WALK_BOOM)
					{
						_wstate = WALKSTATE::WALK;
						_state = STATE::WALK_BOOM;
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
				if (_state == STATE::WALK_UPSHOT)
				{
					_wstate = WALKSTATE::WALK;
					_state = STATE::WALK_UPSHOT;
					//_angle -= 0.5f;
					//아무것도안쓰면 
					//이거 자체가 bullet up상태니까 여기가 자동으로 보정되니까 
				}
				else if (_state == STATE::JUMPWALK_DOWNSHOT)
				{
					_wstate = WALKSTATE::JUMPWALK;
					_state = STATE::JUMPWALK_DOWNSHOT;
				}
				else
				{
					_angle = 0.0f;							//오른쪽기준이니까 양수angel=0이다 
					_angle1 = 0.0f;							//오른쪽기준이라 음수용angle도 0이다 
				}

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
				_frameIndex = -1; 							//프레임 인덱스 초기화
			}

			// ========================================================================
			// ###################### 플레이어 아래 눌렀을 때 ############################
			// ========================================================================
			if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _isJump == false)		//플레이어 아래쪽키 눌럿을시 
			{
				//_normalangle = PI + PI / 2;

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
			if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _isJump == false)		//앉아 있다가 일어나면
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


				//if (_state == STATE::IDLE_UPSHOT ) 
				//{
				//	/*_wstate = WALKSTATE::IDLE;
				//	_state = STATE::IDLE_UPSHOT;*/
				//}
				switch (_weapon)
				{
				case WEAPON::NORMAL:
					if (_state == STATE::IDLE_UPSHOT)
					{
						_wstate = WALKSTATE::IDLE;
						_state = STATE::IDLE_UPSHOT;
					}
					break;
				case WEAPON::HEAVY:
					if (_state == STATE::IDLE_UPSHOT)
					{
						_wstate = WALKSTATE::IDLE;
						_state = STATE::WLAK_UPSTARE;
					}
					break;

				default:
					break;
				}

				_normalangle = PI / 2;
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
					if (_angle < PI / 2.0f)
					{
						_angle = PI / 2.0f;
					}
					if (_angle == PI / 2)
					{
						//_wstate = WALKSTATE::IDLE;
						//_state = STATE::WLAK_UPSTARE;
						_angle = PI / 2;
					}

				}
				else
				{
					_angle += 0.125f;
					if (_angle > PI / 2.0f)
					{
						_angle = PI / 2.0f;
					}
					if (_angle == PI / 2)
					{
						//_wstate = WALKSTATE::IDLE;
						//_state = STATE::WLAK_UPSTARE;
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
					if (_angle < 0.0f)
					{
						_angle = 0.0f;
					}
				}
			}
			if (KEYMANAGER->isOnceKeyUp(VK_UP))		//플레이어 up키를 누르면 
			{
				_bullet = BULLET::IDLE;
				_wstate = WALKSTATE::IDLE;
				_state = STATE::IDLE;
			}
			// ========================================================================
			// ###################### 플레이어 공격(A) 눌렀을 때 #########################
			// ========================================================================
			if (KEYMANAGER->isOnceKeyDown('A'))//A키를 눌럿을떄 
			{
				_playerbulletfire = true;// 동작을 랜더하겟다 
				if (_weapon == WEAPON::HEAVY)
				{
					_hfire = true;
				}

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
						_heavyBullet->fire(_position.x + 530, RND->range(_position.y +146, _position.y + 166) /*_position.y*/, _angle, 12.5f);  //20정도의 오차 
						break;
					case BULLET::RIGHTFIRE://오른쪽만 가는 헤비머신건 
						_heavyBullet->fire(_position.x + 900, RND->range(_position.y +146, _position.y+166 ), _angle, 12.5f);
						break;
					case BULLET::UPFIRE://위에보면서 좌르륵가는거 

						switch (_state)
						{
						case STATE::WALK_UPSHOT:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 675, _position.x +695), _position.y+100 , _angle, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 695, _position.x + 715), _position.y+100 , _angle, 12.5f);
							}
							break;
						case STATE::WLAK_UPSTARE:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 695, _position.x + 715), _position.y-15 , _angle, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 690, _position.x + 710), _position.y-15, _angle, 12.5f);
							}
							break;
						}

						break;
					case BULLET::DOWNFIRE://점프상태일떄 아래보면서 쏘는거 
						switch (_state)
						{
						case STATE::JUMP_DOWNSHOT:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 675, _position.x + 695), _position.y + 270, _angle1, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 700, _position.x + 720), _position.y + 270, _angle1, 12.5f);
							}
							break;
						case STATE::JUMPWALK_DOWNSHOT:
							if (_isLeft)
							{
								_heavyBullet->fire(RND->range(_position.x + 675, _position.x + 695), _position.y + 270, _angle1, 12.5f);
							}
							else if (!_isLeft)
							{

								_heavyBullet->fire(RND->range(_position.x + 700, _position.x + 720), _position.y + 270, _angle1, 12.5f);
							}
							break;
						}

						break;
					case BULLET::DOWNATTACK://그냥 앉아서 쏘는거 

						if (!_isLeft)
						{
							_heavyBullet->fire(_position.x + 890, RND->range(_position.y + 160, _position.y+180 ), _angle, 12.5f);
						}
						else {
							_heavyBullet->fire(_position.x + 510, RND->range(_position.y + 160, _position.y+180 ), _angle, 12.5f);
						}
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
				_gravity = 0.3f;					//중력값은 0.5

													// 걷고 있으면서 JUMP를 누르면 WLAKJUMP
													// 그냥 누르면 JUMP




				if (_wstate != WALKSTATE::JUMPWALK)
					_wstate = WALKSTATE::JUMP;

				//	_wstate = WALKSTATE::JUMP;
				_state = STATE::JUMP;

				//_wstate = WALKSTATE::JUMPWALK;
				//_state = STATE::JUMPWALK_DOWNSHOT;

			}



			// ========================================================================
			// ###################### 플레이어 점프(JUMP) 처리 ##########################
			// ========================================================================
			if (_isJump == true)
			{
				_position.y -= _jumppower;			//플레이어 y축은 점프힘만큼 빼준다  
				_jumppower -= _gravity;				//점프힘은 중력값만큼 빠진다 

				//	_wstate = WALKSTATE::JUMP; 
				//_state = STATE::JUMP_UPSHOT;

													// ------- 점프 중 아래를 누르면 -------
				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{//앉아잇기 앉아서 쏘기 앉아서 `` 앉아서 이동 
				 //플레이어 총알방향은 아래쪽이된다 
					_bullet = BULLET::DOWNFIRE;

					if (_state == STATE::JUMPWALK_DOWNSHOT)
					{
						_state = STATE::JUMPWALK_DOWNSHOT;
						_wstate = WALKSTATE::JUMPWALK;
					}
					else if (_state == STATE::JUMP_DOWNSHOT)

					{
						_state = STATE::JUMP_DOWNSHOT;
						_wstate = WALKSTATE::JUMP;
					}
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
			//**********************픽셀 

			//if (_position.y > 400 && _isJump == true)		//플레이어 중점이 400보다 커지면 
			//{
			//	_isJump = false;		//점프상태는 false로 바까준다 
			//	_wstate = WALKSTATE::IDLE;
			//	_state = STATE::IDLE;
			//}
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
				_boomfire = true;
				if (_isLeft)
				{
					_frameIndex = 0;
				}
				else {
					_frameIndex = -1;
				}
				//만약에 수류탄이 바닥이랑 충돌하면
				/*if (_isLeft == true)
				{
					_playerboom->fire(_position.x, _position.y, PI - 1.1f, 0.5f, 7.5f);
				}
				else
				{
					_playerboom->fire(_position.x, _position.y, 1.14f, 0.5f, 7.5f);
				}
		*///해비앉아서수류탄
				switch (_weapon)
				{
				case WEAPON::NORMAL:
					switch (_wstate)
					{
					case WALKSTATE::IDLE:
						_state = STATE::IDLE_BOOM;
						break;
					case WALKSTATE::WALK:
						_state = STATE::WALK_BOOM;
						break;
					case WALKSTATE::JUMP:
						_state = STATE::JUMP_BOOM;
						break;
					case WALKSTATE::JUMPWALK:
						_state = STATE::JUMPWALK_BOOM;
						break;
					case WALKSTATE::CROUCH:
						_state = STATE::CROUCHBOOM;

						break;
					default:
						break;
					}
					break;
				case WEAPON::HEAVY:
					switch (_wstate)
					{
					case WALKSTATE::IDLE:
						_state = STATE::IDLE_BOOM;
						break;
					case WALKSTATE::WALK:
						_state = STATE::WALK_BOOM;
						break;
					case WALKSTATE::JUMP:
						_state = STATE::JUMP_BOOM;
						break;
					case WALKSTATE::JUMPWALK:
						_state = STATE::JUMPWALK_BOOM;
						break;
					case WALKSTATE::CROUCH:
						_state = STATE::CROUCHBOOM;

						break;
					default:
						break;
					}
					break;
				case WEAPON::SWORD:
					break;
				case WEAPON::GRENADE:
					break;

				}


			}

		}
		if (_playerboom->GetPlayerBoomMax() <= 0)//플레이어 수류탄갯수 던지는거 처리는 bullet클래스boom에서 처리한다 
		{
			_playerboomFire = true;//true가 되면 던질수가없다 
		}


		check = RectMakeCenter(_position.x, _position.y + 52, 30, 30);
		this->UpdateRectByPivot();//렉트를 다시그려주는거 즉 업데이트에서 항시움직일려고  


								  //PlayerLeftSword = RectMake(_rc.left - 20, _rc.top, 20, 20);//안보이지만 실제 애랑충돌되면 weaponstate가 칼로바뀐다
								  //PlayerRightSword = RectMake(_rc.right, _rc.top, 20, 20);//안보이지만 실제 애랑충돌되면 weaponstate가 칼로바뀐다


								  //==============이미지
		this->PlayerMotionState();
		this->PlayerBulletMotion();
		this->PlayerBoomMotion();
		this->PixelMapCollision();
		_playerbullet->move();//플레이어 총알은 항시 움직이고 
		// 처음에는 _playerboom->move() 였다.
		// 인덱스 변하는건 Update()에 있어서
		// 폭탄이 한가지 모양으로만 나간다.
		_playerboom->Update();//플레이어 폭탄도 항심 움직인다  
		_heavyBullet->move();
		collisionplayer = RectMakeCenter(_position.x, _position.y+40, 100, 130);
		_colb = RectMakeCenter(_position.x, _position.y + _size.y / 2 - 100, 10, 10);
		_colr = RectMakeCenter(_position.x + _size.x / 2 - 120, _position.y + 35, 10, 10);
		//플레이어 충돌랙트는 항심움직인다 
		//_InterPlayerRc = RectMakeCenter(_position.x+75, _position.y+130, 60, 95);//충돌렉트는 항심움직인다 

	}
	
//	_temp = RectMakeCenter(_InterPlayerRc.left + 75, _InterPlayerRc.bottom, 15, 15);
}
// ====================================================================================================================================
// ####################################################### 플레이어 Render ##############################################################
// =====================================================================================================================================
void Player::Render()
{
	if (_lifelive == false)
	{
		RECT playerRC = CAMERA->Relative(_rc);
		RECT CHEK = CAMERA->Relative(check);
		
		RECT playercehck= CAMERA->Relative(collisionplayer);
		Rectangle(getMemDC(), CHEK);
		Rectangle(getMemDC(), CAMERA->Relative(_colb));
		Rectangle(getMemDC(), CAMERA->Relative(_colr));
		//플레이어 충돌랙트 
		Rectangle(getMemDC(), playercehck);


		//RECT interplayerrc= CAMERA->Relative(_InterPlayerRc);

		FrameRect(getMemDC(), &playerRC, HBRUSH(RGB(255, 0, 0)));
		
		
		//collisionplayer = RectMakeCenter(_position.x, _position.y, 100, 100);

		//FrameRect(getMemDC(), &CAMERA->Relative(_temp), HBRUSH(RGB(255, 0, 0)));
		_playerbullet->Render(); //bullet에서 받아서 기본총 보여주기 
		_heavyBullet->Render(); //해비머신건 

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
		switch (_weapon)
		{
		case WEAPON::NORMAL:
			switch (_state)
			{
			case Player::STATE::IDLE:
				IMAGEMANAGER->frameRender("플레이어가만", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK:
				//IMAGEMANAGER->frameRender("플레이어이동", getMemDC(), playerRC.left, playerRC.top);
				IMAGEMANAGER->frameRender("플레이어이동", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_SHOT:
				IMAGEMANAGER->frameRender("플레이어딱총공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_UPSHOT:
				IMAGEMANAGER->frameRender("플레이어위딱총공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP:
				IMAGEMANAGER->frameRender("플레이어기본점프", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_UPSTARE:
				IMAGEMANAGER->frameRender("플레이어가만위보기", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCH:
				IMAGEMANAGER->frameRender("플레이어쭈그려", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHWALK:
				IMAGEMANAGER->frameRender("플레이어쭈그려서이동", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHSHOT:
				IMAGEMANAGER->frameRender("플레이어쭈그려공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK:
				IMAGEMANAGER->frameRender("플레이어좌우이동하며점프", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_SHOT:
				IMAGEMANAGER->frameRender("플레이어이동하며공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_SHOT:
				IMAGEMANAGER->frameRender("플레이어가만점프공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_UPSHOT:
				IMAGEMANAGER->frameRender("플레이어이동하면서점프하고위에발사", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_SHOT:
				IMAGEMANAGER->frameRender("플레이어점프하면서공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_UPSHOT:
				IMAGEMANAGER->frameRender("플레이어점프중위공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_UPSHOT:
				IMAGEMANAGER->frameRender("플레이어이동하며위에공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_DOWNSHOT:
				IMAGEMANAGER->frameRender("플레이어가만점프중아래공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_DOWNSHOT:
				IMAGEMANAGER->frameRender("플레이어이동점프중아래공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::FLY:
				IMAGEMANAGER->render("낙하산",getMemDC(),playerRC.left, playerRC.top);
				break; 

				//수류탄 +++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			case STATE::WALK_BOOM:
				IMAGEMANAGER->frameRender("플레이어이동수류탄", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_BOOM:
				IMAGEMANAGER->frameRender("플레이어가만수류탄던지기", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_BOOM:
				IMAGEMANAGER->frameRender("플레이어가만점프수류탄", getMemDC(), playerRC.left, playerRC.top);
				break;

			}
			break;
		case WEAPON::HEAVY:
			/*해비이동하며공격
			해비가만*/
			switch (_state)
			{
			case STATE::IDLE_SHOT:
				IMAGEMANAGER->frameRender("해비가만공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE:
				IMAGEMANAGER->frameRender("해비가만", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_SHOT:
				IMAGEMANAGER->frameRender("해비이동하며공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_SHOT:
				IMAGEMANAGER->frameRender("해비가만점프공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK_SHOT:
				IMAGEMANAGER->frameRender("해비이동점프공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP:
				IMAGEMANAGER->frameRender("해비가만점프", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHSHOT:
				IMAGEMANAGER->frameRender("해비아래공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCH:
				IMAGEMANAGER->frameRender("해비아래가만", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHWALK:
				IMAGEMANAGER->frameRender("해비아래이동", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMPWALK:
				IMAGEMANAGER->frameRender("해비이동하며점프", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK:
				IMAGEMANAGER->frameRender("해비이동", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::WALK_UPSHOT:
				IMAGEMANAGER->frameRender("해비이동업샷", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::IDLE_UPSHOT:
				IMAGEMANAGER->frameRender("해비가만업샷", getMemDC(), playerRC.left, playerRC.top);
				break;
				//#############################################연습############################################
			case STATE::WLAK_UPSTARE:
				IMAGEMANAGER->frameRender("해비고정용", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_DOWNSHOT:
				IMAGEMANAGER->frameRender("해비가만아래점프공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::JUMP_DOWNSTARE:
				IMAGEMANAGER->frameRender("해비점프중아래보고가만", getMemDC(), playerRC.left, playerRC.top);
				break;

			case STATE::JUMPWALK_DOWNSHOT:
				IMAGEMANAGER->frameRender("해비가만아래점프공격", getMemDC(), playerRC.left, playerRC.top);
				break;
			case STATE::CROUCHBOOM:
				IMAGEMANAGER->frameRender("해비앉아서수류탄", getMemDC(), playerRC.left, playerRC.top);
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
		//===================이미지============================================

		// =====================================================================

		//====================디버그용 예시용도다 확인=============================
		if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
			if (_weapon == WEAPON::NORMAL)
			{
				_weapon = WEAPON::HEAVY;
			}
			else {
				_weapon = WEAPON::NORMAL;
			}
		}
		// =====================================================================
	

		//char str[128]; 
		//sprintf_s(&str,);
	}
	
//	Rectangle(getMemDC(), interplayerrc/*.left - playerRC.left, _InterPlayerRc.top - playerRC.top, _InterPlayerRc.right - playerRC.right, _InterPlayerRc.bottom - playerRC.bottom*/);
}

// =====================================================================================================================================
// ###################################################### 플레이어 모션 처리 ##############################################################
// =====================================================================================================================================
void Player::PlayerMotionState()
{

	switch (_weapon)  //무기상태 노말일때 
	{
	case WEAPON::NORMAL:
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

			_frameCount++;
			if (!_isLeft) {
				IMAGEMANAGER->findImage("플레이어이동")->setFrameY(0);
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
		break;
		//============================================================================================%%%%%%%%%%%%%%%%%%%%%
		//==================================================플레이어 해비 상태처리========================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
		//=============================================================================================================================
	case WEAPON::HEAVY:
		switch (_state)
		{
		case STATE ::JUMP_DOWNSTARE:
			//해비점프중아래보고가만
			IMAGEMANAGER->findImage("해비점프중아래보고가만")->setFrameY(0);
			if (_frameCount % SPEED == 0) {
				_frameIndex++;
				if (_frameIndex > 6) {
					_frameIndex = 0;
				}

				IMAGEMANAGER->findImage("해비점프중아래보고가만")->setFrameX(_frameIndex);
			}
			break;

		case STATE::IDLE:
			_frameCount++;
			if (!_isLeft)
			{
				IMAGEMANAGER->findImage("해비가만")->setFrameY(0);
				if (_frameCount % SPEED == 0) {
					_frameIndex++;
					if (_frameIndex > 3) {
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("해비가만")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("해비가만")->setFrameY(1);
				if (_frameCount % SPEED == 0) {
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 3;
					}

					IMAGEMANAGER->findImage("해비가만")->setFrameX(_frameIndex);
				}
			}
			//플레이어이동하면서점프하고위에발사
			break;
		case STATE::WALK:

			_frameCount++;
			if (!_isLeft) {
				IMAGEMANAGER->findImage("해비이동")->setFrameY(0);
				if (_frameCount % SPEED == 0) {
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("해비이동")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("해비이동")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 5;
					}

					IMAGEMANAGER->findImage("해비이동")->setFrameX(_frameIndex);
				}
			}
			break;
		case STATE::JUMP:
			IMAGEMANAGER->findImage("해비가만점프")->setFrameY(0);
			_frameCount++;
			if (!_isLeft)
			{
				if (_frameCount % SPEED == 0) {
					_frameIndex++;
					if (_frameIndex > 5)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("해비가만점프")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("해비가만점프")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 5;
					}

					IMAGEMANAGER->findImage("해비가만점프")->setFrameX(_frameIndex);
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
				IMAGEMANAGER->findImage("해비아래가만")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 3)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("해비아래가만")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("해비아래가만")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 3;
					}

					IMAGEMANAGER->findImage("해비아래가만")->setFrameX(_frameIndex);
				}
			}
			break;

			//	플레이어쭈그려서이동
		case STATE::CROUCHWALK:

			_frameCount++;
			if (!_isLeft)
			{
				IMAGEMANAGER->findImage("해비아래이동")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 6)
					{
						_frameIndex = 0;
					}

					IMAGEMANAGER->findImage("해비아래이동")->setFrameX(_frameIndex);
				}
			}
			else
			{
				IMAGEMANAGER->findImage("해비아래이동")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0) {
						_frameIndex = 6;
					}

					IMAGEMANAGER->findImage("해비아래이동")->setFrameX(_frameIndex);
				}
			}
			break;
			//플레이어좌우이동하며점프
		case STATE::JUMPWALK:
			_frameCount++;
			if (_isLeft == false)
			{
				IMAGEMANAGER->findImage("해비이동하며점프")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 4)
					{
						_frameIndex = 0;
					}
					IMAGEMANAGER->findImage("해비이동하며점프")->setFrameX(_frameIndex);
				}
			}//플레이어이동하면서점프하고위에발사
			else
			{
				IMAGEMANAGER->findImage("해비이동하며점프")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 0)
					{
						_frameIndex = 4;
					}

					IMAGEMANAGER->findImage("해비이동하며점프")->setFrameX(_frameIndex);
				}
			}
			break;
			//플레이어이동하며공격

		case STATE::WLAK_UPSTARE:        //up고정할 실험용 
			//_frameCount = 2;


			_frameCount++;
			if (_isLeft == false)
			{
				IMAGEMANAGER->findImage("해비고정용")->setFrameY(0);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex++;
					if (_frameIndex > 2)
					{
						_frameIndex = 2;
					}
					IMAGEMANAGER->findImage("해비고정용")->setFrameX(_frameIndex);
				}
			}//플레이어이동하면서점프하고위에발사
			else
			{
				IMAGEMANAGER->findImage("해비고정용")->setFrameY(1);
				if (_frameCount % SPEED == 0)
				{
					_frameIndex--;
					if (_frameIndex < 1)
					{
						_frameIndex =1;
					}

					IMAGEMANAGER->findImage("해비고정용")->setFrameX(_frameIndex);
				}
			}
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
								_playerbullet->fire(_position.x+ 183, _position.y , 0, 12.5f);
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
								_playerbullet->fire(_position.x+ 183, _position.y+15, 0, 12.5f);
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
									_playerbullet->fire(_position.x + 183, _position.y , 0, 12.5f);
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


					//=================jumpwalk right 
				case WALKSTATE::JUMPWALK:
					//플레이어점프하면서공격
					_frameCount++; 
					IMAGEMANAGER->findImage("플레이어점프하면서공격")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++; 
						if (_frameIndex > 5)
						{
							_frameIndex = 0; 
						}
						IMAGEMANAGER->findImage("플레이어점프하면서공격")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_playerbullet->fire(_position.x + 183, _position.y , 0, 12.5f);
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
			case BULLET::LEFTFIRE:
				switch (_wstate)
				{

				case WALKSTATE::JUMPWALK:
					//플레이어점프하면서공격
					_frameCount++;
					IMAGEMANAGER->findImage("플레이어점프하면서공격")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 5;
						}
						IMAGEMANAGER->findImage("플레이어점프하면서공격")->setFrameX(_frameIndex);
						if (_frameIndex == 5)
						{
							_playerbullet->fire(_position.x- 120, _position.y+ 15, PI, 12.5f);
						}
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;

						}

					}
					break;

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
							_playerbullet->fire(_position.x-120 , _position.y+15, PI, 12.5f);
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
								_playerbullet->fire(_position.x- 120, _position.y+ 15, PI, 12.5f);
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
								_playerbullet->fire(_position.x -120, _position.y+ 15, PI, 12.5f);
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
				case WALKSTATE::WALK:
					//플레이어이동하며위에공격
					_frameCount++; 
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어이동하며위에공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어이동하며위에공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x+ 30, _position.y-180, PI / 2, 12.5f);
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
							IMAGEMANAGER->findImage("플레이어이동하며위에공격")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어이동하며위에공격")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x+ 30, _position.y-180, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					break;

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
								_playerbullet->fire(_position.x+30 , _position.y - 180, PI / 2, 12.5f);
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
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
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
					_frameCount++; 
				{
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
						
					}
					else
					{
						IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 30, _position.y -180, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}

				}
					
					break;
				case WALKSTATE::JUMPWALK:
					//여기서 쓴다 플레이어이동하면서점프하고위에발사
					_frameCount++;
					
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameY(0);
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
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::JUMPWALK;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5; 
							}
							IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 30, _position.y - 180, PI / 2, 12.5f);
						   }
							if (_frameIndex == 0)
							{
								_state = STATE::JUMPWALK; 
								_playerbulletfire = false; 
							}
						}
					}
					break;
				}
				break;
			case BULLET::DOWNFIRE:
				//플레이어가만점프중아래공격
				switch (_wstate)
				{
				case WALKSTATE::JUMP:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어가만점프중아래공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어가만점프중아래공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x+ 30, _position.y+100, PI2 - (PI / 2), 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("플레이어가만점프중아래공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어가만점프중아래공격")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 22, _position.y + 120, PI2 - (PI / 2), 12.5f);
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
					//플레이어이동점프중아래공격
				
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어이동점프중아래공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("플레이어이동점프중아래공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_playerbullet->fire(_position.x + 41, _position.y + 100, PI2 - (PI / 2), 12.5f);
							}
							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("플레이어이동점프중아래공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어이동점프중아래공격")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x + 11, _position.y + 100, PI2 - (PI / 2), 12.5f);
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
				//_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 12.5f);
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
							_playerbullet->fire(_position.x+150, _position.y+45 , 0, 12.5f);
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
							_playerbullet->fire(_position.x-110, _position.y + 45, PI, 12.5f);
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
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//##################################해비머신건 ##################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################
			//#########################################################################################################


		case WEAPON::HEAVY:
			switch (_bullet)
			{
			case BULLET::RIGHTFIRE:
				switch (_wstate)
				{
				case WALKSTATE::WALK:
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("해비이동하며공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 3)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("해비이동하며공격")->setFrameX(_frameIndex);
							if (_frameIndex == 3)
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
						IMAGEMANAGER->findImage("해비가만공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 3)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("해비가만공격")->setFrameX(_frameIndex);				
							if (_frameIndex == 3)
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
							IMAGEMANAGER->findImage("해비가만점프공격")->setFrameY(0);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex++;
								if (_frameIndex > 3)
								{
									_frameIndex = 0;
								}
								IMAGEMANAGER->findImage("해비가만점프공격")->setFrameX(_frameIndex);
								if (_frameIndex == 3)
								{
									_state = STATE::IDLE;
									_playerbulletfire = false;
								}
							}
							break;
						}
					}




					break;


					//=================jumpwalk right 
				case WALKSTATE::JUMPWALK:
					//플레이어점프하면서공격
					_frameCount++;
					IMAGEMANAGER->findImage("해비이동점프공격")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 3)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("해비이동점프공격")->setFrameX(_frameIndex);
						if (_frameIndex == 3)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;

						}

					}

					break;
				}

				break;
			case BULLET::LEFTFIRE:
				switch (_wstate)
				{

				case WALKSTATE::JUMPWALK:
					//플레이어점프하면서공격
					_frameCount++;
					IMAGEMANAGER->findImage("해비이동점프공격")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 3;
						}
						IMAGEMANAGER->findImage("해비이동점프공격")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_state = STATE::IDLE;
							_playerbulletfire = false;

						}

					}
					break;

				case WALKSTATE::IDLE:
					_frameCount++;
					IMAGEMANAGER->findImage("해비가만공격")->setFrameY(1);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 3;
						}
						IMAGEMANAGER->findImage("해비가만공격")->setFrameX(_frameIndex);
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
						IMAGEMANAGER->findImage("해비이동하며공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 3;
							}
							IMAGEMANAGER->findImage("해비이동하며공격")->setFrameX(_frameIndex);
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
						IMAGEMANAGER->findImage("해비가만점프공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 3;
							}
							IMAGEMANAGER->findImage("해비가만점프공격")->setFrameX(_frameIndex);
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

				//해비이동업샷
			case BULLET::UPFIRE://점프 
				switch (_wstate)
				{
				case WALKSTATE::WALK:
					//플레이어이동하며위에공격
					_frameCount++;
					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("해비이동업샷")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("해비이동업샷")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}
					else//왼쪽모션
					{
						if (_frameCount % SPEED == 0)
						{
							IMAGEMANAGER->findImage("해비이동업샷")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("해비이동업샷")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}
					break;

				case WALKSTATE::IDLE:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("해비가만업샷")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("해비가만업샷")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}
					else//왼쪽모션
					{

						if (_frameCount % SPEED == 0)
						{
							IMAGEMANAGER->findImage("해비가만업샷")->setFrameY(1);
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("해비가만업샷")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::WLAK_UPSTARE;
								_playerbulletfire = false;
							}
						}
					}



					break;

				case WALKSTATE::JUMP:
					_frameCount++;
					{
						if (_isLeft == false)
						{
							IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameY(0);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex++;
								if (_frameIndex > 5)
								{
									_frameIndex = 0;
								}
								IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameX(_frameIndex);
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
						else
						{
							IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameY(1);
							if (_frameCount % SPEED == 0)
							{
								_frameIndex--;
								if (_frameIndex < 0)
								{
									_frameIndex = 5;
								}
								IMAGEMANAGER->findImage("플레이어점프중위공격")->setFrameX(_frameIndex);
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

					}

					break;
				case WALKSTATE::JUMPWALK:
					//여기서 쓴다 플레이어이동하면서점프하고위에발사
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameY(0);
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
					else
					{
						IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("플레이어이동하면서점프하고위에발사")->setFrameX(_frameIndex);
							if (_frameIndex == 5)
							{
								_playerbullet->fire(_position.x, _position.y, PI / 2, 12.5f);
							}
							if (_frameIndex == 0)
							{
								_state = STATE::JUMPWALK;
								_playerbulletfire = false;
							}
						}
					}
					break;
				}
				break;
			case BULLET::DOWNFIRE:
				//플레이어가만점프중아래공격
				switch (_wstate)
				{
				case WALKSTATE::JUMP:
					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameX(_frameIndex);

							if (_frameIndex == 5)
							{
								_state = STATE::JUMP_DOWNSTARE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::JUMP_DOWNSTARE;
								_playerbulletfire = false;
							}
						}
					}

					break;
				case WALKSTATE::JUMPWALK:
					//플레이어이동점프중아래공격

					_frameCount++;

					if (_isLeft == false)
					{
						IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameY(0);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex++;
							if (_frameIndex > 5)
							{
								_frameIndex = 0;
							}
							IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameX(_frameIndex);

							if (_frameIndex == 5)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}
					else
					{
						IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameY(1);
						if (_frameCount % SPEED == 0)
						{
							_frameIndex--;
							if (_frameIndex < 0)
							{
								_frameIndex = 5;
							}
							IMAGEMANAGER->findImage("해비가만아래점프공격")->setFrameX(_frameIndex);
							if (_frameIndex == 0)
							{
								_state = STATE::IDLE;
								_playerbulletfire = false;
							}
						}
					}

					break;


				}
				//_playerbullet->fire(_position.x, _position.y, PI2 - (PI / 2), 12.5f);
				break;
			case BULLET::DOWNATTACK://플레이어쭈그려공격
				_frameCount++;
				if (_isLeft == false)
				{
					IMAGEMANAGER->findImage("해비아래공격")->setFrameY(0);
					if (_frameCount % SPEED == 0)
					{
						_frameIndex++;
						if (_frameIndex > 3)
						{
							_frameIndex = 0;
						}
						IMAGEMANAGER->findImage("해비아래공격")->setFrameX(_frameIndex);
						if (_frameIndex == 3)
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
						IMAGEMANAGER->findImage("해비아래공격")->setFrameY(1);
						_frameIndex--;
						if (_frameIndex < 0)
						{
							_frameIndex = 3;
						}
						IMAGEMANAGER->findImage("해비아래공격")->setFrameX(_frameIndex);
						if (_frameIndex == 0)
						{
							_state = STATE::CROUCH;
							_playerbulletfire = false;
						}
					}
				}
				break;
			}
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
							_playerboom->fire(_position.x + 170, _position.y+ 150, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+70, _position.y+150, PI / 2 + 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+ 170, _position.y+150, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x + 70, _position.y+150, PI / 2 + 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+ 170, _position.y+150, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+70, _position.y+150, PI / 2 + 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+170, _position.y+180, PI / 2 - 1.1f, 0.05f, 12.5f);
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
							_playerboom->fire(_position.x+70, _position.y+180, PI / 2 + 1.1f, 0.05f, 12.5f);
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
	//collisionplayer = RectMakeCenter(_position.x + 130, _position.y + 220, 100, 140);
	
	_pixely = _colb.bottom; //여기가 애니메이션 맨아래부분 
	
	for (int i = _pixely; i < _pixely +140; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 255 && b == 0) && _jumppower <= 0)
		{
			_jumppower = 0.0f; 
			_position.y = i - 240;
			

			if ((_isJump) || _state==STATE::FLY)
			{
				_wstate = WALKSTATE::IDLE;
				_state = STATE::IDLE;
				_isJump = false;
				//_gravity = 0.0f; //픽셀충돌시에는 gravity는  0.0f가된다 
			}
			break; 
		}

	}

	_pixelx = _colr.right ;
	
	for (int i = _pixelx-15; i < _pixelx + 15; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, _position.y+150 );
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 255 && b == 0 && !_isLeft)/* && _jumppower <= 0*/)
		{
			_position.x = i - 50;
			//_gravity = 0.0f; //픽셀충돌시에는 gravity는  0.0f가된다 
			
			break;
		}
	
	}
}

//void Player::EnemyCollision()      //플레이어 기본딱총 
//{
//	RECT temp; 
//	for (int i = 0; i < _playerbullet->getVBullet().size(); i++)
//	{
//		cout << "ㅎㅎ " << endl;
//		if (IntersectRect(&temp, &_playerbullet->getVBullet()[i].rc, &_crab->getCol(2)  ) )//몬스터 ))
//		{//만약에 플레이어 기본총알과  애너미가 충돌햇을시 
//			//buulet1 기본총알의 공격력은 1인상태 
//			//((Crab*)OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "crab"))->setHp(((Crab*)OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "crab"))->getHp() - 1);
//
//			//exit(0);
//			//&((Crab*)OBJECTMANAGER->FindObject(ObjectType::Enum::ENEMY, "crab")).
//		}
//	}
//}
//
