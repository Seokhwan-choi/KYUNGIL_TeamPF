#include "stdafx.h"
#include "BigCrab.h"
#include "Player.h"

BigCrab::BigCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}


BigCrab::~BigCrab()
{
}

HRESULT BigCrab::Init()
{
	//상태 초기화
	_state = state::L_IDLE;
	//게 카메라 렉트 초기화
	for (int i = 0; i < 3; i++)
	{
		_cam[i].pt = { _position.x,_position.y };
		_cam[i].isCrush = false;
	}
	_cam[0].rc = RectMakeCenter(_cam[0].pt.x, _cam[0].pt.y, _size.x * 5.f, _size.y);
	_cam[1].rc = RectMakeCenter(_cam[1].pt.x, _cam[1].pt.y, _size.x * 3.f, _size.y);
	_cam[2].rc = RectMakeCenter(_cam[2].pt.x, _cam[2].pt.y - 200, _size.x * 4.f, _size.y);
	//충돌 렉트 초기화
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x,_position.y };
	}
	//위쪽
	_col[0].rc = RectMakeCenter(_col[0].pt.x + 5, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	//아래쪽
	_col[1].rc = RectMakeCenter(_col[1].pt.x + 5, _col[1].pt.y + _size.y / 3 + 19, _size.x - 30, _size.y / 5);
	//오른쪽
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	//왼쪽
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);
	//플레이어 클래스 초기화
	player = (Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어");
	//공격용 렉트 초기화
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x,_position.y };
	}
	//왼쪽공격용 렉트
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 4, _att[0].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//오른쪽공격용 렉트
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 4 + 10, _att[1].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//카운트 초기화
	count = 0;
	//왼쪽입니다
	isLeft = true;
	//플레이어와의 각도 초기화
	_angle = GetAngle(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	return S_OK;
}

void BigCrab::Release()
{
}

void BigCrab::Update()
{

	//각도 체크
	_angle = GetAngle(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	//거리 체크
	_dist = GetDistance(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	//이동 테스트
	if (KEYMANAGER->isStayKeyDown('I')) {
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('P')) {
		_position.x += 5.f;
	}
	this->rectmove();
	this->Attcol();

	if (!_cam[0].isCrush && !_cam[1].isCrush && !_cam[2].isCrush)
	{
		_state = state::IDLE;
	}
	if (_state == state::IDLE)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			if (_dist > 300.f)
			{
				_position.x -= 5.f;
			}
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			if (_dist > 300.f)
			{
				_position.x += 5.f;
			}
		}

	}
	if (_cam[0].isCrush)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_BUBBLE_SHOOT_MOVE;
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_BUBBLE_SHOOT_MOVE;
		}
	}
	if (_cam[1].isCrush)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK;
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK;
		}
	}
	//if (_cam[2].isCrush)
	//{
	//	_state = state::L_ATTACK;
	//}

	if (_state == state::L_ATTACK)
	{
		_att[0].rc.left -= _size.x / 2 + 40;
		_att[0].rc.right -= _size.x / 2 + 40;
	}
	if (_state == state::R_ATTACK)
	{
		_att[1].rc.left += _size.x / 2 + 40;
		_att[1].rc.right += _size.x / 2 + 40;
	}
}

void BigCrab::Render()
{
	//카메라 렉트 그리기
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), CAMERA->Relative(_cam[i].rc));
	}
	//큰게 렉트 그리기
	Rectangle(getMemDC(), CAMERA->Relative(_rc));
	//큰게 충돌렉트 그리기
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), CAMERA->Relative(_col[i].rc));
	}
	//큰게 공격용렉트 그리기
	for (int i = 0; i < 2; i++)
	{
		Rectangle(getMemDC(), CAMERA->Relative(_att[i].rc));
	}
}

void BigCrab::Attcol()
{
	RECT temp;
	if (IntersectRect(&temp, &_cam[0].rc, &player->GetRect()) && !IntersectRect(&temp, &_cam[1].rc, &player->GetRect()))
	{
		_cam[0].isCrush = true;
	}
	else
	{
		_cam[0].isCrush = false;
	}
	if (IntersectRect(&temp, &_cam[0].rc, &player->GetRect()) && IntersectRect(&temp, &_cam[1].rc, &player->GetRect()))
	{
		_cam[1].isCrush = true;
	}
	else
	{
		_cam[1].isCrush = false;
	}
	if (IntersectRect(&temp, &_cam[2].rc, &player->GetRect()))
	{
		_cam[2].isCrush = true;
	}
	else
	{
		_cam[2].isCrush = false;
	}
}

void BigCrab::rectmove()
{
	//큰게 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
	//카메라 렉트 게 중심으로 따라다니게 하기
	for (int i = 0; i < 3; i++)
	{
		_cam[i].pt = { _position.x,_position.y };
	}
	_cam[0].rc = RectMakeCenter(_cam[0].pt.x, _cam[0].pt.y, _size.x * 4.f, _size.y);
	_cam[1].rc = RectMakeCenter(_cam[1].pt.x, _cam[1].pt.y, _size.x * 2.3f, _size.y);
	_cam[2].rc = RectMakeCenter(_cam[2].pt.x, _cam[2].pt.y - 200, _size.x * 3.f, _size.y / 2);
	//충돌 렉트 게 중심으로 따라다니게 하기
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x,_position.y };
	}
	//위쪽
	_col[0].rc = RectMakeCenter(_col[0].pt.x + 5, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	//아래쪽
	_col[1].rc = RectMakeCenter(_col[1].pt.x + 5, _col[1].pt.y + _size.y / 3 + 19, _size.x - 30, _size.y / 5);
	//오른쪽
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	//왼쪽
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//공격용 렉트 초기화
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x,_position.y };
	}
	//왼쪽공격용 렉트
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 4, _att[0].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//오른쪽공격용 렉트
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 4 + 10, _att[1].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);

}
