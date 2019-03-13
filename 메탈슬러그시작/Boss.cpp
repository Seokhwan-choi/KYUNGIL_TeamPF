#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "FireCannon.h"
#include "Bomb.h"

Boss::Boss(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

Boss::~Boss()
{
}

HRESULT Boss::Init()
{
	//상태 초기화
	_state = state::IDLE;
	//공격 처리를 위한 변수
	_angle = 0.f;
	//처음 등장 움직임 초기화
	_isStart = false;
	//근접 공격 타이머 초기화
	_attTimer = 0;
	//근접 공격 딜레이 초기화
	_attDelay = 30;
	//근접공격 전 정지 딜레이 초기화
	_stopDelay = 150;
	//뒤로 움직임 타이머 초기화
	_moveTimer = 0;
	//뒤로 버프 움직임 타이머
	_moveBuffTimer = 0;
	//뒤로 움직임 전 딜레이 초기화
	_moveDelay = 210;
	//공격 전 딜레이 타이머 초기화
	_delayTimer = 0;
	//움직임공격 유무 초기화
	_isMoveAttack = false;
	//공격 유무 초기화
	_isAttack = false;
	//움직임 공격 종료 유무 초기화
	_isAttackFinish = false;
	//보스 체력 초기화
	_hp = 300;
	//죽음 처리를 위한 변수
	_deathTimer = 0;
	//보스 버프 유무 초기화
	_isBuff = false;
	//보스 버프 등장 유무
	_isBuffStart = false;
	//보스 버프 등장 종료 유무
	_isBuffStartEnd = false;

	//보스 충돌 처리 렉트
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_position.x, _position.y, _size.x - 100.f, _size.y - 100.f);

	//보스 화염포 공격 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 2; i++)
	{
		_fShoot[i].pt = { _position.x, _position.y };
	}
	_fShoot[0].rc = RectMakeCenter(_fShoot[0].pt.x - 118.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);
	_fShoot[1].rc = RectMakeCenter(_fShoot[1].pt.x + 78.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);

	//보스 폭탄 공격 렉트(항상 몸 중앙을 따라 다닌다.)
	_bShoot.pt = { _position.x, _position.y };
	_bShoot.rc = RectMakeCenter(_bShoot.pt.x + 108.f, _bShoot.pt.y - _size.y / 2 + 230.f, 50, 50);

	//보스 근접 공격 렉트(항상 몸 중앙을 따라 다닌다.)
	_att.pt = { _position.x, _position.y };
	_att.rc = RectMakeCenter(_att.pt.x + _size.x / 2 - 100.f, _att.pt.y + 250.f, 300.f, 200.f);


	//플레이어 클래스 초기화
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "플레이어");

	//플레이어와의 각도 초기화
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//화염포 클래스 초기화
	_fireCannon = new FireCannon("화염포");
	_fireCannon->Init("입술.bmp", 30, 30, 5, 1200);

	//폭탄 클래스 초기화
	_bomb = new Bomb("미사일폭탄");
	_bomb->Init("입술.bmp", 30, 30, 1, 1200);

	//다리 이미지 초기화
	for (int i = 0; i < 22; i++)
	{
		string idx = to_string(i + 1);
		string key = "다리" + idx;

		_bridgeImg[i] = IMAGEMANAGER->findImage(key);
	}

	return S_OK;
}

void Boss::Release()
{
	//화염포 해제
	_fireCannon->Release();
	SAFE_DELETE(_fireCannon);

	//미사일폭탄 해제
	_bomb->Release();
	SAFE_DELETE(_bomb);
}

