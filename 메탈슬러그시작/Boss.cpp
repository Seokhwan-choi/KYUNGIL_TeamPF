#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "FireCannon.h"
#include "Bomb.h"

Boss::Boss(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

Boss::~Boss()
{
}

HRESULT Boss::Init()
{
	//���� �ʱ�ȭ
	_state = state::IDLE;
	//���� ó���� ���� ����
	_angle = 0.f;
	//ó�� ���� ������ �ʱ�ȭ
	_isStart = false;
	//���� ���� Ÿ�̸� �ʱ�ȭ
	_attTimer = 0;
	//���� ���� ������ �ʱ�ȭ
	_attDelay = 25;
	//�������� �� ���� ������ �ʱ�ȭ
	_stopDelay = 150;
	//�ڷ� ������ Ÿ�̸� �ʱ�ȭ
	_moveTimer = 0;
	//�ڷ� ���� ������ Ÿ�̸�
	_moveBuffTimer = 0;
	//�ڷ� ������ �� ������ �ʱ�ȭ
	_moveDelay = 210;
	//���� �� ������ Ÿ�̸� �ʱ�ȭ
	_delayTimer = 0;
	//�����Ӱ��� ���� �ʱ�ȭ
	_isMoveAttack = false;
	//���� ���� �ʱ�ȭ
	_isAttack = false;
	//������ ���� ���� ���� �ʱ�ȭ
	_isAttackFinish = false;
	//���� ü�� �ʱ�ȭ
	_hp = 300;
	//���� ó���� ���� ����
	_deathTimer = 0;
	//���� ���� ���� �ʱ�ȭ
	_isBuff = false;
	//���� ���� ���� ����
	_isBuffStart = false;
	//���� ���� ���� ���� ����
	_isBuffStartEnd = false;
	//���� ȭ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_fShoot[i].pt = { _position.x, _position.y };
	}
	_fShoot[0].rc = RectMakeCenter(_fShoot[0].pt.x - 118.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);
	_fShoot[1].rc = RectMakeCenter(_fShoot[1].pt.x + 78.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);

	//���� ��ź ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_bShoot.pt = { _position.x, _position.y };
	_bShoot.rc = RectMakeCenter(_bShoot.pt.x + 108.f, _bShoot.pt.y - _size.y / 2 + 130.f, 50, 50);

	//���� ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_att.pt = { _position.x, _position.y };
	_att.rc = RectMakeCenter(_att.pt.x + _size.x / 2 - 100.f, _att.pt.y, 300.f, 200.f);

	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�");

	//�÷��̾���� ���� �ʱ�ȭ
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//ȭ���� Ŭ���� �ʱ�ȭ
	_fireCannon = new FireCannon("ȭ����");
	_fireCannon->Init("�Լ�.bmp", 30, 30, 1, 1200);

	//��ź Ŭ���� �ʱ�ȭ
	_bomb = new Bomb("�̻�����ź");
	_bomb->Init("�Լ�.bmp", 30, 30, 1, 1200);

	return S_OK;
}

void Boss::Release()
{
	//ȭ���� ����
	_fireCannon->Release();
	SAFE_DELETE(_fireCannon);

	//�̻�����ź ����
	_bomb->Release();
	SAFE_DELETE(_bomb);
}

