#include "stdafx.h"
#include "crab.h"
#include "Player.h"

Crab::Crab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

Crab::~Crab()
{
}

HRESULT Crab::Init()
{
	//���� �ʱ�ȭ
	_state = state::L_IDLE;

	//�̹��� �ʱ�ȭ
	crabImg[0] = IMAGEMANAGER->addFrameImage("crab", "����(��)-2.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	crabImg[1] = IMAGEMANAGER->addFrameImage("crab1", "����(��)-2(������).bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	crabImg[2] = IMAGEMANAGER->addFrameImage("crab2", "����(��)-3.bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	crabImg[3] = IMAGEMANAGER->addFrameImage("crab3", "����(��)-3(������).bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	//�̹��� ������ ���� �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		indexImg[i] = countImg[i] = 0;
	}

	//���� ó���� ���� ����
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	_isAttackFinish = false;
	//�� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//���� ó���� ���� ����
	_deathTimer = 0;

	//�� ī�޶� ��Ʈ(�׻� �� �߾��� ����ٴѴ�.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 15.f, _size.y);
	_cam.isCrush = false;

	//�� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//�� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x, _position.y };
	}
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 3, _att[0].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 3, _att[1].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);

	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�");

	//�÷��̾���� ���� �ʱ�ȭ
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	return S_OK;
}

void Crab::Release()
{
}

void Crab::Update()
{
	//���콺 ��ǥ ���
	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;

	//�̵� �׽�Ʈ
	if (KEYMANAGER->isStayKeyDown('I')) {
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('P')) {
		_position.x += 5.f;
	}

	//�� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//�� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//�� ī�޶� ��Ʈ(�׻� �� �߾��� ����ٴѴ�.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 15.f, _size.y);

	//�� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//�� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x, _position.y };
	}
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 3, _att[0].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 3, _att[1].pt.y - _size.y / 15, _size.x / 3, _size.y - 50);

	//�÷��̾�� ���� üũ
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//�÷��̾�� �Ÿ� üũ
	_dist = GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//ī�޶�� �浹�� �ƴ� ��� ��� ����
	if (!_cam.isCrush)
	{
		_state = state::L_IDLE;
	}

	//�÷��̾� ������ ���� ī�޶�� �浹 ó��
	RECT rcCam;
	if (IntersectRect(&rcCam, &_cam.rc, &_player->GetRect()))
	{
		_cam.isCrush = true;
	}

	//ī�޶�� �浹�� ��� ������ ���� ������ ����
	if (_cam.isCrush)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_MOVE;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_MOVE;
		}
	}

	//�÷��̾���� �Ÿ��� 300.f���� ������ ������ ���� �̵� ���·� ����
	if (_dist <= 300.f)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK_MOVE;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK_MOVE;
		}
	}

	//�÷��̾���� �������� �� ���� ���
	if (_dist <= _player->GetSize().x / 2 + _size.x / 2)
	{
		_isAttack = true;
	}
	
	//���� ����� �������� �� ���� ��ٸ� �� ���ݷ�Ʈ�� ������
	if (_isAttack)
	{
		_gauge++;
	
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK;
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK;
		}
	
		if (_gauge % 80 == 0)
		{
			_isAttack = false;
			_isAttackFinish = true;
			_gauge = 1;
		}
	}

	//������ ������ �ڷ� ���� ó��
	if (_isAttackFinish)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK_FINISH;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK_FINISH;
		}
	}

	//�÷��̾� �Ѿ˰� �浹 üũ
	if (KEYMANAGER->isToggleKey('R'))
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_DEATH;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_DEATH;
		}
	}

	//���¿� ���� ������ ó��
	switch (_state)
	{
	case state::L_MOVE:
		if (_dist > 300.f)
		{
			_position.x -= 5.f;
		}
		break;
	case state::R_MOVE:
		if (_dist > 300.f)
		{
			_position.x += 5.f;
		}
		break;
	case state::L_ATTACK_MOVE:
		if (_dist > _player->GetSize().x / 2 + _size.x / 2)
		{
			_position.x -= 5.f;
		}
		break;
	case state::R_ATTACK_MOVE:
		if (_dist > _player->GetSize().x / 2 + _size.x / 2)
		{
			_position.x += 5.f;
		}
		break;
	case state::L_ATTACK:
		_att[0].rc.left -= _size.x / 4;
		_att[0].rc.right -= _size.x / 4;
		break;
	case state::R_ATTACK:
		_att[1].rc.left += _size.x / 4;
		_att[1].rc.right += _size.x / 4;
		break;
	case state::L_ATTACK_FINISH:
		if (_dist < 320.f)
		{
			_position.x += 5.f;
			indexImg[1] = 0;
		}
		if (_dist >= 300.f)
		{
			_isAttackFinish = false;
		}
		break;
	case state::R_ATTACK_FINISH:
		if (_dist < 320.f)
		{
			_position.x -= 5.f;
			indexImg[1] = 11;
		}
		if (_dist >= 300.f)
		{
			_isAttackFinish = false;
		}
		break;
	case state::L_DEATH:
		//�浹 ��Ʈ ���ֱ�
		for (int i = 0; i < 4; i++)
		{
			_col[i].rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);
		}
		//���� ��Ʈ ���ֱ�
		for (int i = 0; i < 2; i++)
		{
			_att[i].rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);
		}

		//�ӽ÷� y��ǥ ������
		if (_position.y + _size.y / 2 < 730.f)
		{
			//��ü �κ� ����߸���
			_position.y += 5.f;
		}

		//���� �������� ��
		if (_position.y + _size.y / 2 >= 730.f)
		{
			_deathTimer++;

			if (_deathTimer % 100 == 0)
			{
				OBJECTMANAGER->RemoveObject(ObjectType::ENEMY, OBJECTMANAGER->FindObject(ObjectType::ENEMY, "crab"));
			}
		}

		break;
	case state::R_DEATH:
		//�浹 ��Ʈ ���ֱ�
		for (int i = 0; i < 4; i++)
		{
			_col[i].rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);
		}
		//���� ��Ʈ ���ֱ�
		for (int i = 0; i < 2; i++)
		{
			_att[i].rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);
		}

		//�ӽ÷� y��ǥ ������
		if (_position.y + _size.y / 2 < 730.f)
		{
			//��ü �κ� ����߸���
			_position.y += 5.f;
		}

		//���� �������� ��
		if (_position.y + _size.y / 2 >= 730.f)
		{
			_deathTimer++;

			if (_deathTimer % 100 == 0)
			{
				OBJECTMANAGER->RemoveObject(ObjectType::ENEMY, OBJECTMANAGER->FindObject(ObjectType::ENEMY, "crab"));
			}
		}

		break;
	}

	//���¿� ���� �̹��� ����
	this->crabImage();

}