void Boss::Update()
{
	//근접공격 타이머
	if (_hp > 0)
	{
		_attTimer++;
	}

	//보스 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//보스 충돌 처리 렉트
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_position.x, _position.y, _size.x - 100.f, _size.y - 100.f);

	//보스 화염포 대포 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 2; i++)
	{
		_fShoot[i].pt = { _position.x, _position.y };
	}
	_fShoot[0].rc = RectMakeCenter(_fShoot[0].pt.x - 118.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);
	_fShoot[1].rc = RectMakeCenter(_fShoot[1].pt.x + 78.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);

	//보스 폭탄 대포 렉트(항상 몸 중앙을 따라 다닌다.)
	_bShoot.pt = { _position.x, _position.y };
	_bShoot.rc = RectMakeCenter(_bShoot.pt.x + 108.f, _bShoot.pt.y - _size.y / 2 + 230.f, 50, 50);

	//보스 근접 공격 렉트(항상 몸 중앙을 따라 다닌다.)
	_att.pt = { _position.x, _position.y };
	_att.rc = RectMakeCenter(_att.pt.x - 200.f, _att.pt.y + 250.f, 300.f, 200.f);

	//처음에 보스 등장 처리
	if (_rc.right < WINSIZEX / 2 - 50 && !_isStart && !_isBuffStart && !_isBuffStartEnd)
	{
		_position.x += 7.f;
	}

	//화면 중간 위치에 도달 하였을 때 등장 처리 완료
	if (_rc.right >= WINSIZEX / 2 - 50 && !_isBuffStart && !_isBuffStartEnd)
	{
		_isStart = true;
	}

	//버프 후 다시 등장 처리
	if (_isBuffStart && _rc.right < WINSIZEX / 2 - 50 && !_isBuffStartEnd)
	{
		_position.x += 9.f;
	}

	//화면 중간 위치에 도달 하였을 때 버프 등장 처리 완료
	if (_isBuffStart && _rc.right >= WINSIZEX / 2 - 50)
	{
		_isBuffStartEnd = true;
	}

	//버프상태가 아닐때 근접공격 딜레이 수정
	if (_isStart && !_isBuffStart && !_isBuffStartEnd)
	{
		_moveTimer++;
		_attDelay = 70;
	}
	//버프상태 일 때 움직임 타이머 시작
	if (_isBuffStartEnd)
	{
		_moveBuffTimer++;
	}

	//등장 완료 후 뒤로 움직이게 하는 타이머 시작
	if (_isStart && !_isAttack && !_isBuffStartEnd && _hp > 0)
	{
		//화염포 발사 명령
		if (_attTimer % 110 == 0 && _state != STATE::BACK_MOVE)
		{
			for (int i = 0; i < 5; i++)
			{
				this->fireShoot();
			}
		}
		
		//정해진 초 마다 뒤로 움직이게 명령
		if (_moveTimer % _moveDelay == 0)
		{
			_state = STATE::BACK_MOVE;
			_moveTimer = 0;
		}
	}
	//버프 등장 완료 후 뒤로 움직이게 하는 타이머 시작
	else if (!_isAttack && _isBuffStartEnd && _hp > 0)
	{
		//체력에 따른 발사 명령
		if (_attTimer % 60 == 0 && _state != STATE::BACK_MOVE)
		{
			this->fireBomb();
		}

		//정해진 초 마다 뒤로 움직이게 명령
		if (_moveBuffTimer % _moveDelay == 0)
		{
			_state = STATE::BACK_MOVE;
			_moveBuffTimer = 0;
		}
	}

	//앞으로 이동 공격 명령을 받았을 때 약간 대기
	if (_isAttack)
	{
		_delayTimer++;

		if (_delayTimer % _stopDelay == 0)
		{
			_state = STATE::ATTACK;
		}
	}

	//체력에 따른 상태 변경
	if (_hp > 150)
	{
		_isBuff = false;
		_stopDelay = 140;
		_moveDelay = 210;
	}
	else if (_hp == 150 && !_isBuffStart)
	{
		_position.x = -WINSIZEX / 4;
		_isBuffStart = true;
	}
	else if (_hp < 150 && _hp > 0)
	{
		_isBuff = true;
		_stopDelay = 30;
		_moveDelay = 150;
	}
	else if (_hp <= 0)
	{
		_hp = 0;
		_state = STATE::DEATH;
	}

	//상태에 따른 움직임 처리
	switch (_state)
	{
	case STATE::BACK_MOVE:
		if (_rc.right > 100.f)
		{
			if (!_isBuff)
			{
				_position.x -= 5;
			}
			else
			{
				_position.x -= 10;
			}
		}
		//뒤로 다 이동하였을 경우 앞으로 이동 공격 명령
		if (_rc.right <= 100.f)
		{
			_isAttack = true;
		}
		break;
	case STATE::ATTACK:
		//앞으로 이동 공격
		if (_rc.right < WINSIZEX / 2 - 50)
		{
			//체력에 따른 공격 속도 수정
			if (!_isBuff)
			{
				_position.x += 5;
				_attDelay = 35;
			}
			else
			{
				_position.x += 15;
				_attDelay = 25;
			}
		}

		//화면 중앙에서 대기 상태일 때
		if (_rc.right >= WINSIZEX / 2 - 50)
		{
			//체력에 따른 공격 딜레이 수정
			if (!_isBuff)
			{
				_attDelay = 70;
			}
			else
			{
				_attDelay = 55;
			}
			_isAttack = false;
		}
		break;
	case STATE::DEATH:
		if (_rc.top < WINSIZEY + 50)
		{
			_position.y += 2.5f;
		}

		break;
	}

	//설정한 초마다 근접 공격 처리
	if (_attTimer % _attDelay == 0
		|| _attTimer % _attDelay == 1
		|| _attTimer % _attDelay == 2
		|| _attTimer % _attDelay == 3
		|| _attTimer % _attDelay == 4
		|| _attTimer % _attDelay == 5)
	{
		_att.rc.left += 410.f;
		_att.rc.right += 410.f;
	}

	//다리 충돌 체크 임시 렉트
	RECT rc;
	//다리와 충돌 체크
	for (int i = 0; i < 22; i++)
	{
		if (IntersectRect(&rc, &_att.rc, &_bridgeImg[i]->boudingBox()))
		{
			//임시로 보냄
			_bridgeImg[i]->setX(-200);
		}
	}

	//반피 테스트
	if (KEYMANAGER->isStayKeyDown('O'))
	{
		_hp = 150;
	}
	//죽음 테스트
	if (KEYMANAGER->isStayKeyDown('P'))
	{
		_hp = 0;
	}

	//왼쪽,오른쪽 화염포 움직임 처리
	_fireCannon->Update();

	//미사일 폭탄 움직임 처리
	_bomb->Update();


	//좌우 움직임 테스트
	/*if (KEYMANAGER->isStayKeyDown('T'))
	{
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('U'))
	{
		_position.x += 5.f;
	}*/

	//근접 공격 테스트
	/*if (KEYMANAGER->isStayKeyDown('I'))
	{
		_att.rc.left += 600.f;
		_att.rc.right += 600.f;
	}*/
}

