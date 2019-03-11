#include "stdafx.h"
#include "OldMan.h"
#include "Player.h"

OldMan::OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{
	//========================================================
	//���� ���� �� �̹��� ���� ���� �ʱ�ȭ 
	//========================================================
	_state = CAPTIVESTATE::R_MOVE;
	_count = 0;
	_index = 0;
	_isRight = false;
	_isCrush = false;
	_speed = 4.0f;			//���� �ӵ�
	_move = { 300, 500 };	//���� - �� 


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
	//���� �浹 ��Ʈ
	//========================================================
	//����
	_colRc[0] = RectMake(_rc.left + _size.x / 2, _rc.top + _size.y / 2, 10, 10);
	//������
	_colRc[1] = RectMake(_rc.right - _size.x / 2, _rc.top + _size.y / 2, 10, 10);

	//�Դٰ��ٰŸ�����
	if (_move.x > _rc.left) {
		_isRight == true;
	}
	if (_move.y < _rc.right) {
		_isRight = false;
	}
	//������ �ȱ�
	if (_isRight == true) {
		_position.x += _speed;
		_state = CAPTIVESTATE::R_MOVE;
	}
	//���� �ȱ�
	if (_isRight == false) {
		_position.x -= _speed;
		_state = CAPTIVESTATE::R_MOVE;
	}
	//���� �浹�� ������ ����ش�
	if (IntersectRect(&temp, &OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�")->GetRect(), &_colRc[0])) {
		_state = CAPTIVESTATE::R_THANKU;
		_isCrush = true;
	}
	if (IntersectRect(&temp, &OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�")->GetRect(), &_colRc[1])) {
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
