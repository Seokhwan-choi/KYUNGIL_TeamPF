#include "stdafx.h"
#include "Monster.h"


Monster::Monster(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name,pos,size,pivot)
{
	_name = name; //Ŭ���� �̸������صд� 
	_position = pos; //��ǥ �ʱ�ȭ ���ش� 
	_size = size; //������ �ʱ�ȭ���ش� 
	_pivot = Pivot::Center; //�ǹ���ġ����ش� 
	this->UpdateRectByPivot(); //RECT�׷��ش� 
	_isActive = true; //Ȱ��ȭ�Ǿ��ִ�
	_isLive = true; //����ִ� 
	
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
