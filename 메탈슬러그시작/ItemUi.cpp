#include "stdafx.h"
#include "ItemUi.h"
#include "OldMan.h"
#include "Player.h"

ItemUi::ItemUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, ITEM item)
	:GameObject(name, pos, size, pivot, item)
{
	_isShow = false;
	_isVanish = false;
	_isTouch = false;
	_count = 0;
	_index = 0;
	_item = item;
	//초기 불값 초기화
	switch (_item)
	{
	case ITEM::FISH:
		_isShow = true;
		break;
	case ITEM::CHICKEN:
		
		break;
	case ITEM::FRUIT:
		_isShow = true;
		break;
	case ITEM::HEAVY:
		break;
	case ITEM::GRENADE:
		break;
	case ITEM::CRAB:
		break;
	default:
		break;
	}

	//플레이어와 닿기 전
	IMAGEMANAGER->addFrameImage("cap_granade", "UI/item/item_1.bmp", 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("heavy", "UI/item/item_2.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("granade", "UI/item/item_3.bmp", 50, 50, true, RGB(255, 0, 255));
	
	//플레이어와 닿은 후 사라지도록 만들어야함
	IMAGEMANAGER->addFrameImage("heavy_dis", "UI/item/item_4.bmp", 100, 20, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fish", "UI/item/item_5.bmp",540,60, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("chicken", "UI/item/item_6.bmp", 341, 32, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fuit", "UI/item/item_7.bmp", 389, 38, 12, 1, true, RGB(255, 0, 255));	
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
	
	_count++;
	RECT temp;
	
	//충돌체크
	if (IntersectRect(&temp, &_rc, &OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어")->GetRect())) {
		_isTouch = true;
		switch (_item)
		{
		//점수처리
		case ITEM::FISH:				
			if (_isTouch == true && _isShow == true) {
				DATA->setScore(DATA->getScore() + 500);
				_isShow = false;
				_isTouch = false;
				break;
			}
			break;
		case ITEM::CHICKEN:
			if (_isTouch == true && _isShow == true) {
				DATA->setScore(DATA->getScore() + 500);
				_isShow = false;
				_isTouch = false;
				break;
			}
			break;
		case ITEM::FRUIT:
			if (_isTouch == true && _isShow == true) {
				DATA->setScore(DATA->getScore() + 500);
				_isShow = false;
				_isTouch = false;
				break;
			}
			break;
		case ITEM::HEAVY:
			if (_isShow == true) {
				((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어"))->SetWeapon(WEAPON::HEAVY);
				DATA->setWeapon(WEAPON::HEAVY);
			}
			break;
		case ITEM::GRENADE:
			if (_isShow == true) {
				((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어"))->SetWeapon(WEAPON::GRENADE);
				//DATA->setWeapon(WEAPON::GRENADE);
			}
			break;
		case ITEM::CRAB:
			break;
		default:
			break;
		}
	}
	

	//프레임 처리
	if (_isShow == true) {
		switch (_item)
		{
			//위치는 알아서 선정
		case ITEM::FISH:
			IMAGEMANAGER->findImage("fish")->setFrameY(0);
			if (_count % 10 == 0) {
				_index++;
				if (_index > 5) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("fish")->setFrameX(_index);
			}
			break;
		case ITEM::CHICKEN:
			IMAGEMANAGER->findImage("chicken")->setFrameY(0);
			if (_count % 15 == 0) {
				_index++;
				if (_index > 10) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("chicken")->setFrameX(_index);
			}
			break;
		case ITEM::FRUIT:
			IMAGEMANAGER->findImage("fruit")->setFrameY(0);
			if (_count % 15 == 0) {
				_index++;
				if (_index > 11) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("fruit")->setFrameX(_index);
			}
			break;
		case ITEM::CRAB:
			break;
		default:
			break;
		}

	}
	this->UpdateRectByPivot();
}

void ItemUi::Render(void)
{
	RECT _rect;
	_rect = CAMERA->Relative(_rc);

	if (KEYMANAGER->isToggleKey(VK_F1)) {
		Rectangle(getMemDC(), _rect);
	}

	//트루일때만 보여줌
	
	switch (_item)
	{
		//위치는 알아서 선정
	case ITEM::FISH:
		if (_isShow == true) {
			IMAGEMANAGER->frameRender("fish", getMemDC(), _rect.left, _rect.top);
		}
		//Rectangle(getMemDC(), _rect);
		break;
	case ITEM::CHICKEN:
		if (_isShow == true) {
			IMAGEMANAGER->frameRender("chicken", getMemDC(), _rect.left, _rect.top);
		}
		//Rectangle(getMemDC(), _rect);
		break;
	case ITEM::FRUIT:
		IMAGEMANAGER->frameRender("fruit", getMemDC(), _rect.left, _rect.top);
		//Rectangle(getMemDC(), _rect);
		break;
	case ITEM::HEAVY:
		if (_isShow == true) {
			IMAGEMANAGER->render("heavy", getMemDC(), _rect.left, _rect.top);
		}
		
		//Rectangle(getMemDC(), _rect);
		break;
	case ITEM::GRENADE:
		if (_isShow == true) {
			IMAGEMANAGER->render("granade", getMemDC(), _rect.left, _rect.top);
		}
		//Rectangle(getMemDC(), _rect);
		break;
	case ITEM::CRAB:
		//Rectangle(getMemDC(), _rect);
		break;
	default:
		break;
	}
	
	//트루일때 보여주고 바로 없어지게끔 처리해야함
	if (_isVanish) {
		switch (_item)
		{
		case ITEM::HEAVY:
			IMAGEMANAGER->frameRender("heavy_dis", getMemDC(), _rc.left, _rc.top);
			//Rectangle(getMemDC(), _rect);
			break;
		default:
			break;
		}

	}
}
