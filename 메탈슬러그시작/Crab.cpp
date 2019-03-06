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
	crab[0] = IMAGEMANAGER->addFrameImage("crab", "����(��)-2.bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	crab[1] = IMAGEMANAGER->addFrameImage("crab1", "����(��)-2(������).bmp", 1800, 150, 12, 1, true, RGB(255, 0, 255));
	crab[2] = IMAGEMANAGER->addFrameImage("crab2", "����(��)-3.bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	crab[3] = IMAGEMANAGER->addFrameImage("crab3", "����(��)-3(������).bmp", 2448, 172, 12, 1, true, RGB(255, 0, 255));
	//�̹��� ������ ����  �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		index[i] = count[i] = 0;
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
			index[1] = 0;
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
			index[1] = 11;
		}
		if (_dist >= 300.f)
		{
			_isAttackFinish = false;
		}
		break;
	}

	this->Crabimage();


}

void Crab::Render()
{
	//ī�޶� ��Ʈ �׸���
	Rectangle(getMemDC(), _cam.rc);

	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);
	this->CrabimageRender();
	//�浹��Ʈ �׸���
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), _col[i].rc);
	}

	//��üó����Ʈ �׸���
	for (int i = 0; i < 3; i++)
	{
		//Rectangle(getMemDC(), _part[i].rc);
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

void Crab::Crabimage()
{
	if ((_state == state::L_IDLE || _state == state::L_MOVE || _state == state::L_ATTACK_MOVE) && !(_state == state::L_ATTACK_FINISH))
	{
		count[0]++;
		if (count[0] % 10 == 0)
		{
			index[0]++;
			if (index[0] > 11)
			{
				index[0] = 0;
			}
			crab[0]->setFrameX(index[0]);
		}
	}
	if (_state == state::R_IDLE || _state == state::R_MOVE || _state == state::R_ATTACK_MOVE && !(_state == state::R_ATTACK_FINISH))
	{
		count[0]++;
		if (count[0] % 10 == 0)
		{
			index[0]++;
			if (index[0] > 11)
			{
				index[0] = 0;
			}
			crab[1]->setFrameX(index[0]);
		}
	}
	if (_state == state::L_ATTACK)
	{
		count[1]++;
		if (count[1] % 8 == 0)
		{
			index[1]++;
			if (index[1] > 11)
			{
				index[1] = 0;
			}
			crab[2]->setFrameX(index[1]);
		}
	}
	if (_state == state::R_ATTACK)
	{
		count[1]++;
		if (count[1] % 8 == 0)
		{
			index[1]--;
			if (index[1] < 0)
			{
				index[1] = 11;
			}
			crab[3]->setFrameX(index[1]);
		}
	}
	if (_state == state::L_ATTACK_FINISH)
	{
		count[2]++;
		if (count[2] % 10 == 0)
		{
			index[2]--;
			if (index[2] < 0)
			{
				index[2] = 11;
			}
			crab[0]->setFrameX(index[2]);
		}
	}
	if (_state == state::R_ATTACK_FINISH)
	{
		count[2]++;
		if (count[2] % 10 == 0)
		{
			index[2]--;
			if (index[2] < 0)
			{
				index[2] = 11;
			}
			crab[1]->setFrameX(index[2]);
		}
	}
}

void Crab::CrabimageRender()
{
	if ((_state == state::L_IDLE || _state == state::L_MOVE || _state == state::L_ATTACK_MOVE) && !(_state == state::L_ATTACK_FINISH))
	{
		crab[0]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::R_IDLE || _state == state::R_MOVE || _state == state::R_ATTACK_MOVE)
	{
		crab[1]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::L_ATTACK)
	{
			crab[2]->frameRender(getMemDC(), _rc.left -60, _rc.top - 22);
		
	}
	if (_state == state::R_ATTACK)
	{
		crab[3]->frameRender(getMemDC(), _rc.left + 10, _rc.top - 22);
	}
	if (_state == state::L_ATTACK_FINISH)
	{
		crab[0]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
	if (_state == state::R_ATTACK_FINISH)
	{
		crab[1]->frameRender(getMemDC(), _rc.left, _rc.top);
	}
}