void Boss::Update()
{
	//�������� Ÿ�̸�
	if (_hp > 0)
	{
		_attTimer++;
	}

	//���� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//���� ȭ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_fShoot[i].pt = { _position.x, _position.y };
	}
	_fShoot[0].rc = RectMakeCenter(_fShoot[0].pt.x - 118.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);
	_fShoot[1].rc = RectMakeCenter(_fShoot[1].pt.x + 78.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);

	//���� ��ź ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_bShoot.pt = { _position.x, _position.y };
	_bShoot.rc = RectMakeCenter(_bShoot.pt.x + 108.f, _bShoot.pt.y - _size.y / 2 + 130.f, 50, 50);

	//���� ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_att.pt = { _position.x, _position.y };
	_att.rc = RectMakeCenter(_att.pt.x - 200.f, _att.pt.y + 150.f, 300.f, 200.f);

	//ó���� ���� ���� ó��
	if (_rc.right < WINSIZEX / 2 - 50 && !_isStart && !_isBuffStart && !_isBuffStartEnd)
	{
		_position.x += 7.f;
	}

	//ȭ�� �߰� ��ġ�� ���� �Ͽ��� �� ���� ó�� �Ϸ�
	if (_rc.right >= WINSIZEX / 2 - 50 && !_isBuffStart && !_isBuffStartEnd)
	{
		_isStart = true;
	}

	//���� �� �ٽ� ���� ó��
	if (_isBuffStart && _rc.right < WINSIZEX / 2 - 50 && !_isBuffStartEnd)
	{
		_position.x += 8.f;
	}

	//ȭ�� �߰� ��ġ�� ���� �Ͽ��� �� ���� ���� ó�� �Ϸ�
	if (_isBuffStart && _rc.right >= WINSIZEX / 2 - 50)
	{
		_isBuffStartEnd = true;
	}

	//�������°� �ƴҶ� �������� ������ ����
	if (_isStart && !_isBuffStart && !_isBuffStartEnd)
	{
		_moveTimer++;
		_attDelay = 55;
	}
	//�������� �� �� ������ Ÿ�̸� ����
	if (_isBuffStartEnd)
	{
		_moveBuffTimer++;
	}

	//���� �Ϸ� �� �ڷ� �����̰� �ϴ� Ÿ�̸� ����
	if (_isStart && !_isAttack && !_isBuffStartEnd && _hp > 0)
	{
		//ȭ���� �߻� ���
		if (_attTimer % 75 == 0)
		{
			this->fireShoot();
		}
		
		//������ �� ���� �ڷ� �����̰� ���
		if (_moveTimer % _moveDelay == 0)
		{
			_state = STATE::BACK_MOVE;
			_moveTimer = 0;
		}
	}
	//���� ���� �Ϸ� �� �ڷ� �����̰� �ϴ� Ÿ�̸� ����
	else if (!_isAttack && _isBuffStartEnd && _hp > 0)
	{
		//ü�¿� ���� �߻� ���
		if (_attTimer % 50 == 0)
		{
			this->fireBomb();
		}

		//������ �� ���� �ڷ� �����̰� ���
		if (_moveBuffTimer % _moveDelay == 0)
		{
			_state = STATE::BACK_MOVE;
			_moveBuffTimer = 0;
		}
	}

	//������ �̵� ���� ����� �޾��� �� �ణ ���
	if (_isAttack)
	{
		_delayTimer++;

		if (_delayTimer % _stopDelay == 0)
		{
			_state = STATE::ATTACK;
		}
	}

	//ü�¿� ���� ���� ����
	if (_hp > 150)
	{
		_isBuff = false;
		_stopDelay = 150;
		_moveDelay = 210;
	}
	else if (_hp == 150 && !_isBuffStart)
	{
		_position.x = -WINSIZEX / 4;
		_isBuffStart = true;
	}
	else if (_hp < 150 && _hp > 0)
	{
		_isBuff = true;
		_stopDelay = 60;
		_moveDelay = 150;
	}
	else if (_hp <= 0)
	{
		_hp = 0;
		_state = STATE::DEATH;
	}

	//���¿� ���� ������ ó��
	switch (_state)
	{
	case STATE::BACK_MOVE:
		if (_rc.right > 100.f)
		{
			_position.x -= 5;
		}
		//�ڷ� �� �̵��Ͽ��� ��� ������ �̵� ���� ���
		if (_rc.right <= 100.f)
		{
			_isAttack = true;
		}
		break;
	case STATE::ATTACK:
		//������ �̵� ����
		if (_rc.right < WINSIZEX / 2 - 50)
		{
			_position.x += 5;
			//ü�¿� ���� ���� ������ ����
			if (!_isBuff)
			{
				_attDelay = 25;
			}
			else
			{
				_attDelay = 15;
			}
		}

		//ȭ�� �߾ӿ��� ��� ������ ��
		if (_rc.right >= WINSIZEX / 2 - 50)
		{
			//ü�¿� ���� ���� ������ ����
			if (!_isBuff)
			{
				_attDelay = 55;
			}
			else
			{
				_attDelay = 35;
			}
			_isAttack = false;
		}
		break;
	case STATE::DEATH:
		if (_rc.top < WINSIZEY + 50)
		{
			_position.y += 2.5f;
		}

		break;
	}

	//������ �ʸ��� ���� ���� ó��
	if (_attTimer % _attDelay == 0
		|| _attTimer % _attDelay == 1
		|| _attTimer % _attDelay == 2
		|| _attTimer % _attDelay == 3
		|| _attTimer % _attDelay == 4
		|| _attTimer % _attDelay == 5)
	{
		_att.rc.left += 500.f;
		_att.rc.right += 500.f;
	}

	//���� �׽�Ʈ
	if (KEYMANAGER->isStayKeyDown('O'))
	{
		_hp = 150;
	}
	//���� �׽�Ʈ
	if (KEYMANAGER->isStayKeyDown('P'))
	{
		_hp = 0;
	}

	//���� ȭ���� ������ ó��
	_fireCannon->leftFireMove();

	//������ ȭ���� ������ ó��
	_fireCannon->rightFireMove();

	//�̻��� ��ź ������ ó��
	_bomb->move();


	//�¿� ������ �׽�Ʈ
	/*if (KEYMANAGER->isStayKeyDown('T'))
	{
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('U'))
	{
		_position.x += 5.f;
	}*/

	//���� ���� �׽�Ʈ
	/*if (KEYMANAGER->isStayKeyDown('I'))
	{
		_att.rc.left += 600.f;
		_att.rc.right += 600.f;
	}*/
}

