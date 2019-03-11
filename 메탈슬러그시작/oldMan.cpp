#include "stdafx.h"
#include "OldMan.h"
#include "ItemUi.h"
#include "Player.h"
OldMan::OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, CAPTIVE captive, ITEM item)
	:GameObject(name,pos,size,pivot,captive,item)
{
	_captive = CAPTIVE::TIED;
	_index = 0;
	_count = 0;
	_range = { 1500,2000 };
	_speed = 3.f;
	_gravity = 0.3f;
	_isRight = true;
	_isCrush = false;
	_t = 0;
	_captive = captive;
	_item = item;
}

OldMan::~OldMan()
{
}

HRESULT OldMan::Init(void)
{
	return S_OK;
}

void OldMan::Release(void)
{
}

void OldMan::Update(void)
{
	RECT temp;
	switch (_captive)
	{
	case CAPTIVE::TIED:

		_position.x -= _speed;
		if (IntersectRect(&temp, &_colRc[0], &OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어")->GetRect())) {
			_isCrush = true;
		}
		if (_isCrush == true) {
			_speed = 0;
			_isGo = true;
			_t++;
		}
		if (_isGo&& _t < 50) {
			_position.x += 2.0f;
		}
		if (_isGo&&_t > 50 && _t < 150) {
			_speed = 0;
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition(_position);
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);

		}
		if (_isGo && _t > 150) {
			_position.x -= 4.f;
		}
		break;
	case CAPTIVE::MOVE:
		//좌우 왔다갔다 하도록 함
		if (_isRight) {
			_position.x += _speed;
		}
		if (!_isRight) {
			_position.x -= _speed;
		}
		if (_rc.left < _range.x) {
			_isRight = true;
		}
		if (_rc.right > _range.y) {
			_isRight = false;
		}
		//좌
		//충돌시
		if (IntersectRect(&temp, &_colRc[0], &OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어")->GetRect())) {
			_isCrush = true;
		}
		if (_isCrush == true) {
			_speed = 0;
			_isGo = true;
			_t++;
		}
		if (_isGo&& _t < 50) {
			_position.x += 2.0f;
		}
		if (_isGo&&_t > 50 && _t < 150) {
			_speed = 0;
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition(_position);
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);
		}
		if (_isGo && _t > 150) {
			_position.x -= 4.f;
		}
		break;
	default:
		break;
	}
	this->UpdateRectByPivot();
	//좌
	_colRc[0] = RectMake(_position.x, _position.y + 20, 10, 10);
	//우
	_colRc[1] = RectMake(_position.x + _size.x - 10, _position.y + 20, 10, 10);
}

void OldMan::Render(void)
{
	
		switch (_state)
		{
		case CAPTIVESTATE::TIED:
			break;
		case CAPTIVESTATE::UNTIED:
			break;
		case CAPTIVESTATE::WALK:
			if (_isRight) {

			}
			else {

			}
			break;
		case CAPTIVESTATE::RUN:
			break;
		case CAPTIVESTATE::THANKU:
			break;
		case CAPTIVESTATE::ITEM:
			break;
		default:
			break;
		}
	

	RECT  _rect = CAMERA->Relative(_rc);
	Rectangle(getMemDC(), _rect);
	
	for (int i = 0; i < 3; i++) {
		if (_isCrush == false) {
			RECT _rect1[3];
			_rect1[i] = CAMERA->Relative(_colRc[i]);
			Rectangle(getMemDC(), _rect1[i]);
		}
	}
	
}

void OldMan::motion()
{

}

