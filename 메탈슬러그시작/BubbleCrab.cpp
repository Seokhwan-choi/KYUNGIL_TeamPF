#include "stdafx.h"
#include "BubbleCrab.h"
#include "Player.h"
#include "Bubble.h"

BubbleCrab::BubbleCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

BubbleCrab::~BubbleCrab()
{
}

HRESULT BubbleCrab::Init()
{
	//���� �ʱ�ȭ
	_state = state::IDLE;
	_isStop = false;
	//���� ó���� ���� ����
	_gauge = 1;
	_bubbleGauge = 1;
	_angle = 0.f;
	_isAttack = false;
	_isAttackFinish = false;
	_isBubbleShoot = false;
	_isBubbleShootFinish = false;
	_moveTimer = 1;
	//��ǰ�� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//���� ó���� ���� ����
	_deathTimer = 0;

	//��ǰ�� ī�޶� ��Ʈ(�׻� �� �߾��� ����ٴѴ�.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 18.f, _size.y);
	_cam.isCrush = false;

	//��ǰ�� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//��ǰ�� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
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

	//��ǰ Ŭ���� �ʱ�ȭ
	_bubble = new Bubble("��ǰ");
	_bubble->Init("�Լ�.bmp", 30, 30, 3, 1280);

	return S_OK;
}

void BubbleCrab::Release()
{
	_bubble->Release();
	SAFE_DELETE(_bubble);
}

void BubbleCrab::Update()
{
	//��ǰ�� ��Ʈ
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);

	//��ǰ�� ��üó�� ��Ʈ
	for (int i = 0; i < 3; i++)
	{
		_part[i].pt = { _position.x + _size.x / 2 * (i - 1), _position.y };
		_part[i].rc = RectMakeCenter(_part[i].pt.x, _part[i].pt.y, 50, 10);
	}

	//��ǰ�� ī�޶� ��Ʈ(�׻� �� �߾��� ����ٴѴ�.)
	_cam.pt = { _position.x, _position.y };
	_cam.rc = RectMakeCenter(_cam.pt.x, _cam.pt.y, _size.x * 18.f, _size.y);

	//��ǰ�� �浹 ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x, _position.y };
	}
	_col[0].rc = RectMakeCenter(_col[0].pt.x, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	_col[1].rc = RectMakeCenter(_col[1].pt.x, _col[1].pt.y + _size.y / 3 + 10, _size.x - 30, _size.y / 5);
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//��ǰ�� ���� ��Ʈ(�׻� �� �߾��� ���� �ٴѴ�.)
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
		_state = state::IDLE;
	}

	//�÷��̾� ������ ���� ī�޶�� �浹 ó��
	RECT rcCam;
	if (IntersectRect(&rcCam, &_cam.rc, &_player->GetRect()))
	{
		_cam.isCrush = true;
	}

	//ī�޶�� �浹�� ��� ������ ���� ������ ����
	if (_cam.isCrush && !_isStop)
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

	//�÷��̾���� �Ÿ��� 300.f���� �۰� �÷��̾�� �浹�� �ƴ� �� ��ǰ �߻縦 ���� �̵� ���
	if (!_isStop && _dist <= 300.f && _dist > 100.f)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_BUBBLE_SHOOT_MOVE;
		}

		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_BUBBLE_SHOOT_MOVE;
		}

		//ī�޶� ���� ����
		_isStop = true;
	}
	//�÷��̾�� �浹�� ��� ���� ���� ���
	else if (_dist <= _player->GetSize().x / 2 + _size.x / 2)
	{
		_isAttack = true;
	}

	//���� ���� ���� �ƴ� �� ��ǰ ���� ����� ���� ���� ���� ��ٸ� ���� ��ǰ �߻�
	if (_isBubbleShoot && !_isBubbleShootFinish && !_isAttack && !_isAttackFinish)
	{
		_bubbleGauge++;
	}

	//��ǰ �ѹ߾� �߻� ó��
	if (_bubbleGauge % 50 == 0)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_bubble->fire(_position.x - 50.f, _position.y, _angle, 5.f);
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_bubble->fire(_position.x + 50.f, _position.y, _angle, 5.f);
		}

		//�� �ʱ�ȭ
		_bubbleGauge = 1;
		_isBubbleShoot = false;
		_isBubbleShootFinish = true;
	}

	//�߻� �� �ణ ������ �̵� ó��
	if (_isBubbleShootFinish)
	{
		_moveTimer++;

		if (_moveTimer % 25 == 0)
		{
			if (_angle <= PI + PI / 2 && _angle > PI / 2)
			{
				_state = state::L_BUBBLE_SHOOT_FINISH;
			}


			if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
			{
				_state = state::R_BUBBLE_SHOOT_FINISH;
			}
		}
	}

	//���� ���� ����� �������� �� ���� ������ �� ���⿡ ���� ���� ���� ó��
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

	//���� ������ ������ �ڷ� ���� ó��
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
	case state::L_BUBBLE_SHOOT_MOVE:
		if (_dist < 400.f && _rc.right <= WINSIZEX)
		{
			_position.x += 5.f;
		}
		//��ǰ�߻���(�� ������ ���� �÷��̾�� �浹�� �ƴ� ��� ��ǰ �߻� ���)
		if (_dist >= 400.f || _rc.right >= WINSIZEX)
		{
			_isBubbleShoot = true;
		}
		break;
	case state::R_BUBBLE_SHOOT_MOVE:
		if (_dist < 400.f && _rc.left >= 0.f)
		{
			_position.x -= 5.f;
		}
		//��ǰ�߻���(�� ������ ���� �÷��̾�� �浹�� �ƴ� ��� ��ǰ �߻� ���)
		if (_dist >= 400.f || _rc.left <= 0.f)
		{
			_isBubbleShoot = true;
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
	case state::L_BUBBLE_SHOOT_FINISH:

		if (_dist > 300.f)
		{
			_position.x -= 5.f;
		}

		if (_dist <= 300.f || _rc.right <= WINSIZEX)
		{
			_isBubbleShootFinish = false;
			_isStop = false;
			_moveTimer = 1; 
		}

		break;
	case state::R_BUBBLE_SHOOT_FINISH:
		if (_dist > 300.f)
		{
			_position.x += 5.f;
		}

		if (_dist <= 300.f || _rc.left >= 0)
		{
			_isBubbleShootFinish = false;
			_isStop = false;
			_moveTimer = 1;
		}

		break;
	case state::L_ATTACK_FINISH:
		if (_dist <= 300.f && _rc.right <= WINSIZEX)
		{
			_position.x += 5.f;
		}
		if (_dist > 300.f || _rc.right >= WINSIZEX)
		{
			_isAttackFinish = false;
			_isStop = false;
		}
		break;
	case state::R_ATTACK_FINISH:
		if (_dist < 300.f && _rc.left >= 0)
		{
			_position.x -= 5.f;
		}
		if (_dist >= 300.f || _rc.left <= 0)
		{
			_isAttackFinish = false;
			_isStop = false;
		}
		break;
	}

	//��ǰ ������ ó��
	_bubble->move();
}

void BubbleCrab::Render()
{
	//ī�޶� ��Ʈ �׸���
	Rectangle(getMemDC(), _cam.rc);

	//��Ʈ �׸���
	Rectangle(getMemDC(), _rc);

	//�浹��Ʈ �׸���
	for (int i = 0; i < 4; i++)
	{
		//Rectangle(getMemDC(), _col[i].rc);
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
	sprintf(msg1, "x : %f", _dist);
	TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));

	//��ǰ �׸���
	_bubble->Render();
}