void Boss::Render()
{
	//보스 렉트 그리기
	Rectangle(getMemDC(), _rc);

	//충돌 렉트 그리기
	Rectangle(getMemDC(), _col.rc);

	//화염포 대포 렉트 그리기
	for (int i = 0; i < 2; i++)
	{
		Rectangle(getMemDC(), _fShoot[i].rc);
	}

	//화염포 그리기
	_fireCannon->Render();

	//폭탄 공격 처리 렉트 그리기
	Rectangle(getMemDC(), _bShoot.rc);

	//미사일 폭탄 그리기
	_bomb->Render();

	//근접 공격 처리 렉트 그리기
	Rectangle(getMemDC(), _att.rc);

	//텍스트 출력
	//sprintf(msg1, "_fireDist : %f", _fireDist);
	//TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));
}

//양쪽 화염포 발사 명령
void Boss::fireShoot()
{
	for (int i = 0; i < 2; i++)
	{
		float centerX = _fShoot[i].rc.left + (_fShoot[i].rc.right - _fShoot[i].rc.left) / 2;
		float centerY = _fShoot[i].rc.top + (_fShoot[i].rc.bottom - _fShoot[i].rc.top) / 2;

		if (i == 0)
		{
			_fireCannon->leftFire(centerX, centerY, PI / 180 * 35, 6.f);
		}
		else if (i == 1)
		{
			//발사할 당시의 플레이어 좌표
			_fireCannon->setPosition(_player->GetPosition().x, _player->GetPosition().y);

			_fireCannon->rightFire(centerX, centerY, PI / 180 * 30, 15.f);
		}
	}
}

//폭탄 발사 명령
void Boss::fireBomb()
{
	float centerX = _bShoot.rc.left + (_bShoot.rc.right - _bShoot.rc.left) / 2;
	float centerY = _bShoot.rc.top + (_bShoot.rc.bottom - _bShoot.rc.top) / 2;

	//발사할 당시의 플레이어 좌표
	_bomb->setPosition(_player->GetPosition().x, _player->GetPosition().y);

	_bomb->fire(centerX, centerY, PI / 180 * 20, 15.f);
}