void Crab::Render()
{
	//ī�޶� ��Ʈ �׸���
	Rectangle(getMemDC(), _cam.rc);

	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);

	//�� �̹��� �׸���
	//this->crabImageRender();

	//�浹��Ʈ �׸���
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), _col[i].rc);
	}

	//��üó����Ʈ �׸���
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _part[i].rc);
	}

	//����ó����Ʈ �׸���
	for (int i = 0; i < 2; i++)
	{
		Rectangle(getMemDC(), _att[i].rc);
	}

	//�ؽ�Ʈ ���
	sprintf(msg1, "x : %d, y : %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));
}

void Crab::crabImage()
{
	if ((_state == state::L_IDLE || _state == state::L_MOVE || _state == state::L_ATTACK_MOVE) && !(_state == state::L_ATTACK_FINISH))
	{
		countImg[0]++;
		if (countImg[0] % 10 == 0)
		{
			indexImg[0]++;
			if (indexImg[0] > 11)
			{
				indexImg[0] = 0;
			}
			crabImg[0]->setFrameX(indexImg[0]);
		}
	}
	if (_state == state::R_IDLE || _state == state::R_MOVE || _state == state::R_ATTACK_MOVE && !(_state == state::R_ATTACK_FINISH))
	{
		countImg[0]++;
		if (countImg[0] % 10 == 0)
		{
			indexImg[0]++;
			if (indexImg[0] > 11)
			{
				indexImg[0] = 0;
			}
			crabImg[1]->setFrameX(indexImg[0]);
		}
	}
	if (_state == state::L_ATTACK)
	{
		countImg[1]++;
		if (countImg[1] % 8 == 0)
		{
			indexImg[1]++;
			if (indexImg[1] > 11)
			{
				indexImg[1] = 0;
			}
			crabImg[2]->setFrameX(indexImg[1]);
		}
	}
	if (_state == state::R_ATTACK)
	{
		countImg[1]++;
		if (countImg[1] % 8 == 0)
		{
			indexImg[1]--;
			if (indexImg[1] < 0)
			{
				indexImg[1] = 11;
			}
			crabImg[3]->setFrameX(indexImg[1]);
		}
	}
	if (_state == state::L_ATTACK_FINISH)
	{
		countImg[2]++;
		if (countImg[2] % 10 == 0)
		{
			indexImg[2]--;
			if (indexImg[2] < 0)
			{
				indexImg[2] = 11;
			}
			crabImg[0]->setFrameX(indexImg[2]);
		}
	}
	if (_state == state::R_ATTACK_FINISH)
	{
		countImg[2]++;
		if (countImg[2] % 10 == 0)
		{
			indexImg[2]--;
			if (indexImg[2] < 0)
			{
				indexImg[2] = 11;
			}
			crabImg[1]->setFrameX(indexImg[2]);
		}
	}
}

void Crab::crabImageRender()
{
	if ((_state == state::L_IDLE || _state == state::L_MOVE || _state == state::L_ATTACK_MOVE) && !(_state == state::L_ATTACK_FINISH))
	{
		crabImg[0]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::R_IDLE || _state == state::R_MOVE || _state == state::R_ATTACK_MOVE)
	{
		crabImg[1]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::L_ATTACK)
	{
			crabImg[2]->frameRender(getMemDC(), _rc.left -60, _rc.top - 22);
		
	}
	if (_state == state::R_ATTACK)
	{
		crabImg[3]->frameRender(getMemDC(), _rc.left + 10, _rc.top - 22);
	}
	if (_state == state::L_ATTACK_FINISH)
	{
		crabImg[0]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::R_ATTACK_FINISH)
	{
		crabImg[1]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
}
