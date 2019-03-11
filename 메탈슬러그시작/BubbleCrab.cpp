#include "stdafx.h"
#include "BubbleCrab.h"
#include "Player.h"
#include "Bubble.h"

BubbleCrab::BubbleCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

BubbleCrab::~BubbleCrab()
{
}

HRESULT BubbleCrab::Init()
{
	//상태 초기화
	_state = state::IDLE;
	_isStop = false;
	//공격 처리를 위한 변수
	_gauge = 1;
	_bubbleGauge = 1;
	_angle = 0.f;
	_isAttack = false;
	_isAttackFinish = false;
	_isBubbleShoot = false;
	_isBubbleShootFinish = false;
	_moveTimer = 1;
	//거품게 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//죽음 처리를 위한 변수
	_deathTimer = 0;

	//거품게 카메라 렉트(항상 몸 중앙을 따라다닌다.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 18.f, _size.y);
	_cam.isCrush = false;

	//거품게 충돌 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//거품게 공격 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x, _position.y };
	}
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 3, _att[0].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 3, _att[1].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);

	//플레이어 클래스 초기화
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "플레이어");

	//플레이어와의 각도 초기화
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//거품 클래스 초기화
	_bubble = new Bubble("거품");
	_bubble->Init("입술.bmp", 30, 30, 3, 1280);

	return S_OK;
}

void BubbleCrab::Release()
{
	_bubble->Release();
	SAFE_DELETE(_bubble);
}

