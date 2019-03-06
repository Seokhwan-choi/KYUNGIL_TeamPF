#include "stdafx.h"
#include "Fish.h"
#include "Player.h"



Fish::Fish(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}


Fish::~Fish()
{
}

HRESULT Fish::Init()
{
	//����� �ʱ�ȭ ����
	_state = state::IDLE;
	//�÷��̾� Ŭ���� �ʱ�ȭ
	player = (Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�");
	//����� ��Ʈ �ʱ�ȭ
	Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 50);
	//�Ÿ� ����
	_cam.isCrush = false;
	//ī���� �ʱ�ȭ
	count = 0;
	return S_OK;
}

void Fish::Release()
{
}

void Fish::Update()
{
	//����� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
	//ī�޶� ��Ʈ
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 13.5f, _size.y);
	
	if (!_cam.isCrush)
	{
		_state = state::IDLE;
	}
	RECT rcCam;
	if (IntersectRect(&rcCam, &_cam.rc, &player->GetRect()))
	{
		_cam.isCrush = true;
	}
	if (_cam.isCrush)
	{
		_state = state::L_MOVE;
	}
	if (_state == state::L_MOVE)
	{
		count++;
		if (count > 0 && count < 50)
		{
			Fish_Rc.top -= 2;
			Fish_Rc.bottom -= 2;
		}
		if (count > 50 && count < 100)
		{
			Fish_Rc.top += 2;
			Fish_Rc.bottom += 2;
			Fish_Rc.left -= 2;
			Fish_Rc.right -= 2;
		}
		if (count > 100)
		{
			Fish_Rc.left -= 5;
			Fish_Rc.right -= 5;
		}
		if (Fish_Rc.left < 0)
		{
			Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 50);
			count = 0;
		}
	}

}

void Fish::Render()
{
	//ī�޶� ��Ʈ �׸���
	Rectangle(getMemDC(), _cam.rc);
	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);
	//����� ��Ʈ �׸���
	if (_state == state::L_MOVE)
	{
		Rectangle(getMemDC(), Fish_Rc);
	}
	
}
