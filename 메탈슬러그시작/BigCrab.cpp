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


	return S_OK;
}

void BigCrab::Release()
{
}

void BigCrab::Update()
{
	//�̵� �׽�Ʈ
	if (KEYMANAGER->isStayKeyDown('I')) {
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('P')) {
		_position.x += 5.f;
	}

	this->rectmove();
	this->Attcol();
	
}

void BigCrab::Render()
{
	//ī�޶� ��Ʈ �׸���
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _cam[i].rc);
	}
	//ū�� ��Ʈ �׸���
	Rectangle(getMemDC(), _rc);
	//ū�� �浹��Ʈ �׸���
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), _col[i].rc);
	}
}

void BigCrab::Attcol()
{
	RECT temp;
	if (IntersectRect(&temp, &_cam[0].rc, &player->GetRect()) && !IntersectRect(&temp,&_cam[1].rc,&player->GetRect()))
	{
		_cam[0].isCrush = true;
	}
	if (IntersectRect(&temp, &_cam[0].rc, &player->GetRect()) && IntersectRect(&temp, &_cam[1].rc, &player->GetRect()))
	{
		_cam[1].isCrush = true;
	}
	if (IntersectRect(&temp, &_cam[2].rc, &player->GetRect()))
	{
		_cam[2].isCrush = true;
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
}
