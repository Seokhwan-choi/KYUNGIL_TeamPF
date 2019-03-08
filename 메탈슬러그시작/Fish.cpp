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
	for (int i = 0; i < 8; i++)
	{
		fish_rc[i].Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 30);
		fish_rc[i].isFish = false;
		fish_rc[i].count = 1;
	}
	//�Ÿ� ����
	_cam.isCrush = false;
	//ī���� �ʱ�ȭ
	count = 1;
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
		if (count % 30 == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				if (fish_rc[i].isFish == true)
				{
					continue;
				}
				fish_rc[i].isFish = true;
				break;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			if (fish_rc[i].isFish == true)
			{
				fish_rc[i].count++;
				if (fish_rc[i].count && fish_rc[i].count < 50)
				{
					fish_rc[i].Fish_Rc.top -= 3;
					fish_rc[i].Fish_Rc.bottom -= 3;
				}
				if (fish_rc[i].count > 50 && fish_rc[i].count < 100)
				{
					fish_rc[i].Fish_Rc.top += 2;
					fish_rc[i].Fish_Rc.bottom += 2;
					fish_rc[i].Fish_Rc.left -= 2;
					fish_rc[i].Fish_Rc.right -= 2;
				}
				if (fish_rc[i].count > 100)
				{
					fish_rc[i].Fish_Rc.left -= 5;
					fish_rc[i].Fish_Rc.right -= 5;
				}
				if (fish_rc[i].Fish_Rc.left < 0)
				{
					fish_rc[i].Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 30);
					fish_rc[i].count = 0;
				}
			}
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
	for (int i = 0; i < 8; i++)
	{
		if (_state == state::L_MOVE && fish_rc[i].isFish == true)
		{
			Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
		}

	}
}
