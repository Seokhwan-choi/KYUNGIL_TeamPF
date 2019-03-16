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
	//_state = state::IDLE;
	//���� ������ ó���� ���� ���� �ʱ�ȭ
	_move = 0;
	_isUp = false;
	//���� ó���� ���� ����
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	_isAttackReturn = false;
	//ü�� �ʱ�ȭ
	_hp = 3;

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
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, 500, 550);
	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�");
	//�÷��̾���� ���� �ʱ�ȭ
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	//���ڸ� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_col.pt.x + _size.y / 2, _col.pt.y, _size.x, _size.y / 2);
	//���ڸ� �̹��� �ʱ�ȭ
	_flyBugImg[0] = IMAGEMANAGER->findImage("flybug");
	_flyBugImg[1] = IMAGEMANAGER->findImage("flybug1");
	_flyBugImg[2] = IMAGEMANAGER->findImage("flybug2");
	_flyBugImg[3] = IMAGEMANAGER->findImage("flybug3");
	_flyBugImg[4] = IMAGEMANAGER->findImage("flybug4");

	for (int i = 0; i < 5; i++)
	{
		_index[i] = 0;
		_countImg[i] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		_alpha[i] = 255;
	}

	//�÷��̾�� �Ÿ� ���
	_dist = GetDistance(_cam.pt.x, _cam.pt.y, _player->GetPosition().x, _player->GetPosition().y);

	//�ٽ� ���ư� ��ġ ����
	_tempPt = { _position.x, _position.y };
	//ó�� ������ǥ�� �Ÿ� ���
	_initDist = GetDistance(_position.x, _position.y, _tempPt.x, _tempPt.y);
	//���� �� �÷��̾���� ���� ���
	_attackAngle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	count = 0;
	return S_OK;
}

void FlyBug::Release()
{
}

void FlyBug::Update()
{
	//���ڸ� ó�� ������ǥ�� �Ÿ� ���
	_initDist = GetDistance(_position.x, _position.y, _tempPt.x, _tempPt.y);
	_dist = GetDistance(_cam.pt.x, _cam.pt.y, _player->GetPosition().x, _player->GetPosition().y);
	//cout << "ó���Ÿ� : " << _initDist << endl;
	//cout << _dist << endl;
	//��� ���� �̹��� ó�� ���� 
	_countImg[0]++;
	if (_countImg[0] % 1 == 0)
	{
		_index[0]++;
		if (_index[0] > 23)
		{
			_index[0] = 0;
		}
	}

	//���ڸ� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//���ڸ� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + 50 * (i - 1), _position.y };
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
	//cout << _angle << endl;
	//�÷��̾���� �Ÿ��� 1100���� �۰� ������ 180���� 360 �����̰� ���� ���� ������ �� ��� ���� ����
	if (_dist <= 1100 && (_angle > PI && _angle < PI * 2) && !_isAttackReturn)
	{
		_state = state::IDLE;
	}

	//���� ������ 5�� ���̸� �׶� ���� ���·� ����
	if (_gauge % 5 == 0 && _state == state::IDLE && !_isAttackReturn)
	{	
		_state = state::ATTACK;
		//���� ���� ����
		if (!_isAttack)
		{
			_isAttack = true;
		}
	}

	if (!_isAttack)
	{
		//���� ���� ���� �� �÷��̾�� ���� ���
		_attackAngle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	}

	//�÷��̾� �Ѿ˰� �浹 üũ
	if (KEYMANAGER->isToggleKey('R') || _hp <= 0)
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
			//cout << "idle" << endl;
			//�Ʒ��� �̵�
			if (!_isUp)
			{
				//_position.x += 2.f;
				_position.y += 5.f;
				_move += 1;
			}
			//���� �̵�
			else
			{
				//_position.x -= 2.f;
				_position.y -= 5.f;
				_move += 1;
			}

			//25 �̵��� �ݴ�� �̵�
			if (_move > 16)
			{
				_move = 0;
				_isUp = !_isUp;
				_gauge++;
				//cout << _gauge << endl;
			}

		break;
		//���� ����
		case state::ATTACK:
			//cout << "A_Angle : " << _attackAngle << endl;
			//���� �̹��� ���� ó��
			_countImg[1]++;
			if (_countImg[1] % 1 == 0)
			{
				_index[1]++;
				if (_index[1] > 26)
				{
					_index[1] = 0;
				}
			}
			//�浹�Ǳ� ������ ���ڸ��� ����
			_position.x += cosf(_attackAngle) * 10.f;
			_position.y += -sinf(_attackAngle) * 10.f;
	
			//�浹 üũ(�÷��̾�� �浹 �Ǵ� ī�޶��� ���ҿ��� ���� 200��ġ�� �浹 ��)
			RECT rc;
			if (IntersectRect(&rc, &_rc, &_player->GetRect()) || _position.y > CAMERA->GetCamera().bottom - 200)
			{
				//cout << "�浹" << endl;
				_isAttackReturn = true;
				//�浹�� ���� ���� ���·� ����
				_state = STATE::ATTACK_FINISH;
			}
		break;
		case state::ATTACK_FINISH:
			//ó�� ���� ��ġ�� �ٽ� ���ƿ��� ������ �̵�
			if (_initDist > 0)
			{
				_position.x += cosf(_attackAngle - PI) * 10.f;
				_position.y += -sinf(_attackAngle - PI) * 10.f;
			}
			//ó�� ���� ��ġ�� ���ƿ��� �ٽ� ��� ���·� ���ư�
			if (_initDist == 0)
			{
				//���� ��� �ʱ�ȭ
				_isAttack = false;
				//���� �� ���ڸ��� �̵� ��� �ʱ�ȭ
				_isAttackReturn = false;
				//���� ������ �ʱ�ȭ
				_gauge = 1;
			}
		break;
		//���� ����
		case state::DEATH:
			_countImg[2]++;
			if (_countImg[2] % 5 == 0)
			{
				_index[2]++;
				if (_index[2] > 29)
				{
					_index[2] = 29;
				}
			}
			if (_index[2] == 29)
			{
				_alpha[1] -= 3;
				if (_alpha[1] <= 0)
				{
					_alpha[1] = 0;
				}
			}
			_countImg[3]++;
			if (_countImg[3] % 5 == 0)
			{
				_index[3]++;
				if (_index[3] > 12)
				{
					_index[3] = 0;
				}
			}
			_countImg[4]++;
			if (_countImg[4] % 5 == 0)
			{
				_index[4]++;
				if (_index[4] > 12)
				{
					_index[4] = 0;
				}
			}
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
				_index[3] = 12;
				if (_index[3] == 12)
				{
					_alpha[0] -= 50;
					if (_alpha[0] <= 0)
					{
						_alpha[0] = 255;
					}
				}
				_index[4] = 12;
				if (_index[4] == 12)
				{
					_alpha[2] -= 50;
					if (_alpha[2] <= 0)
					{
						_alpha[2] = 255;
					}
				}
				_deathTimer++;

				if (_deathTimer % 100 == 0)
				{
					OBJECTMANAGER->RemoveObject(ObjectType::ENEMY, OBJECTMANAGER->FindObject(ObjectType::ENEMY, "flyBug"));
				}
			}

		break;
	}

}

