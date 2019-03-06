#include "stdafx.h"
#include "crab.h"
#include "Player.h"

Crab::Crab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

Crab::~Crab()
{
}

HRESULT Crab::Init()
{
	//상태 초기화
	_state = state::L_IDLE;

	//이미지 초기화
	crab[0] = IMAGEMANAGER->addFrameImage("crab", "몬스터(게)-2.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	crab[1] = IMAGEMANAGER->addFrameImage("crab1", "몬스터(게)-2(오른쪽).bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	crab[2] = IMAGEMANAGER->addFrameImage("crab2", "몬스터(게)-3.bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	crab[3] = IMAGEMANAGER->addFrameImage("crab3", "몬스터(게)-3(오른쪽).bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	//이미지 랜더용 변수  초기화
	for (int i = 0; i < 2; i++)
	{
		index[i] = count[i] = 0;
	}
	//공격 처리를 위한 변수
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	_isAttackFinish = false;
	//게 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//죽음 처리를 위한 변수	
	_deathTimer = 0;

	//게 카메라 렉트(항상 몸 중앙을 따라다닌다.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 15.f, _size.y);
	_cam.isCrush = false;

	//게 충돌 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//게 공격 렉트(항상 몸 중앙을 따라 다닌다.)
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

	return S_OK;
}

void Crab::Release()
{
}

void Crab::Update()
{
	//마우스 좌표 담기
	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;

	//이동 테스트
	if (KEYMANAGER->isStayKeyDown('I')) {
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('P')) {
		_position.x += 5.f;
	}

	//게 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//게 시체처리 렉트
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//게 카메라 렉트(항상 몸 중앙을 따라다닌다.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 15.f, _size.y);

	//게 충돌 렉트(항상 몸 중앙을 따라 다닌다.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//게 공격 렉트(항상 몸 중앙을 따라 다닌다.)
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
		_state = state::L_IDLE;
	}

	//플레이어 감지를 위한 카메라와 충돌 처리
	RECT rcCam;
	if (IntersectRect(&rcCam, &_cam.rc, &_player->GetRect()))
	{
		_cam.isCrush = true;
	}

	//카메라와 충돌일 경우 각도에 따른 움직임 상태
	if (_cam.isCrush)
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

	//플레이어와의 거리가 300.f보다 작을때 공격을 위한 이동 상태로 변경
	if (_dist <= 300.f)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK_MOVE;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK_MOVE;
		}
	}

	//플레이어와의 접촉했을 때 공격 명령
	if (_dist <= _player->GetSize().x / 2 + _size.x / 2)
	{
		_isAttack = true;
	}
	
	//공격 명령이 내려졌을 때 조금 기다린 후 공격렉트를 움직임
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
		}
	}

	//공격이 끝나면 뒤로 후퇴 처리
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
	case state::L_ATTACK_MOVE:
		if (_dist > _player->GetSize().x / 2 + _size.x / 2)
		{
			_position.x -= 5.f;
		}
		break;
	case state::R_ATTACK_MOVE:
		if (_dist > _player->GetSize().x / 2 + _size.x / 2)
		{
			_position.x += 5.f;
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
	case state::L_ATTACK_FINISH:
		if (_dist < 320.f)
		{
			_position.x += 5.f;
			index[1] = 0;
		}
		if (_dist >= 300.f)
		{
			_isAttackFinish = false;
		}
		break;
	case state::R_ATTACK_FINISH:
		if (_dist < 320.f)
		{
			_position.x -= 5.f;
			index[1] = 11;
		}
		if (_dist >= 300.f)
		{
			_isAttackFinish = false;
		}
		break;
	}

	this->Crabimage();


}

void Crab::Render()
{
	//카메라 렉트 그리기
	Rectangle(getMemDC(), _cam.rc);

	//렉트 그리기
	Rectangle(getMemDC(), _rc);
	this->CrabimageRender();
	//충돌렉트 그리기
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), _col[i].rc);
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
	sprintf(msg1, "x : %d, y : %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));
}

void Crab::Crabimage()
{
	if ((_state == state::L_IDLE || _state == state::L_MOVE || _state == state::L_ATTACK_MOVE) && !(_state == state::L_ATTACK_FINISH))
	{
		count[0]++;
		if (count[0] % 10 == 0)
		{
			index[0]++;
			if (index[0] > 11)
			{
				index[0] = 0;
			}
			crab[0]->setFrameX(index[0]);
		}
	}
	if (_state == state::R_IDLE || _state == state::R_MOVE || _state == state::R_ATTACK_MOVE && !(_state == state::R_ATTACK_FINISH))
	{
		count[0]++;
		if (count[0] % 10 == 0)
		{
			index[0]++;
			if (index[0] > 11)
			{
				index[0] = 0;
			}
			crab[1]->setFrameX(index[0]);
		}
	}
	if (_state == state::L_ATTACK)
	{
		count[1]++;
		if (count[1] % 8 == 0)
		{
			index[1]++;
			if (index[1] > 11)
			{
				index[1] = 0;
			}
			crab[2]->setFrameX(index[1]);
		}
	}
	if (_state == state::R_ATTACK)
	{
		count[1]++;
		if (count[1] % 8 == 0)
		{
			index[1]--;
			if (index[1] < 0)
			{
				index[1] = 11;
			}
			crab[3]->setFrameX(index[1]);
		}
	}
	if (_state == state::L_ATTACK_FINISH)
	{
		count[2]++;
		if (count[2] % 10 == 0)
		{
			index[2]--;
			if (index[2] < 0)
			{
				index[2] = 11;
			}
			crab[0]->setFrameX(index[2]);
		}
	}
	if (_state == state::R_ATTACK_FINISH)
	{
		count[2]++;
		if (count[2] % 10 == 0)
		{
			index[2]--;
			if (index[2] < 0)
			{
				index[2] = 11;
			}
			crab[1]->setFrameX(index[2]);
		}
	}
}

void Crab::CrabimageRender()
{
	if ((_state == state::L_IDLE || _state == state::L_MOVE || _state == state::L_ATTACK_MOVE) && !(_state == state::L_ATTACK_FINISH))
	{
		crab[0]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::R_IDLE || _state == state::R_MOVE || _state == state::R_ATTACK_MOVE)
	{
		crab[1]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::L_ATTACK)
	{
			crab[2]->frameRender(getMemDC(), _rc.left -60, _rc.top - 22);
		
	}
	if (_state == state::R_ATTACK)
	{
		crab[3]->frameRender(getMemDC(), _rc.left + 10, _rc.top - 22);
	}
	if (_state == state::L_ATTACK_FINISH)
	{
		crab[0]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::R_ATTACK_FINISH)
	{
		crab[1]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
}
