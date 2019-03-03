#include "stdafx.h"
#include "GameObject.h"


// 게임오브젝트 생성자에서 
// 멤버 이니셜 라이즈를 사용해서 초기화 해준다.
GameObject::GameObject(string name, POINTFLOAT pos, POINTFLOAT size,Pivot pivot)
	:_name(name),_position(pos),_size(size),_pivot(pivot),_isActive(true),_isLive(true)
{
	// 초기화된 멤버 변수 값을 이용해서
	// RECT를 그려준다.
	this->UpdateRectByPivot();
}
GameObject::GameObject(string name)
	: _name(name), _position({0,0}),_size({ 0,0 }), _pivot(Pivot::LeftTop), _isActive(true), _isLive(true)
{
	
}
GameObject::~GameObject()
{
}

HRESULT GameObject::Init()
{

	return S_OK;
}

void GameObject::Release()
{

}

void GameObject::Update()
{
	
}

void GameObject::Render()
{
}

// 좌표가 변경되었으니 RECT를 다시그려준다.
void GameObject::SetPosition(POINTFLOAT position)
{
	_position = position;
	this->UpdateRectByPivot();
}

// 크기가 변경되었으니 RECT를 다시그려준다.
void GameObject::SetSize(POINTFLOAT size)
{
	 _size = size;
	 this->UpdateRectByPivot();
}

// RECT가 변경되었으니 RECT를 다시그려준다.
void GameObject::SetRect(RECT rc)
{
	this->_rc = rc;
	this->UpdateRectByPivot();
}

// pivot이 변경되었으니 RECT를 다시그려준다.
void GameObject::SetPivot(Pivot pivot)
{
	this->_pivot = pivot;
	this->UpdateRectByPivot();
}
// _pivot 값을 기준으로
// RECT를 그려준다.
void GameObject::UpdateRectByPivot()
{
	switch (_pivot)
	{
	// 왼쪽, 탑 기준으로 RECT를 그려준다. RectMake
	case GameObject::Pivot::LeftTop:
		this->_rc = RectMake(_position.x, _position.y, _size.x, _size.y);
		break;
	// 센터를 기준으로 RECT를 그려준다. RectMakeCeter
	case GameObject::Pivot::Center:
		this->_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
		break;
	// 바텀을 기준으로 RECT를 그려준다. RectMakeBottom F12 ㄱㄱ
	case GameObject::Pivot::Bottom:
		this->_rc = RectMakeBottom(_position.x, _position.y, _size.x, _size.y);
		break;
	default:
		break;
	}
}