void FlyBug::Render()
{
	//��� �����̰ų� ���� �� ���ڸ��� �̵��� ��(����)
	if ((_state == state::IDLE && _attackAngle > PI / 180 * 270)
		|| (_state == state::ATTACK_FINISH && _attackAngle > PI / 180 * 270)
		&& !(_state == state::ATTACK) 
		&& !(_state == state::DEATH))
	{
		_flyBugImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[0], 0);
	}
	//��� �����̰ų� ���� �� ���ڸ��� �̵��� ��(������)
	if ((_state == state::IDLE && _attackAngle < PI / 180 * 270)
		|| (_state == state::ATTACK_FINISH && _attackAngle < PI / 180 * 270)
		&& !(_state == state::ATTACK)
		&& !(_state == state::DEATH))
	{
		_flyBugImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[0], 1);
	}
	//���� ���(����)
	if (_state == state::ATTACK && _attackAngle > PI / 180 * 270)
	{
		_flyBugImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[1], 0);
	}
	//���� ���(������)
	if (_state == state::ATTACK && _attackAngle < PI / 180 * 270)
	{
		_flyBugImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, _index[1], 1);
	}
	
	//��ü�̹���(����)
	//[2]:���� [3]:���ʳ��� [4]:�����ʳ���
	for (int i = 0; i < 3; i++)
	{
		if (_state == state::DEATH)
		{
			_flyBugImg[2]->alphaFrameRender(getMemDC(), _part[1].rc.left - CAMERA->GetCamera().left - 300, _part[1].rc.top - CAMERA->GetCamera().top, _index[2], 0, _alpha[1]);
			_flyBugImg[3]->alphaFrameRender(getMemDC(), _part[2].rc.left + 80 - CAMERA->GetCamera().left - 300, _part[2].rc.top + 20 - CAMERA->GetCamera().top, _index[3], 0, _alpha[0]);
			_flyBugImg[4]->alphaFrameRender(getMemDC(), _part[0].rc.left + 130 - CAMERA->GetCamera().left - 300, _part[0].rc.top + 20 - CAMERA->GetCamera().top, _index[4], 0, _alpha[2]);
		}
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		//ī�޶� ��Ʈ �׸���
		Rectangle(getMemDC(), CAMERA->Relative(_cam.rc));
		//��Ʈ �׸���
		Rectangle(getMemDC(), CAMERA->Relative(_rc));
		//�浹��Ʈ �׸���
		Rectangle(getMemDC(), CAMERA->Relative(_col.rc));
		//��üó����Ʈ �׸���
		for (int i = 0; i < 3; i++)
		{
			Rectangle(getMemDC(), CAMERA->Relative(_part[i].rc));
		}
	}
}