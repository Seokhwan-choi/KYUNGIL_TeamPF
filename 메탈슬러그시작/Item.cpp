#include "stdafx.h"
#include "Item.h"




Item::Item(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	: GameObject(name, pos, size, pivot)
{
	_name = name;
	_position = pos;
	_size = size;
	_pivot = Pivot::LeftTop;
	this->UpdateRectByPivot();
	_isActive = false;
}

Item::~Item()
{
}

HRESULT Item::Init()
{
	return S_OK;
}

void Item::Release()
{
}

void Item::Update()
{
}

void Item::Render()
{
		switch (_oldmanItem)
		{
		case ITEM::haevy:
			
			//���⼭ �̹����� �׷��ش�
			break;
		case ITEM::scoreup:
			//���⼭ �̹����� �׷��ش�
			break;
		case ITEM::tracer:
			//�̹����� �׷��ش�
			break;
		default:
			break;
		}
	if (_isActive == true){
		Rectangle(getMemDC(), _rc);
	}
}
