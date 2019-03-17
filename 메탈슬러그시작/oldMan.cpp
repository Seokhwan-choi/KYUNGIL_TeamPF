#include "stdafx.h"
#include "OldMan.h"
#include "ItemUi.h"
#include "Player.h"

OldMan::OldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot, CAPTIVE captive, ITEM item)
	:GameObject(name,pos,size,pivot,captive,item)
{
	_index = 0;
	_count = 0;
	_time = 0;
	_count1 = 0;
	_index1 = 0;
	_range = { _position.x - 100,_position.x + 200 };
	_speed = 3.f;
	_tiedRc = RectMake(_position.x,_position.y, _size.x, _size.y);
	_gravity = 2.3f;
	//_gravity = 0.0f;
	_isRight = true;
	_isCrush = false;
	_isShot = false;
	_touch = false;
	_isSave = false;
	_temp = RectMake(0, 0, 0, 0);
	_t = 0;
	_captive = captive;
	_item = item;
	_coly = _position.y + _size.y ;
	//����
	IMAGEMANAGER->findImage("tied");
	IMAGEMANAGER->findImage("untied");
	IMAGEMANAGER->findImage("walk");
	IMAGEMANAGER->findImage("run");
	IMAGEMANAGER->findImage("sir");
	IMAGEMANAGER->findImage("item");
	//���		
	IMAGEMANAGER->findImage("rumi_walk");
	IMAGEMANAGER->findImage("rumi_run");
	IMAGEMANAGER->findImage("rumi_sir");
	IMAGEMANAGER->findImage("rumi_crush");

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
	//�׽��߷°��� �ش�
	_position.y += _gravity;

	//�Ʒ��� �浹��Ʈ ��ġ ��ǥ ������Ʈ
	_coly = _position.y + _size.y ;
	//�Ʒ��� �ȼ� �浹
	if (SCENEMANAGER->FindScene("����������")) {
		for (int i = _coly - 60; i < _coly + 400; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("����ȼ�")->getMemDC(), _position.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 255 && b == 0))
			{
				_gravity = 0.0f;
				_position.y = i - _size.y - 125;
				break;
			}
		}
	}
	if (SCENEMANAGER->FindScene("���Ͻ�������")) {
		for (int i = _coly - 60; i < _coly + 400; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("���Ϲ���ȼ�")->getMemDC(), _position.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 255 && b == 0))
			{
				_gravity = 0.0f;
				_position.y = i - _size.y;
				break;
			}
		}
	}

	switch (_captive)
	{
		// ==================================================================================
		// ################################## �����ִ� ���� #################################
		// ==================================================================================

	case CAPTIVE::TIED:
		if (!_isShot) {

			_state = CAPTIVESTATE::TIED;
		}
	
		if (_isShot) {
			_time++;
			if (_time < 100) {
				_state = CAPTIVESTATE::UNTIED;
			}			
			if (_time > 10) {
				_position.x -= _speed;
				_state = CAPTIVESTATE::WALK;
				_isRight = false;
			}
			//�浹��
			//���� ���� �� �ϳ�  �÷��ֱ�
			if (IntersectRect(&temp, &_colRc[0],
				&((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"))->GetCollisionPlayer())) {
				_isCrush = true;
				_touch = false;
				if (_isSave == false) {
					DATA->setCaptive(DATA->getCaptive() + 1);
					_isSave = true;
					break;
				}
			}
			if (_isCrush == true) {
				_speed = 0;
				_position.x += _speed;
				_isGo = true;
				_t++;
			}
			//0.5�̸��϶� 
			if (_isGo == true && _t < 50) {
				_position.x += 2.0f;
			}
			//.5~1.5 ������ �ְԲ�
			if (_isGo&&_t > 50 && _t < 160) {
				_state = CAPTIVESTATE::ITEM;
				_speed = 0;
			}
			if (_isGo&&_t == 120) {
				((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition({ _position.x + 10, _position.y + _size.y - 50 });
				((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(true);
				((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);
			}
			if (_isGo&&_t > 160 && _t < 270) {
				_state = CAPTIVESTATE::THANKU;
				_speed = 0;
			}
			//1.5�� �̻��� �� ������ �԰� 100�� �ø� �� ����
			if (_isGo && _t > 270) {
				_state = CAPTIVESTATE::RUN;
				_position.x -= 6.f;
				if (IntersectRect(&temp, &((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"))->GetCollisionPlayer(),
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
	// ############################ �¿� �Դٰ��� �ϴ� ���� #######################
	// ==================================================================================
	case CAPTIVE::MOVE:
		//�¿� �Դٰ��� �ϵ��� ��
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
		//��
		//�浹��
		//���� ���� �� �ϳ�  �÷��ֱ�
		if (IntersectRect(&temp, &_colRc[0],
			&((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"))->GetCollisionPlayer())) {
			_isCrush = true;
			_touch = false;
			if (_isSave == false) {
				DATA->setCaptive(DATA->getCaptive() + 1);
				_isSave = true;
				break;
			}
		}
		if (_isCrush == true) {
			_speed = 0;
			_isGo = true;		
			_t++;
		}
		//0.5�̸��϶� 
		if (_isGo && _t < 50) {
			_position.x += 2.0f;
		}
		//.5~1.5 ������ �ְԲ�
		if (_isGo&&_t > 50 && _t < 160) {
			_state = CAPTIVESTATE::ITEM;
			_speed = 0;			
		}
		if (_isGo&&_t == 125) {
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition({ _position.x + 10, _position.y + _size.y - 50 });
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(true);
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);
		}
		if (_isGo&&_t > 160 && _t < 270) {
			_state = CAPTIVESTATE::THANKU;
			_speed = 0;
		}
		//1.5�� �̻��� �� ������ �԰� 100�� �ø� �� ����
		if (_isGo && _t > 270) {
			_state = CAPTIVESTATE::RUN;
			_position.x -= 6.f;
			if (IntersectRect(&temp, &((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"))->GetCollisionPlayer(),
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
		
		// ==================================================================================
		// ############################ ��� #######################
		// ==================================================================================
	case CAPTIVE::RUMI:
		_position.x -= _speed;
		_rumistate = RUMISTATE::WALK;
		_isRight = false;
		//��
		//�浹��
		//���� ���� �� �ϳ�  �÷��ֱ�
		if (IntersectRect(&temp, &_colRc[0],
			&OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�")->GetRect())) {
			_isCrush = true;
			_touch = false;
			if (_isSave == false) {
				DATA->setCaptive(DATA->getCaptive() + 1);
				_isSave = true;
				break;
			}
		}
		if (_isCrush == true) {
			_speed = 0;
			_isGo = true;
			_t++;
		}
		
		//.5~1.5 ������ �ְԲ�
		if (_isGo&&_t > 0 && _t < 130) {
			_rumistate = RUMISTATE::CRUSH;
			_speed = 0;
		}
		if (_isGo&&_t == 60) {
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition({ _position.x + _size.x - 5, _position.y + _size.y - 50 });
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(true);
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);
		}
		if (_isGo&&_t > 130 && _t < 210) {
			_rumistate = RUMISTATE::SIR;
			_speed = 0;
		}
		//1.5�� �̻��� �� ������ �԰� 100�� �ø� �� ����
		if (_isGo && _t > 210) {
			_rumistate = RUMISTATE::RUN;
			_position.x -= 6.f;
			if (IntersectRect(&temp, &((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"))->GetCollisionPlayer(), &OBJECTMANAGER->FindObject(ObjectType::UI, "item")->GetRect())) {
				_touch = true;
				if (_touch == true && ((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->getShow() == true) {
					((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(false);
					_touch = false;
					break;
				}
			}
		}
		break;

		// ==================================================================================
		// ############################ �������� �ɾ���� ���� #######################
		// ==================================================================================
	case CAPTIVE::RUN:
		_position.x -= _speed;
		_state = CAPTIVESTATE::WALK;
		_isRight = false;
		//��
		//�浹��
		//���� ���� �� �ϳ�  �÷��ֱ�
		if (IntersectRect(&temp, &_colRc[0],
			&OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�")->GetRect())) {
			_isCrush = true;
			_touch = false;
			if (_isSave == false) {
				DATA->setCaptive(DATA->getCaptive() + 1);
				_isSave = true;
				break;
			}
		}
		if (_isCrush == true) {
			_speed = 0;
			_isGo = true;
			_t++;
		}
		//0.5�̸��϶� 
		if (_isGo && _t < 50) {
			_position.x += 2.0f;
		}
		//.5~1.5 ������ �ְԲ�
		if (_isGo&&_t > 50 && _t < 160) {
			_state = CAPTIVESTATE::ITEM;
			_speed = 0;
		}
		if (_isGo&&_t == 125) {
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->SetPosition({ _position.x + 10, _position.y + _size.y - 50 });
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setShow(true);
			((ItemUi*)OBJECTMANAGER->FindObject(ObjectType::UI, "item"))->setItem(_item);
		}
		if (_isGo&&_t > 160 && _t < 270) {
			_state = CAPTIVESTATE::THANKU;
			_speed = 0;
		}
		//1.5�� �̻��� �� ������ �԰� 100�� �ø� �� ����
		if (_isGo && _t > 270) {
			_state = CAPTIVESTATE::RUN;
			_position.x -= 6.f;
			if (IntersectRect(&temp, &OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�")->GetRect(),
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
	// ############################### �ִϸ��̼� ���� #################################
	// ==================================================================================
	switch (_state)
	{
	case CAPTIVESTATE::TIED:
		IMAGEMANAGER->findImage("tied")->setFrameY(0);
		_count++;
		if (_count % 15 == 0) {
			_index++;
			if (_index > 7) {
				_index = 8;
			}
			IMAGEMANAGER->findImage("tied")->setFrameX(_index);
		}
		break;
	case CAPTIVESTATE::UNTIED:
		IMAGEMANAGER->findImage("untied")->setFrameY(0);
		_count1++;
		if (_count1 % 10 == 0) {
			_index1++;
			if (_index1 > 9) {
				_index1 = 10;
			}
			IMAGEMANAGER->findImage("untied")->setFrameX(_index);
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
				_index = 13;
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
				_index = 10;
			}
			IMAGEMANAGER->findImage("item")->setFrameX(_index);
		}
		break;
	default:
		break;
	}
	//��� �ൿ ���
	switch (_rumistate)
	{
	case RUMISTATE::WALK:
		IMAGEMANAGER->findImage("rumi_walk")->setFrameY(0);
		_count++;
		if (_count % 8 == 0) {
			_index--;
			if (_index < 0) {
				_index = 15;
			}
			IMAGEMANAGER->findImage("rumi_walk")->setFrameX(_index);
		}
		break;
	case RUMISTATE::RUN:
		IMAGEMANAGER->findImage("rumi_run")->setFrameY(0);
		_count++;
		if (_count % 8 == 0) {
			_index++;
			if (_index > 8) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("rumi_run")->setFrameX(_index);
		}
		break;
	case RUMISTATE::SIR:
		IMAGEMANAGER->findImage("rumi_sir")->setFrameY(0);
		_count++;
		if (_count % 20 == 0) {
			_index--;
			if (_index < 0) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("rumi_sir")->setFrameX(_index);
		}
		break;
	case RUMISTATE::CRUSH:
		IMAGEMANAGER->findImage("rumi_crush")->setFrameY(0);
		_count++;	
		if (_count % 13 == 0) {
			_index--;
			if (_index < 0) {
				_index = 0;
			}
			IMAGEMANAGER->findImage("rumi_crush")->setFrameX(_index);
		}
		break;
	default:
		break;
	}
	this->UpdateRectByPivot();
	// ==================================================================================
	// ################################## �浹 ��Ʈ ���� #################################
	// ==================================================================================

	//��
	_colRc[0] = RectMake(_position.x + _size.x/2, _position.y + 20, 10, 100);
	//��
	_colRc[1] = RectMake(_position.x + _size.x - 10, _position.y + 20, 10, 10);
	//��
	_colRc[2] = RectMake(_position.x + _size.x / 2, _coly, 10, 10);
	_tiedcolRc = RectMake(_position.x + _size.x / 2, _coly, 10, 10);
	_tiedRc = RectMake(_position.x, _position.y, _size.x, _size.y);

}

void OldMan::Render(void)
{
	//�����ǥ
	RECT _tied = CAMERA->Relative(_tiedRc);
	RECT  _rect = CAMERA->Relative(_rc);
	RECT _colrect = CAMERA->Relative(_colRc[2]);
	RECT _rect1[2];

	for (int i = 0; i < 2; i++) {
		if (_isCrush == false) {
			_rect1[i] = CAMERA->Relative(_colRc[i]);
		}
	}
	//��Ʈ �����ִ� ��
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		Rectangle(getMemDC(), _colrect);
		Rectangle(getMemDC(), _rect);
		Rectangle(getMemDC(), _tied);
		//�浹��Ʈ
		for (int i = 0; i < 2; i++) {
			Rectangle(getMemDC(), _rect1[i]);
		}
	}
	//���� �κ�
	switch (_state)
	{
	case CAPTIVESTATE::TIED:
		IMAGEMANAGER->frameRender("tied", getMemDC(), _tied.left, _tied.top);
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
	//��� ����
	switch (_rumistate)
	{
	case RUMISTATE::WALK:
		IMAGEMANAGER->frameRender("rumi_walk", getMemDC(), _rect.left, _rect.top);
		break;
	case RUMISTATE::RUN:
		IMAGEMANAGER->frameRender("rumi_run", getMemDC(), _rect.left, _rect.top);
		break;
	case RUMISTATE::SIR:
		IMAGEMANAGER->frameRender("rumi_sir", getMemDC(), _rect.left, _rect.top);
		break;
	case RUMISTATE::CRUSH:
		IMAGEMANAGER->frameRender("rumi_crush", getMemDC(), _rect.left, _rect.top);
		break;
	default:
		break;
	}
}


void OldMan::motion()
{

}