void BubbleCrab::Update()
{
	//거품게 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//거품게 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//거품게 카메라 렉트(항상 몸 중앙을 따라다닌다.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 18.f, _size.y);

	//거품게 충돌 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//거품게 공격 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x, _position.y };
	}
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 3, _att[0].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 3, _att[1].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);

	//플레이어와 각도 체크
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//플레이어와 거리 체크
	_dist = GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//카메라와 충돌이 아닐 경우 대기 상태
	if (!_cam.isCrush)
	{
		_state = state::IDLE;
	}

	//플레이어 감지를 위한 카메라와 충돌 처리
	RECT rcCam;
	if (IntersectRect(&rcCam, &_cam.rc, &_player->GetRect()))
	{
		_cam.isCrush = true;
	}

	//카메라와 충돌일 경우 각도에 따른 움직임 상태
	if (_cam.isCrush && !_isStop)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_MOVE;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_MOVE;
		}
	}

	//플레이어와의 거리가 300.f보다 작고 플레이어와 충돌이 아닐 때 거품 발사를 위한 이동 명령
	if (!_isStop && _dist <= 300.f && _dist > 100.f)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_BUBBLE_SHOOT_MOVE;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_BUBBLE_SHOOT_MOVE;
		}

		//카메라 센서 정지
		_isStop = true;
	}
	//플레이어와 충돌일 경우 근접 공격 명령
	else if (_dist <= _player->GetSize().x / 2 + _size.x / 2)
	{
		_isAttack = true;
	}

	//근접 공격 중이 아닐 때 거품 공격 명령이 내려 지고 조금 기다린 다음 거품 발사
	if (_isBubbleShoot && !_isBubbleShootFinish && !_isAttack && !_isAttackFinish)
	{
		_bubbleGauge++;
	}

	//거품 한발씩 발사 처리
	if (_bubbleGauge % 50 == 0)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_bubble->fire(_position.x - 50.f, _position.y, _angle, 5.f);
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_bubble->fire(_position.x + 50.f, _position.y, _angle, 5.f);
		}

		//값 초기화
		_bubbleGauge = 1;
		_isBubbleShoot = false;
		_isBubbleShootFinish = true;
	}

	//발사 후 약간 앞으로 이동 처리
	if (_isBubbleShootFinish)
	{
		_moveTimer++;

		if (_moveTimer % 25 == 0)
		{
			if (_angle <= PI + PI / 2 && _angle > PI / 2)
			{
				_state = state::L_BUBBLE_SHOOT_FINISH;
			}


			if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
			{
				_state = state::R_BUBBLE_SHOOT_FINISH;
			}
		}
	}

	//근접 공격 명령이 내려졌을 때 근접 공격한 후 방향에 따른 근접 공격 처리
	if (_isAttack)
	{
		_gauge++;

		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK;
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK;
		}

		if (_gauge % 80 == 0)
		{
			_isAttack = false;
			_isAttackFinish = true;
			_gauge = 1;
		}
	}

	//근접 공격이 끝나면 뒤로 후퇴 처리
	if (_isAttackFinish)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK_FINISH;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK_FINISH;
		}
	}

	//상태에 따른 움직임 처리
	switch (_state)
	{
	case state::L_MOVE:
		if (_dist > 300.f)
		{
			_position.x -= 5.f;
		}
		break;
	case state::R_MOVE:
		if (_dist > 300.f)
		{
			_position.x += 5.f;
		}
		break;
	case state::L_BUBBLE_SHOOT_MOVE:
		if (_dist < 400.f && _rc.right <= WINSIZEX)
		{
			_position.x += 5.f;
		}
		//거품발사명령(끝 지점일 때도 플레이어와 충돌이 아닐 경우 거품 발사 명령)
		if (_dist >= 400.f || _rc.right >= WINSIZEX)
		{
			_isBubbleShoot = true;
		}
		break;
	case state::R_BUBBLE_SHOOT_MOVE:
		if (_dist < 400.f && _rc.left >= 0.f)
		{
			_position.x -= 5.f;
		}
		//거품발사명령(끝 지점일 때도 플레이어와 충돌이 아닐 경우 거품 발사 명령)
		if (_dist >= 400.f || _rc.left <= 0.f)
		{
			_isBubbleShoot = true;
		}
		break;
	case state::L_ATTACK:
		_att[0].rc.left -= _size.x / 4;
		_att[0].rc.right -= _size.x / 4;
		break;
	case state::R_ATTACK:
		_att[1].rc.left += _size.x / 4;
		_att[1].rc.right += _size.x / 4;
		break;
	case state::L_BUBBLE_SHOOT_FINISH:

		if (_dist > 300.f)
		{
			_position.x -= 5.f;
		}

		if (_dist <= 300.f || _rc.right <= WINSIZEX)
		{
			_isBubbleShootFinish = false;
			_isStop = false;
			_moveTimer = 1; 
		}

		break;
	case state::R_BUBBLE_SHOOT_FINISH:
		if (_dist > 300.f)
		{
			_position.x += 5.f;
		}

		if (_dist <= 300.f || _rc.left >= 0)
		{
			_isBubbleShootFinish = false;
			_isStop = false;
			_moveTimer = 1;
		}

		break;
	case state::L_ATTACK_FINISH:
		if (_dist <= 300.f && _rc.right <= WINSIZEX)
		{
			_position.x += 5.f;
		}
		if (_dist > 300.f || _rc.right >= WINSIZEX)
		{
			_isAttackFinish = false;
			_isStop = false;
		}
		break;
	case state::R_ATTACK_FINISH:
		if (_dist < 300.f && _rc.left >= 0)
		{
			_position.x -= 5.f;
		}
		if (_dist >= 300.f || _rc.left <= 0)
		{
			_isAttackFinish = false;
			_isStop = false;
		}
		break;
	}

	//거품 움직임 처리
	_bubble->move();
}

void BubbleCrab::Render()
{
	//카메라 렉트 그리기
	Rectangle(getMemDC(), _cam.rc);

	//렉트 그리기
	Rectangle(getMemDC(), _rc);

	//충돌렉트 그리기
	for (int i = 0; i < 4; i++)
	{
		//Rectangle(getMemDC(), _col[i].rc);
	}

	//시체처리렉트 그리기
	for (int i = 0; i < 3; i++)
	{
		//Rectangle(getMemDC(), _part[i].rc);
	}

	//공격처리렉트 그리기
	for (int i = 0; i < 2; i++)
	{
		Rectangle(getMemDC(), _att[i].rc);
	}
	//텍스트 출력
	//sprintf(msg1, "x : %f", _dist);
	//TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));

	//거품 그리기
	_bubble->Render();
}
