#include "stdafx.h"
#include "realPlayer.h"


realPlayer::realPlayer(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;
	_position = pos;
	_pivot = Pivot::LeftTop;
	_isActive = true;
	_isLive = true;
	this->UpdateRectByPivot();
}

realPlayer::~realPlayer()
{
}

HRESULT realPlayer::Init()
{
	return S_OK;
}

void realPlayer::Release()
{
}

void realPlayer::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_rc.left += 2.f;
		_rc.right += 2.f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_rc.left -= 2.f;
		_rc.right -= 2.f;
	}

	
}

void realPlayer::Render()
{
	Rectangle(getMemDC(), _rc);
}
