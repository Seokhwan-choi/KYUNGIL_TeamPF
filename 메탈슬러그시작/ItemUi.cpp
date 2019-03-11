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
	RECT _rect;
	_rect = CAMERA->Relative(_rc);

	//Ʈ���϶��� ������
	if (_isShow) {
		switch (_item)
		{
			//��ġ�� �˾Ƽ� ����
		case ITEM::FISH:
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			Rectangle(getMemDC(), _rect);
			break;
		case ITEM::CHICKEN:
			Rectangle(getMemDC(), _rect);
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::FRUIT:
			Rectangle(getMemDC(), _rect);
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::HEAVY:
			Rectangle(getMemDC(), _rect);
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::GRENADE:
			Rectangle(getMemDC(), _rect);
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::CRAB:
			Rectangle(getMemDC(), _rect);
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		default:
			break;
		}
	}
	//Ʈ���϶� �����ְ� �ٷ� �������Բ� ó���ؾ���
	if (_isVanish) {
		switch (_item)
		{
		case ITEM::HEAVY:
			Rectangle(getMemDC(), _rect);
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		case ITEM::GRENADE:
			Rectangle(getMemDC(), _rect);
			//IMAGEMANAGER->frameRender(getMemDC(), _rc.left, _rc.top);
			break;
		default:
			break;
		}

	}
}
