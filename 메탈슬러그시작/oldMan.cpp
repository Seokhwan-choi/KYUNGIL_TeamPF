#include "stdafx.h"
#include "OldMan.h"
#include "Player.h"

OldMan::OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//========================================================
	//포로 상태 및 이미지 변수 관련 초기화 
	//========================================================
	_state = CAPTIVESTATE::R_MOVE;
	_count = 0;
	_index = 0;
	_isRight = false;
	_isCrush = false;
	_speed = 4.0f;			//포로 속도
	_move = { 300, 500 };	//시작 - 끝 


}

OldMan::~OldMan()
{
}

HRESULT OldMan::Init()
{
	return S_OK;
}

void OldMan::Release()
{
}

void OldMan::Update()
{
	RECT temp;
	_count++;
	//========================================================
	//포로 충돌 렉트
	//========================================================
	//왼쪽
	_colRc[0] = RectMake(_rc.left + _size.x / 2, _rc.top + _size.y / 2, 10, 10);
	//오른쪽
	_colRc[1] = RectMake(_rc.right - _size.x / 2, _rc.top + _size.y / 2, 10, 10);

	//왔다갔다거리게함
	if (_move.x > _rc.left) {
		_isRight == true;
	}
	if (_move.y < _rc.right) {
		_isRight = false;
	}
	//오른쪽 걷기
	if (_isRight == true) {
		_position.x += _speed;
		_state = CAPTIVESTATE::R_MOVE;
	}
	//왼쪽 걷기
	if (_isRight == false) {
		_position.x -= _speed;
		_state = CAPTIVESTATE::R_MOVE;
	}
	//만약 충돌시 아이템 뱉어준다
	if (IntersectRect(&temp, &OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "플레이어")->GetRect(), &_colRc[0])) {
		_state = CAPTIVESTATE::R_THANKU;
		_isCrush = true;
	}
	if (IntersectRect(&temp, &OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "플레이어")->GetRect(), &_colRc[1])) {
		_state = CAPTIVESTATE::L_THANKU;
		_isCrush = true;

	}



}

void OldMan::Render()
{
	switch (_state)
	{
	case CAPTIVESTATE::R_IDLE:

		break;
	case CAPTIVESTATE::L_IDLE:
		break;
	case CAPTIVESTATE::R_MOVE:
		break;
	case CAPTIVESTATE::L_MOVE:
		break;
	case CAPTIVESTATE::R_THANKU:
		break;
	case CAPTIVESTATE::L_THANKU:
		break;
	case CAPTIVESTATE::END:
		break;
	default:
		break;
	}
}

void OldMan::captive1()
{
}

void OldMan::captive2()
{
}
