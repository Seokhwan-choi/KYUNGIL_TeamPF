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
	//물고기 초기화 상태
	_state = state::IDLE;
	//플레이어 클래스 초기화
	player = (Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어");
	//물고기 렉트 초기화
	for (int i = 0; i < 8; i++)
	{
		fish_rc[i].Fish_Rc = RectMakeCenter(_position.x, _position.y, 50, 30);
		fish_rc[i].isFish = false;
		fish_rc[i].count = 1;
	}
	//거리 조절
	_cam.isCrush = false;
	//카운터 초기화
	count = 1;
	return S_OK;
}

void Fish::Release()
{
}

void Fish::Update()
{
	//물고기 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
	//카메라 렉트
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
	//카메라 렉트 그리기
	Rectangle(getMemDC(), _cam.rc);
	//렉트 그리기
	Rectangle(getMemDC(), _rc);
	//물고기 렉트 그리기
	for (int i = 0; i < 8; i++)
	{
		if (_state == state::L_MOVE && fish_rc[i].isFish == true)
		{
			Rectangle(getMemDC(), fish_rc[i].Fish_Rc);
		}

	}
}
