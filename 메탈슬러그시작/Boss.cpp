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
	_attDelay = 30;
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

	//���� �浹 ó�� ��Ʈ
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_position.x, _position.y, _size.x - 100.f, _size.y - 100.f);

	//���� ȭ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_fShoot[i].pt = { _position.x, _position.y };
	}
	_fShoot[0].rc = RectMakeCenter(_fShoot[0].pt.x - 118.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);
	_fShoot[1].rc = RectMakeCenter(_fShoot[1].pt.x + 78.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);

	//���� ��ź ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_bShoot.pt = { _position.x, _position.y };
	_bShoot.rc = RectMakeCenter(_bShoot.pt.x + 108.f, _bShoot.pt.y - _size.y / 2 + 230.f, 50, 50);

	//���� ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_att.pt = { _position.x, _position.y };
	_att.rc = RectMakeCenter(_att.pt.x + _size.x / 2 - 100.f, _att.pt.y + 250.f, 300.f, 200.f);


	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = (Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�");

	//�÷��̾���� ���� �ʱ�ȭ
	_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//ȭ���� Ŭ���� �ʱ�ȭ
	_fireCannon = new FireCannon("ȭ����");
	_fireCannon->Init("Enemy/ȭ����.bmp", 100, 100, 4, 1, 5, 1200);

	//��ź Ŭ���� �ʱ�ȭ
	_bomb = new Bomb("�̻�����ź");
	_bomb->Init("Enemy/����.bmp", 1650, 200, 11, 1, 1, 1200);

	//�ٸ� �̹��� �ʱ�ȭ
	for (int i = 0; i < 22; i++)
	{
		string idx = to_string(i + 1);
		string key = "�ٸ�" + idx;

		_bridgeImg[i] = IMAGEMANAGER->findImage(key);
	}

	for (int i = 0; i < 7; i++)
	{
		_index[i] = 0;
		_countImg[i] = 0;
	}
	_deathWaterIndex[0] = 0;
	_deathWaterIndex[1] = 6;
	_deathWaterIndex[2] = 12;
	_deathWaterIndex[3] = 8;
	_deathWaterIndex[4] = 24;
	speed = 6;
	_BoassImg[0] = IMAGEMANAGER->findImage("boss");
	_BoassImg[1] = IMAGEMANAGER->findImage("boss1");
	_BoassImg[2] = IMAGEMANAGER->findImage("boss2");
	_BoassImg[3] = IMAGEMANAGER->findImage("boss3");
	_BoassImg[4] = IMAGEMANAGER->findImage("boss4");
	_BoassImg[5] = IMAGEMANAGER->findImage("boss5");
	_BoassImg[6] = IMAGEMANAGER->findImage("boss6");
	_deathWater = IMAGEMANAGER->findImage("deathwater");
	_alpha[0] = 255;
	_alpha[1] = 255;
	_isdeathWaterEnd = false;
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

	//���� �浹 ó�� ��Ʈ
	_col.pt = { _position.x, _position.y };
	_col.rc = RectMakeCenter(_position.x, _position.y, _size.x - 100.f, _size.y - 100.f);

	//���� ȭ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 2; i++)
	{
		_fShoot[i].pt = { _position.x, _position.y };
	}
	_fShoot[0].rc = RectMakeCenter(_fShoot[0].pt.x - 118.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);
	_fShoot[1].rc = RectMakeCenter(_fShoot[1].pt.x + 78.f, _fShoot[0].pt.y - _size.y / 2, 50, 50);

	//���� ��ź ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_bShoot.pt = { _position.x, _position.y };
	_bShoot.rc = RectMakeCenter(_bShoot.pt.x + 108.f, _bShoot.pt.y - _size.y / 2 + 230.f, 50, 50);

	//���� ���� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	_att.pt = { _position.x, _position.y };
	_att.rc = RectMakeCenter(_att.pt.x - 200.f, _att.pt.y + 250.f, 300.f, 200.f);

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
		_position.x += 9.f;
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
		_attDelay = 70;
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
		if (_attTimer % 110 == 0 && _state != STATE::BACK_MOVE)
		{
			_state = STATE::FIRECANNON_SHOOT;
			_index[1] = 0;
			for (int i = 0; i < 5; i++)
			{
				this->fireShoot();
			}
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
		if (_attTimer % 60 == 0 && _state != STATE::BACK_MOVE)
		{
			_state = STATE::BOMB_SHOOT;
			_index[4] = 0;
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
		_stopDelay = 140;
		_moveDelay = 210;
	}
	else if (_hp == 150 && !_isBuffStart)
	{
		_position.x = -WINSIZEX / 4;
		_isBuffStart = true;
		_attTimer = 0;
	}
	else if (_hp <= 150 && _hp > 0)
	{
		_isBuff = true;
		_stopDelay = 30;
		_moveDelay = 150;
	}
	else if (_hp <= 0)
	{
		_hp = 0;
		_state = STATE::DEATH;
	}
	if (!_isBuff)
	{
		_countImg[0]++;
		if (_countImg[0] % speed == 0)
		{
			_index[0]++;
			if (_index[0] > 11)
			{
				_index[0] = 0;
			}
		}
	}
	if (_isBuffStart)
	{
		_countImg[2]++;
		if (_countImg[2] % speed == 0)
		{
			_index[2]++;
			if (_index[2] > 11)
			{
				_index[2] = 11;
			}
		}
	}
	if (_index[2] == 11)
	{
		_countImg[3]++;
		if (_countImg[3] % speed == 0)
		{
			_index[3]++;
			if (_index[3] > 11)
			{
				_index[3] = 0;
			}
		}
	}
	//���¿� ���� ������ ó��
	switch (_state)
	{
	case STATE::BACK_MOVE:
		speed = 6;
		if (_rc.right > 100.f)
		{
			if (!_isBuff)
			{
				_position.x -= 5;
			}
			else
			{
				_position.x -= 10;
			}
		}
		//�ڷ� �� �̵��Ͽ��� ��� ������ �̵� ���� ���
		if (_rc.right <= 100.f)
		{
			_isAttack = true;
		}
		break;
	case STATE::ATTACK:
		//������ �̵� ����
		speed = 3;
		if (_rc.right < WINSIZEX / 2 - 50)
		{
			//ü�¿� ���� ���� �ӵ� ����
			if (!_isBuff)
			{
				_position.x += 5;
				_attDelay = 35;
			}
			else
			{
				_position.x += 15;
				_attDelay = 25;
			}
		}

		//ȭ�� �߾ӿ��� ��� ������ ��
		if (_rc.right >= WINSIZEX / 2 - 50)
		{
			speed = 6;
			//ü�¿� ���� ���� ������ ����
			if (!_isBuff)
			{
				_attDelay = 70;
			}
			else
			{
				_attDelay = 55;
			}
			_isAttack = false;
		}
		break;
	case STATE::FIRECANNON_SHOOT:
		_countImg[1]++;
		if (_countImg[1] % 10 == 0)
		{
			_index[1]++;
			if (_index[1] > 11)
			{
				_index[1] = 0;
			}
		}
		break;
	case STATE::BOMB_SHOOT:
		_countImg[4]++;
		if (_countImg[4] % 10 == 0)
		{
			_index[4]++;
			if (_index[4] > 11)
			{
				_index[4] = 0;
			}
		}
		break;
	case STATE::DEATH:
		_countImg[5]++;
		if (_countImg[5] % 10 == 0)
		{
			_index[5]++;
			if (_index[5] > 23)
			{
				_index[5] = 0;
			}
		}
		
		_alpha[0] -= 200;
		if (_alpha[0] < 0)
		{
			_alpha[0] = 255;
		}
		if (_rc.top < WINSIZEY + 50)
		{
			_position.y += 2.5f;
			_countImg[6]++;
			if (_countImg[6] % 2 == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					_deathWaterIndex[i]++;
					if (_deathWaterIndex[i] > 25)
					{
						_deathWaterIndex[i] = 0;
					}
				}
			}
		}
		if (_rc.top >= WINSIZEY + 50)
		{
			_countImg[6]++;
			if (_countImg[6] % 2 == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					_deathWaterIndex[i]++;
					if (_deathWaterIndex[i] > 25)
					{
						_deathWaterIndex[i] = 25;
					}
				}
			}

			if (_deathWaterIndex[0] == 25
				&& _deathWaterIndex[1] == 25
				&& _deathWaterIndex[2] == 25
				&& _deathWaterIndex[3] == 25
				&& _deathWaterIndex[4] == 25)
			{
				_alpha[1] -= 10;
				if (_alpha[1] < 0)
				{
					_alpha[1] = 0;
				}
			}
		}
		if (_alpha[1] == 0)
		{
			_isdeathWaterEnd = true;
		}
		break;
	}

	//������ �ʸ��� ���� ���� ó��
	if (_attTimer % _attDelay == 0
		|| _attTimer % _attDelay == 1
		|| _attTimer % _attDelay == 2
		|| _attTimer % _attDelay == 3
		|| _attTimer % _attDelay == 4
		//|| _attTimer % _attDelay == 5
		) 
		
	{
		_att.rc.left += 410.f;
		_att.rc.right += 410.f;
	}

	//�ٸ� �浹 üũ �ӽ� ��Ʈ
	RECT rc;
	//�ٸ��� �浹 üũ
	for (int i = 0; i < 22; i++)
	{
		if (IntersectRect(&rc, &_att.rc, &_bridgeImg[i]->boudingBox()))
		{
			//�ӽ÷� ����
			_bridgeImg[i]->setX(-200);
		}
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

	//����,������ ȭ���� ������ ó��
	_fireCannon->Update();

	//�̻��� ��ź ������ ó��
	_bomb->Update();

	RECT temp;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (IntersectRect(&temp, &_player->GetRect(), &_fireCannon->getVFireCannon(i)[j].rc))
			{
				//exit(0);
			}
		}
		
	}
	if (IntersectRect(&temp, &_player->GetRect(), &_bomb->getVBomb()[0].rc))
	{
		//exit(0);
	}
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
	//���� ��Ʈ �׸���
	//Rectangle(getMemDC(), _rc);

	//�浹 ��Ʈ �׸���
	//Rectangle(getMemDC(), _col.rc);

	if ((_state == state::IDLE || _state == state::BACK_MOVE || _state == state::ATTACK)
		&& !_isBuff
		&& !(_state == state::FIRECANNON_SHOOT) 
		&& !(_state == state::BOMB_SHOOT)
		&& !_isBuffStart
		&& !(_state == state::DEATH))
	{
		_BoassImg[0]->frameRender(getMemDC(), _rc.left, _rc.top - 100, _index[0], 0);
	}
	if (!(_state == state::BACK_MOVE) 
		&& !_isBuff
		&& _state == state::FIRECANNON_SHOOT)
	{
		_BoassImg[1]->frameRender(getMemDC(), _rc.left, _rc.top - 100, _index[1], 0);
	}
	if (_isBuffStart && !_isBuffStartEnd)
	{
		_BoassImg[2]->frameRender(getMemDC(), _rc.left, _rc.top - 100, _index[2], 0);
	}
	if ((_state == state::IDLE || _state == state::BACK_MOVE || _state == state::ATTACK)
		&& !(_state == state::FIRECANNON_SHOOT)
		&& !(_state == state::BOMB_SHOOT)
		&& (_isBuffStartEnd)
		&& !(_state == state::DEATH))
	{
		_BoassImg[3]->frameRender(getMemDC(), _rc.left, _rc.top - 100, _index[3], 0);
	}
	if (!(_state == state::BACK_MOVE)
		&& (_isBuffStartEnd)
		&& _state == state::BOMB_SHOOT)
	{

		_BoassImg[4]->frameRender(getMemDC(), _rc.left, _rc.top - 100, _index[4], 0);
	}
	if (_state == state::DEATH)
	{
		//_BoassImg[6]->frameRender(getMemDC(), _rc.left, _rc.top - 100, _index[5], 0);
		_BoassImg[6]->alphaFrameRender(getMemDC(), _rc.left, _rc.top - 100, _index[5], 0, _alpha[0]);
		RECT rc[5];
		rc[0] = RectMakeCenter(60, WINSIZEY - 200, 100, 400);
		rc[1] = RectMakeCenter(180, WINSIZEY - 200, 100, 400);
		rc[2] = RectMakeCenter(300, WINSIZEY - 200, 100, 400);
		rc[3] = RectMakeCenter(420, WINSIZEY - 200, 100, 400);
		rc[4] = RectMakeCenter(540, WINSIZEY - 200, 100, 400);
		
		for (int i = 0; i < 5; i++)
		{
			if (_isdeathWaterEnd == false)
			{
				//_deathWater->frameRender(getMemDC(), rc[i].left, rc[i].top, _deathWaterIndex[i], 0);
				_deathWater->alphaFrameRender(getMemDC(), rc[i].left, rc[i].top, _deathWaterIndex[i], 0, _alpha[1]);
			}
		}
		
		
	}
	//ȭ���� ���� ��Ʈ �׸���
	//for (int i = 0; i < 2; i++)
	//{
	//	Rectangle(getMemDC(), _fShoot[i].rc);
	//}

	//ȭ���� �׸���
	_fireCannon->Render();

	//��ź ���� ó�� ��Ʈ �׸���
	//Rectangle(getMemDC(), _bShoot.rc);

	//�̻��� ��ź �׸���
	_bomb->Render();

	//���� ���� ó�� ��Ʈ �׸���
	//Rectangle(getMemDC(), _att.rc);

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
			_fireCannon->leftFire(centerX, centerY, PI / 180 * 35, 6.f);
		}
		else if (i == 1)
		{
			//�߻��� ����� �÷��̾� ��ǥ
			_fireCannon->setPosition(_player->GetPosition().x, _player->GetPosition().y);

			_fireCannon->rightFire(centerX - 100, centerY + 50, PI / 180 * 30, 15.f);
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

	_bomb->fire(centerX + 30, centerY + 30, PI / 180 * 20, 15.f);
}