void Boss::Render()
{
	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);

	//ȭ���� ���� ��Ʈ �׸���
	for (int i = 0; i < 2; i++)
	{
		Rectangle(getMemDC(), _fShoot[i].rc);
	}

	//ȭ���� �׸���
	_fireCannon->Render();

	//��ź ���� ó�� ��Ʈ �׸���
	Rectangle(getMemDC(), _bShoot.rc);

	//�̻��� ��ź �׸���
	_bomb->Render();

	//���� ���� ó�� ��Ʈ �׸���
	Rectangle(getMemDC(), _att.rc);

	//�ؽ�Ʈ ���
	//sprintf(msg1, "_fireDist : %f", _fireDist);
	//TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));
}

//���� ȭ���� �߻� ���
void Boss::fireShoot()
{
	for (int i = 0; i < 2; i++)
	{
		float centerX = _fShoot[i].rc.left + (_fShoot[i].rc.right - _fShoot[i].rc.left) / 2;
		float centerY = _fShoot[i].rc.top + (_fShoot[i].rc.bottom - _fShoot[i].rc.top) / 2;

		if (i == 0)
		{
			_fireCannon->leftFire(centerX, centerY, PI / 180 * 60, 6.f);
		}
		else if (i == 1)
		{
			//�߻��� ����� �÷��̾� ��ǥ
			_fireCannon->setPosition(_player->GetPosition().x, _player->GetPosition().y);

			_fireCannon->rightFire(centerX, centerY, PI / 180 * 30, 15.f);
		}
	}
}

//��ź �߻� ���
void Boss::fireBomb()
{
	float centerX = _bShoot.rc.left + (_bShoot.rc.right - _bShoot.rc.left) / 2;
	float centerY = _bShoot.rc.top + (_bShoot.rc.bottom - _bShoot.rc.top) / 2;

	//�߻��� ����� �÷��̾� ��ǥ
	_bomb->setPosition(_player->GetPosition().x, _player->GetPosition().y);

	_bomb->fire(centerX, centerY, PI / 180 * 20, 15.f);
}
