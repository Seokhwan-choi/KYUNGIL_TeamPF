#include "stdafx.h"
#include "Monster.h"


Monster::Monster(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name,pos,size,pivot)
{
	_name = name; //클래스 이름설정해둔다 
	_position = pos; //좌표 초기화 해준다 
	_size = size; //사이즈 초기화해준다 
	_pivot = Pivot::Center; //피벗위치잡아준다 
	this->UpdateRectByPivot(); //RECT그려준다 
	_isActive = true; //활성화되어있다
	_isLive = true; //살아있다 
	
}


Monster::~Monster()
{
}

HRESULT Monster::Init()
{
	return S_OK;
}

void Monster::Release()
{
}

void Monster::Update()
{
}

void Monster::Render()
{
	Rectangle(getMemDC(), _rc);
}
