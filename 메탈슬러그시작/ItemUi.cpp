#include "stdafx.h"
#include "ItemUi.h"
#include "OldMan.h"
ItemUi::ItemUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot)
	:GameObject(name, pos, size, pivot)
{

}

ItemUi::~ItemUi()
{
}

HRESULT ItemUi::Init(void)
{
	return S_OK;
}

void ItemUi::Release(void)
{
}

void ItemUi::Update(void)
{
}

void ItemUi::Render(void)
{
	//트루일때만 보여줌
	if (_isShow) {
		switch (_item)
		{
			//위치는 알아서 선정
		case ITEM::FISH:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::CHICKEN:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::FRUIT:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::HEAVY:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::GRENADE:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::CRAB:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		default:
			break;
		}
	}
	//트루일때 보여주고 바로 없어지게끔 처리해야함
	if (_isVanish) {
		switch (_item)
		{
		case ITEM::HEAVY:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::GRENADE:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		default:
			break;
		}

	}
}
