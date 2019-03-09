#include "stdafx.h"
#include "oldMan.h"
#include "Item.h"
#include "realPlayer.h"

oldMan::oldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;
	_position = pos;
	_pivot = Pivot::LeftTop;
	_isActive = true;
	_isLive = true;
	_isRight = true;
	this->UpdateRectByPivot();

}

HRESULT oldMan::Init()
{

	return S_OK;
}

void oldMan::Release()
{
}

void oldMan::Update()
{
	if (_isRight == true)
	{
		_rc.left += 2.f;
		_rc.right += 2.f;
		if (_rc.right > WINSIZEX)
		{
			_isRight = false;
		}
	}
	else if (_isRight == false)
	{
		_rc.left -= 2.f;
		_rc.right -= 2.f;
		if (_rc.left < (WINSIZEX / 4) * 3)
		{
			_isRight = true;
		}
	}
	//만약 충돌됐다 1노인이랑 -플레이어랑
	// 2번쨰 노인 - 플레이어
	//3번째 노인 - 플레이어
	RECT temp;
	temp = RectMake(0, 0, 0, 0);
	if (IntersectRect(&temp, &_rc, &OBJECTMANAGER->FindObject(ObjectType::Enum::Object, "realplayer")->GetRect())) {
		OBJECTMANAGER->FindObject(ObjectType::Enum::Object, "item")->SetisActive(true);
		//OBJECTMANAGER->FindObject(ObjectType::Enum::Object, "Item")->GetRect();
		
	}
	_colRc = RectMake(_rc.left - 10, _rc.top + 50, 20, 20);

}

void oldMan::Render()
{
	Rectangle(getMemDC(), _rc);
	Rectangle(getMemDC(), _colRc);
}

oldMan::~oldMan()
{
}