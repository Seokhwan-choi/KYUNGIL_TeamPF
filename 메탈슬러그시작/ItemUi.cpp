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
	//�ʱ� �Ұ� �ʱ�ȭ
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
	//�ȼ� �浹
	_coly = _position.y + _size.y;
	_botRc = RectMake(_position.x, _position.y, _size.x, _size.y);
	_gravity = 3.3f;
	//_gravity = 0.0f;
	//�÷��̾�� ��� ��
	IMAGEMANAGER->findImage("cap_granade");
	IMAGEMANAGER->findImage("heavy");
	IMAGEMANAGER->findImage("granade");

	//�÷��̾�� ���� �� ��������� ��������
	IMAGEMANAGER->findImage("heavy_dis");
	IMAGEMANAGER->findImage("fish");
	IMAGEMANAGER->findImage("chicken");
	IMAGEMANAGER->findImage("fuit");
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
	//�׽� �߷°��� �ش�
	_position.y += _gravity;
	//�Ʒ��� �浹��Ʈ ��ġ ��ǥ ������Ʈ
	_coly = _position.y + _size.y;
	//�ȼ��浹
	for (int i = _coly - 60; i < _coly + 60; i++) {
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("����ȼ�")->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 255 && b == 0) {
			_gravity = 0.0f;
			_position.y = i - _size.y - 140;
			break;
		}

	}
	_botRc = RectMake(_position.x + _size.x / 2, _coly, 10, 10);

	_count++;
	RECT temp;

	//�浹üũ
	if (IntersectRect(&temp, &_rc, &OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�")->GetRect())) {
		_isTouch = true;
		switch (_item)
		{
			//����ó��
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
				((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"))->SetWeapon(WEAPON::HEAVY);
				DATA->setWeapon(WEAPON::HEAVY);
				DATA->setArms(200);
			}
			break;
		case ITEM::GRENADE:
			if (_isShow == true) {
				((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"))->SetWeapon(WEAPON::GRENADE);
				DATA->setWeapon(WEAPON::GRENADE);
			}
			break;
		case ITEM::CRAB:
			break;
		default:
			break;
		}
	}


	//������ ó��
	if (_isShow == true) {
		switch (_item)
		{
			//��ġ�� �˾Ƽ� ����
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

	//Ʈ���϶��� ������

	switch (_item)
	{
		//��ġ�� �˾Ƽ� ����
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

	//Ʈ���϶� �����ְ� �ٷ� �������Բ� ó���ؾ���
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
