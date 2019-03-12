#include "stdafx.h"
#include "OldMan.h"
#include "ItemUi.h"
#include "Player.h"

OldMan::OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, CAPTIVE captive, ITEM item)
	:GameObject(name,pos,size,pivot,captive,item)
{
	_index = 0;
	_count = 0;
	_range = { _position.x - 100,_position.x + 200 };
	_speed = 3.f;
	//_gravity = 2.3f;
	_gravity = 0.0f;
	_isRight = true;
	_isCrush = false;
	_isShot = false;
	_touch = false;
	_temp = RectMake(0, 0, 0, 0);
	_t = 0;
	_captive = captive;
	_item = item;
	_coly = _position.y + _size.y ;
	IMAGEMANAGER->addFrameImage("tied", "UI/item/captive_tied.bmp", 1872, 150, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("untied", "UI/item/captive_untied.bmp", 660, 48.10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("walk", "UI/item/captive_walk.bmp", 2500, 300, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("run", "UI/item/captive_run.bmp", 1666, 150, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sir", "UI/item/captive_sir.bmp", 2916, 150, 14, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("item", "UI/item/captive_item.bmp", 2288, 150, 11, 1, true, RGB(255, 0, 255));

}

OldMan::~OldMan()
{
}

HRESULT OldMan::Init(void)
{
	_touch = false;
	return S_OK;
}

void OldMan::Release(void)
{
}

void OldMan::Update(void)
{
	RECT temp;
	//항시중력값을 준다
	_position.y += _gravity;

	//아래쪽 충돌렉트 위치 좌표 업데이트
	_coly = _position.y + _size.y ;
	//아래쪽 픽셀 충돌
	for (int i = _coly - 60; i < _coly + 60; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if ((r == 255 && g == 255 && b == 0))
		{
			_gravity = 0.0f;
			_position.y = i- _size.y - 140;
			break;
		}
	}
	switch (_captive)
	{
		// ==================================================================================
		// ################################## 묶여있는 포로 #################################
		// ==================================================================================

	case CAPTIVE::TIED:
		if (!_isShot) {
			_state = CAPTIVESTATE::TIED;
		}
		if (_isShot) {
			_position.x -= _speed;
			_isRight = false;
			_state = CAPTIVESTATE::WALK;
			//좌
			//충돌시
			if (IntersectRect(&temp, &_colRc[0],
				&OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어")->GetRect())) {
				_isCrush = true;
				_touch = false;
			}
			if (_isCrush == true) {
				_speed = 0;
				_isGo = true;
				_t++;
			}
			//0.5미만일때 
			if (_isGo && _t < 50) {
				_position.x += 2.0f;
			}
			//.5~1.5 가만히 있게끔
			if (_isGo&&_t > 50 && _t < 160) {
				_state = CAPTIVESTATE::ITEM;
				_speed = 0;
			}
			if (_isGo&&_t == 110) {
				((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition({ _position.x + 10, _position.y + _size.y - 50 });
				((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(true);
				((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);
			}
			if (_isGo&&_t > 160 && _t < 240) {
				_state = CAPTIVESTATE::THANKU;
				_speed = 0;
			}
			//1.5초 이상일 때 아이템 먹고 100점 올릴 수 있음
			if (_isGo && _t > 240) {
				_state = CAPTIVESTATE::RUN;
				_position.x -= 6.f;
				if (IntersectRect(&temp, &OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어")->GetRect(),
					&OBJECTMANAGER->FindObject(ObjectType::UI, "item")->GetRect())) {
					_touch = true;
					if (_touch == true && ((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->getShow() == true) {
						DATA->setScore(DATA->getScore() + 100);
						((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(false);
						_touch = false;
						break;
					}
				}
			}
		}
		break;
		// ==================================================================================
		// ################################## 좌우 왔다갔다 하는 포로 #################################
		// ==================================================================================

	case CAPTIVE::MOVE:
		//좌우 왔다갔다 하도록 함
		if (_isRight) {
			_state = CAPTIVESTATE::WALK;
		}
		if (!_isRight) {
			_position.x -= _speed;
			_state = CAPTIVESTATE::WALK;
		}
		if (_rc.left < _range.x) {
			_isRight = true;
		}
		if (_rc.right > _range.y) {
			_isRight = false;
		}
		//좌
		//충돌시
		if (IntersectRect(&temp, &_colRc[0], 
			&OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어")->GetRect())) {
			_isCrush = true;
			_touch = false;
		}
		if (_isCrush == true) {
			_speed = 0;
			_isGo = true;		
			_t++;
		}
		//0.5미만일때 
		if (_isGo && _t < 50) {
			_position.x += 2.0f;
		}
		//.5~1.5 가만히 있게끔
		if (_isGo&&_t > 50 && _t < 160) {
			_state = CAPTIVESTATE::ITEM;
			_speed = 0;			
		}
		if (_isGo&&_t == 110) {
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition({ _position.x + 10, _position.y + _size.y - 50 });
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(true);
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);
		}
		if (_isGo&&_t > 160 && _t < 240) {
			_state = CAPTIVESTATE::THANKU;
			_speed = 0;
		}
		//1.5초 이상일 때 아이템 먹고 100점 올릴 수 있음
		if (_isGo && _t > 240) {
			_state = CAPTIVESTATE::RUN;
			_position.x -= 6.f;
			if (IntersectRect(&temp, &OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어")->GetRect(),
				&OBJECTMANAGER->FindObject(ObjectType::UI, "item")->GetRect())) {
				_touch = true;
				if (_touch == true && ((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->getShow() == true) {
					DATA->setScore(DATA->getScore() + 100);
					((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(false);
					_touch = false;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
	// ==================================================================================
	// ############################### 애니메이션 포로 #################################
	// ==================================================================================
	switch (_state)
	{
	case CAPTIVESTATE::TIED:
		IMAGEMANAGER->findImage("tied")->setFrameY(0);
		_count++;
		if (_count % 20 == 0) {
			_index++;
			if (_index > 7) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("tied")->setFrameX(_index);
		}
		break;
	case CAPTIVESTATE::UNTIED:
		IMAGEMANAGER->findImage("untied")->setFrameY(0);
		_count++;
		if (_count % 20 == 0) {
			_index++;
			//if(_index >)
		}
		break;
	case CAPTIVESTATE::WALK:
		if (_isRight) {
			IMAGEMANAGER->findImage("walk")->setFrameY(1);	
			_count++;
			if (_count % 10 == 0) {
				_index--;
				if (_index < 0) {
					_index = 11;
				}
				IMAGEMANAGER->findImage("walk")->setFrameX(_index);
			}
		}
		else {
			IMAGEMANAGER->findImage("walk")->setFrameY(0);
			_count++;
			if (_count % 10 == 0) {
				_index++;
				if (_index > 11) {
					_index = 0;
				}
				IMAGEMANAGER->findImage("walk")->setFrameX(_index);
			}
		}
		break;
	case CAPTIVESTATE::RUN:
		IMAGEMANAGER->findImage("run")->setFrameY(0);
		_count++;
		if (_count % 10 == 0) {
			_index++;
			if (_index > 7) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("run")->setFrameX(_index);
		}
		break;
	case CAPTIVESTATE::THANKU:
		IMAGEMANAGER->findImage("sir")->setFrameY(0);
		_count++;
		if (_count % 8 == 0) {
			_index++;
			if (_index > 13) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("sir")->setFrameX(_index);
		}
		break;
	case CAPTIVESTATE::ITEM:
		IMAGEMANAGER->findImage("item")->setFrameY(0);
		_count++;
		if (_count % 11 == 0) {
			_index++;
			if (_index > 10) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("item")->setFrameX(_index);
		}
		break;
	default:
		break;
	}
	this->UpdateRectByPivot();
	// ==================================================================================
	// ################################## 충돌 렉트 선언 #################################
	// ==================================================================================

	//좌
	_colRc[0] = RectMake(_position.x, _position.y + 20, 10, 10);
	//우
	_colRc[1] = RectMake(_position.x + _size.x - 10, _position.y + 20, 10, 10);
	//하
	_colRc[2] = RectMake(_position.x + _size.x / 2, _coly, 10, 10);
}

void OldMan::Render(void)
{
	//상대좌표
	RECT  _rect = CAMERA->Relative(_rc);
	RECT _colrect = CAMERA->Relative(_colRc[2]);
	RECT _rect1[2];

	for (int i = 0; i < 2; i++) {
		if (_isCrush == false) {
			_rect1[i] = CAMERA->Relative(_colRc[i]);
		}
	}
	//렉트 보여주는 곳
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		for (int i = 0; i < 2; i++) {
			Rectangle(getMemDC(), _rect1[i]);
		}
		Rectangle(getMemDC(), _colrect);
		Rectangle(getMemDC(), _rect);
	}
	//랜더 부분
	switch (_state)
	{
	case CAPTIVESTATE::TIED:
		IMAGEMANAGER->frameRender("tied", getMemDC(), _rect.left, _rect.top);
		break;
	case CAPTIVESTATE::UNTIED:
		IMAGEMANAGER->frameRender("untied", getMemDC(), _rect.left, _rect.top);
		break;
	case CAPTIVESTATE::WALK:
		IMAGEMANAGER->frameRender("walk", getMemDC(), _rect.left, _rect.top);
		break;
	case CAPTIVESTATE::RUN:
		IMAGEMANAGER->frameRender("run", getMemDC(), _rect.left, _rect.top);
		break;
	case CAPTIVESTATE::THANKU:
		IMAGEMANAGER->frameRender("sir", getMemDC(), _rect.left, _rect.top);
		break;
	case CAPTIVESTATE::ITEM:
		IMAGEMANAGER->frameRender("item", getMemDC(), _rect.left, _rect.top);
		break;
	default:
		break;
	}
		
}


void OldMan::motion()
{

}

