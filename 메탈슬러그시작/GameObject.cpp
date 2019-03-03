#include "stdafx.h"
#include "GameObject.h"


// ���ӿ�����Ʈ �����ڿ��� 
// ��� �̴ϼ� ����� ����ؼ� �ʱ�ȭ ���ش�.
GameObject::GameObject(string name, POINTFLOAT pos, POINTFLOAT size,Pivot pivot)
	:_name(name),_position(pos),_size(size),_pivot(pivot),_isActive(true),_isLive(true)
{
	// �ʱ�ȭ�� ��� ���� ���� �̿��ؼ�
	// RECT�� �׷��ش�.
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

// ��ǥ�� ����Ǿ����� RECT�� �ٽñ׷��ش�.
void GameObject::SetPosition(POINTFLOAT position)
{
	_position = position;
	this->UpdateRectByPivot();
}

// ũ�Ⱑ ����Ǿ����� RECT�� �ٽñ׷��ش�.
void GameObject::SetSize(POINTFLOAT size)
{
	 _size = size;
	 this->UpdateRectByPivot();
}

// RECT�� ����Ǿ����� RECT�� �ٽñ׷��ش�.
void GameObject::SetRect(RECT rc)
{
	this->_rc = rc;
	this->UpdateRectByPivot();
}

// pivot�� ����Ǿ����� RECT�� �ٽñ׷��ش�.
void GameObject::SetPivot(Pivot pivot)
{
	this->_pivot = pivot;
	this->UpdateRectByPivot();
}
// _pivot ���� ��������
// RECT�� �׷��ش�.
void GameObject::UpdateRectByPivot()
{
	switch (_pivot)
	{
	// ����, ž �������� RECT�� �׷��ش�. RectMake
	case GameObject::Pivot::LeftTop:
		this->_rc = RectMake(_position.x, _position.y, _size.x, _size.y);
		break;
	// ���͸� �������� RECT�� �׷��ش�. RectMakeCeter
	case GameObject::Pivot::Center:
		this->_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
		break;
	// ������ �������� RECT�� �׷��ش�. RectMakeBottom F12 ����
	case GameObject::Pivot::Bottom:
		this->_rc = RectMakeBottom(_position.x, _position.y, _size.x, _size.y);
		break;
	default:
		break;
	}
}
