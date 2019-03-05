#include "stdafx.h"
#include "FlyBug.h"
#include "Player.h"

FlyBug::FlyBug(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

FlyBug::~FlyBug()
{
}

HRESULT FlyBug::Init()
{
	//���� �ʱ�ȭ
	_state = state::IDLE;
	//���� ������ ó���� ���� ���� �ʱ�ȭ
	_move = 0;
	_isUp = false;
	//���� ó���� ���� ����
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	//���ڸ� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}
	//���� ó���� ���� ����
	_deathTimer = 0;
	//���ڸ� ī�޶� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 3.f, _size.y * 2.f);
	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�");
	//�÷��̾���� ���� �ʱ�ȭ
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	//���ڸ� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_col.pt.x + _size.y / 2, _col.pt.y, _size.x, _size.y / 2);

	return S_OK;
}

void FlyBug::Release()
{
}

void FlyBug::Update()
{
	//���콺 ��ǥ ���
	_pt.x = _ptMouse.x;
	_pt.y = _ptMouse.y;

	//���ڸ� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//���ڸ� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//���ڸ� ī�޶� ��Ʈ(�׻� �� �߾��� ����ٴѴ�.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 2.f, _size.y);

	//���ڸ� �浹 ��Ʈ(�׻� ���� ���� �ٴѴ�.)
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_col.pt.x, _col.pt.y, _size.x, _size.y);

	//�÷��̾�� ���� üũ
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	if (_cam.rc.left <= 50 || _cam.rc.right >= WINSIZEX - 50)
	{
		_state = state::IDLE;
	}

	//270������ ũ�� �������� �̵�
	if (_angle > PI / 180 * 270 && _cam.rc.left > 50)
	{
		_state = state::L_MOVE;
	}
	//270�� ���� ������ ���������� �̵�
	else if (_angle < PI / 180 * 270 && _cam.rc.right < WINSIZEX - 50)
	{
		_state = state::R_MOVE;
	}

	//���� ������ 10�� ������ �׶� ���� ���·� ����
	if (_gauge % 10 == 0)
	{
		_state = state::ATTACK;
	}
	//�÷��̾�� �浹 üũ
	if (GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y)
		< _size.x / 2 + _player->GetSize().x / 2)
	{
		_isAttack = true;
	}

	//�÷��̾� �Ѿ˰� �浹 üũ
	if (KEYMANAGER->isToggleKey('R'))
	{
		_state = state::DEATH;
	}

	//�̵� �׽�Ʈ
	/*if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_position.x -= 5.f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_position.x += 5.f;
	}*/
	//���� ���� ������ ó��
	switch (_state)
	{
		//��� ����
	case state::IDLE:
		//�Ʒ��� �̵�
		if (!_isUp)
		{
			//_position.x += 2.f;
			_position.y += 4.f;
			_move += 1;
		}
		//���� �̵�
		else
		{
			//_position.x -= 2.f;
			_position.y -= 4.f;
			_move += 1;
		}

		//25 �̵��� �ݴ�� �̵�
		if (_move > 25)
		{
			_move = 0;
			_isUp = !_isUp;
			_gauge++;
		}
		break;
		//���� ����
	case state::ATTACK:
		if (!_isAttack)
		{
			//�÷��̾ ���� �� ���� ����
			_attackAngle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

			_position.x += cosf(_attackAngle) * 5.f;
			_position.y += -sinf(_attackAngle) * 5.f;
		}

		//�÷��̾�� �浹 ó�� �Ǹ� �ٽ� ����ġ
		if (_isAttack)
		{
			_attackAngle = GetAngle(_position.x, _position.y, _tempPt.x, _tempPt.y);
			_position.x += cosf(_attackAngle) * 5.f;
			_position.y += -sinf(_attackAngle) * 5.f;
			_gauge = 1;
			_isAttack = false;
		}

		break;
		//�������� �̵� ����
	case state::L_MOVE:
		//270������ ũ�� �������� �̵�
		if (_cam.rc.left > 50)
		{
			_position.x -= 12.f;
		}

		if (_cam.rc.top > 150)
		{
			_position.y -= 5.f;
		}

		//�ٽ� ���ư� ��ġ ����
		_tempPt = { _position.x, _position.y };

		break;
		//���������� �̵� ����
	case state::R_MOVE:
		//270�� ���� ������ ���������� �̵�
		if (_cam.rc.right < WINSIZEX - 50)
		{
			_position.x += 12.f;
		}

		if (_cam.rc.top > 150)
		{
			_position.y -= 5.f;
		}

		//�ٽ� ���ư� ��ġ ����
		_tempPt = { _position.x, _position.y };

		break;
		//���� ����
	case state::DEATH:
		//�浹 ��Ʈ ���ֱ�
		_col.rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);

		if (_position.y + _size.y / 2 < WINSIZEY)
		{
			//��ü �κ� ����߸���
			_position.y += 5.f;
		}
		//���� �������� ��
		if (_position.y + _size.y / 2 >= WINSIZEY)
		{
			_deathTimer++;

			if (_deathTimer % 100 == 0)
			{
				OBJECTMANAGER->RemoveObject(ObjectType::ENEMY, OBJECTMANAGER->FindObject(ObjectType::ENEMY, "flybug"));
			}
		}

		break;
	}

}

void FlyBug::Render()
{
	//ī�޶� ��Ʈ �׸���
	Rectangle(getMemDC(), _cam.rc);
	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);
	//�浹��Ʈ �׸���
	Rectangle(getMemDC(), _col.rc);
	//��üó����Ʈ �׸���
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _part[i].rc);
	}
	//�ؽ�Ʈ ���
	sprintf(msg1, "x : %d, y : %d", _pt.x, _pt.y);
	TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));
}
