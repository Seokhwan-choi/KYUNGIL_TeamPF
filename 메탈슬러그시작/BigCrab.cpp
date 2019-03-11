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
	//���� �ʱ�ȭ
	_state = state::L_IDLE;
	//�� ī�޶� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < 3; i++)
	{
		_cam[i].pt = { _position.x,_position.y };
		_cam[i].isCrush = false;
	}
	_cam[0].rc = RectMakeCenter(_cam[0].pt.x, _cam[0].pt.y, _size.x * 5.f, _size.y);
	_cam[1].rc = RectMakeCenter(_cam[1].pt.x, _cam[1].pt.y, _size.x * 3.f, _size.y);
	_cam[2].rc = RectMakeCenter(_cam[2].pt.x, _cam[2].pt.y - 200, _size.x * 4.f, _size.y);
	//�浹 ��Ʈ �ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x,_position.y };
	}
	//����
	_col[0].rc = RectMakeCenter(_col[0].pt.x + 5, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	//�Ʒ���
	_col[1].rc = RectMakeCenter(_col[1].pt.x + 5, _col[1].pt.y + _size.y / 3 + 19, _size.x - 30, _size.y / 5);
	//������
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	//����
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);
	//�÷��̾� Ŭ���� �ʱ�ȭ
	player = (Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�");
	//���ݿ� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x,_position.y };
	}
	//���ʰ��ݿ� ��Ʈ
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 4, _att[0].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//�����ʰ��ݿ� ��Ʈ
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 4 + 10, _att[1].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//ī��Ʈ �ʱ�ȭ
	count = 0;
	//�����Դϴ�
	isLeft = true;
	//�÷��̾���� ���� �ʱ�ȭ
	_angle = GetAngle(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	return S_OK;
}

void BigCrab::Release()
{
}

void BigCrab::Update()
{

	//���� üũ
	_angle = GetAngle(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	//�Ÿ� üũ
	_dist = GetDistance(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	//�̵� �׽�Ʈ
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
	//ī�޶� ��Ʈ �׸���
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), CAMERA->Relative(_cam[i].rc));
	}
	//ū�� ��Ʈ �׸���
	Rectangle(getMemDC(), CAMERA->Relative(_rc));
	//ū�� �浹��Ʈ �׸���
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), CAMERA->Relative(_col[i].rc));
	}
	//ū�� ���ݿ뷺Ʈ �׸���
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
	//ū�� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
	//ī�޶� ��Ʈ �� �߽����� ����ٴϰ� �ϱ�
	for (int i = 0; i < 3; i++)
	{
		_cam[i].pt = { _position.x,_position.y };
	}
	_cam[0].rc = RectMakeCenter(_cam[0].pt.x, _cam[0].pt.y, _size.x * 4.f, _size.y);
	_cam[1].rc = RectMakeCenter(_cam[1].pt.x, _cam[1].pt.y, _size.x * 2.3f, _size.y);
	_cam[2].rc = RectMakeCenter(_cam[2].pt.x, _cam[2].pt.y - 200, _size.x * 3.f, _size.y / 2);
	//�浹 ��Ʈ �� �߽����� ����ٴϰ� �ϱ�
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x,_position.y };
	}
	//����
	_col[0].rc = RectMakeCenter(_col[0].pt.x + 5, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	//�Ʒ���
	_col[1].rc = RectMakeCenter(_col[1].pt.x + 5, _col[1].pt.y + _size.y / 3 + 19, _size.x - 30, _size.y / 5);
	//������
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	//����
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//���ݿ� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x,_position.y };
	}
	//���ʰ��ݿ� ��Ʈ
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 4, _att[0].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//�����ʰ��ݿ� ��Ʈ
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 4 + 10, _att[1].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);

}
