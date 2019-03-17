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
		_isShow = true;
		break;
	case ITEM::FRUIT:
		break;
	case ITEM::HEAVY:
		break;
	case ITEM::GRENADE:
		break;
	case ITEM::CRAB:
		break;
	case ITEM::BOMB:

		break;
	default:
		break;
	}
	//픽셀 충돌
	_coly = _position.y + _size.y;
	_botRc = RectMake(_position.x, _position.y, _size.x, _size.y);
	_gravity = 3.3f;
	//_gravity = 0.0f;
	//플레이어와 닿기 전
	IMAGEMANAGER->findImage("cap_granade");
	IMAGEMANAGER->findImage("heavy");
	IMAGEMANAGER->findImage("granade");

	//플레이어와 닿은 후 사라지도록 만들어야함
	IMAGEMANAGER->findImage("heavy_dis");
	IMAGEMANAGER->findImage("fish");
	IMAGEMANAGER->findImage("chicken");
	IMAGEMANAGER->findImage("fuit");
	IMAGEMANAGER->findImage("cap_granade");

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
	//항시 중력값을 준다
	_position.y += _gravity;
	//아래쪽 충돌렉트 위치 좌표 업데이트
	_coly = _position.y + _size.y;
	//픽셀충돌
	if (SCENEMANAGER->FindScene("스테이지원")) {

		for (int i = _coly - 60; i < _coly + 60; i++) {
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), _position.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0) {
				_gravity = 0.0f;
				_position.y = i - _size.y - 140;
				break;
			}

		}
	}
	if (SCENEMANAGER->FindScene("지하스테이지")) {

	for (int i = _coly - 60; i < _coly + 60; i++) {
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("지하배경픽셀")->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 255 && b == 0) {
			_gravity = 0.0f;
			_position.y = i - _size.y;
			break;
		}

	}
	}

	_botRc = RectMake(_position.x + _size.x / 2, _coly, 10, 10);

	_count++;
	RECT temp;

	//충돌체크
	if (IntersectRect(&temp, &_rc, &((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어"))->GetCollisionPlayer())) {
		_isTouch = true;
		switch (_item)
		{
			//점수처리
		case ITEM::FISH:
			if (_isTouch == true && _isShow == true) {
				DATA->setScore(DATA->getScore() + 500);
				_isShow = false;
				_isTouch = false;
				SOUNDMANAGER->play("아이템먹음");
				break;
			}
			break;
		case ITEM::CHICKEN:
			if (_isTouch == true && _isShow == true) {
				DATA->setScore(DATA->getScore() + 500);
				_isShow = false;
				_isTouch = false;
				SOUNDMANAGER->play("아이템먹음");
				break;
			}
			break;
		case ITEM::FRUIT:
			if (_isTouch == true && _isShow == true) {
				DATA->setScore(DATA->getScore() + 500);
				_isShow = false;
				_isTouch = false;
				SOUNDMANAGER->play("아이템먹음");
				break;
			}
			break;
		case ITEM::HEAVY:
			if (_isShow == true) {
				((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어"))->SetWeapon(WEAPON::HEAVY);
				DATA->setWeapon(WEAPON::HEAVY);
				DATA->setArms(200);
			}
			break;
		case ITEM::GRENADE:
			if (_isShow == true) {
				((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어"))->SetWeapon(WEAPON::GRENADE);
				DATA->setWeapon(WEAPON::GRENADE);
			}
			break;
		case ITEM::CRAB:
			break;
		case ITEM::BOMB:
			if (_isShow == true && _isTouch == true) {
				DATA->setBomb(DATA->getBomb() + 10);
				//고친부분
				_isShow = false;
				_isTouch = false;
				break;
			}
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
			IMAGEMANAGER->findImage("fuit")->setFrameY(0);
			if (_count % 15 == 0) {
				_index++;
				if (_index > 11) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("fuit")->setFrameX(_index);
			}
			break;
		case ITEM::CRAB:
			break;
		case ITEM::BOMB:
			IMAGEMANAGER->findImage("cap_granade")->setFrameY(0);
			if (_count % 15 == 0) {
				_index--;
				if (_index < 0) {
					_index = 5;
				}
				IMAGEMANAGER->findImage("cap_granade")->setFrameX(_index);
			}
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
		if (_isShow == true) {
			IMAGEMANAGER->frameRender("fuit", getMemDC(), _rect.left, _rect.top);
		}
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
	case ITEM::BOMB:
		if (_isShow == true) {
			IMAGEMANAGER->frameRender("cap_granade", getMemDC(), _rect.left, _rect.top);
		}
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
