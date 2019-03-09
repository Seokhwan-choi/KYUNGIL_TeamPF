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
			
			//여기서 이미지를 그려준다
			break;
		case ITEM::scoreup:
			//여기서 이미지를 그려준다
			break;
		case ITEM::tracer:
			//이미지를 그려준다
			break;
		default:
			break;
		}
	if (_isActive == true){
		Rectangle(getMemDC(), _rc);
	}
}
