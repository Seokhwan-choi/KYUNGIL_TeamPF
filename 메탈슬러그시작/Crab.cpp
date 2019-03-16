
#include "stdafx.h"
#include "crab.h"
#include "Player.h"

Crab::Crab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}

Crab::~Crab()
{

}

void Crab::death()
{
	RECT temp;
	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&temp, &_att[i].rc, &_player->GetCollisionPlayer()))
		{
			cout << "kill" << endl;
		}
	}
	
}

HRESULT Crab::Init()
{
	//���� �ʱ�ȭ
	_state = state::IDLE;

	//�̹��� �ʱ�ȭ
	crabImg[0] = IMAGEMANAGER->findImage("crab");
	crabImg[1] = IMAGEMANAGER->findImage("crab1");
	crabImg[2] = IMAGEMANAGER->findImage("crab2");
	crabImg[3] = IMAGEMANAGER->findImage("crab3");
	crabImg[4] = IMAGEMANAGER->findImage("crab4");
	crabImg[5] = IMAGEMANAGER->findImage("crab5");
	//�̹��� ������ ���� �ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		indexImg[i] = 0;
		countImg[i] = 0;
	}

	indexImg[4] = 22;
	countImg[4] = 0;
	//���� ó���� ���� ����
	_gauge = 1;
	_angle = 0.f;
	_isAttack = false;
	_isAttackFinish = false;

	//ü�� �ʱ�ȭ
	_hp = 5;

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

	_probeY = _position.y + _size.y / 2;
	_probeX = _position.x + _size.x / 2;
	_pixelImage = IMAGEMANAGER->findImage("����ȼ�");
	_pixelGravity = 1.f;

	return S_OK;
}

void Crab::Release()
{
}

void Crab::Update()
{
	this->death();
	//�̵� �׽�Ʈ
	/*if (KEYMANAGER->isStayKeyDown('I')) {
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('P')) {
		_position.x += 5.f;
	}*/

	//�׽� �߷� ����
	_position.y += _pixelGravity;

	//�Ʒ��� �浹��Ʈ ��ġ ��ǥ ������Ʈ
	_probeY = _position.y + _size.y/2;
	_probeX = _position.x + _size.x/2;
	//�ȼ� �浹 ó��
	
	for (int i = _probeY; i < _probeY + 360; i++)
	{
		COLORREF color = GetPixel(_pixelImage->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if ((r == 255 && g == 255 && b == 0))
		{
			_pixelGravity = 0.f;
			_position.y = i - _size.y / 2 - 140;
	
			break;
		}
	}

	for (int i = _probeX; i < _probeX + 50; i++)
	{
		COLORREF color = GetPixel(_pixelImage->getMemDC(), i, _position.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			_pixelGravity = 0.f;
			_position.x = i - _size.x / 2 - 140;

			break;
		}
	}
	
	
	//�ȼ� ��Ʈ
	_pixelrc[0] = RectMakeCenter(_position.x, _probeY, 10, 10);
	_pixelrc[1] = RectMakeCenter(_probeX, _position.y, 10, 10);
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

	//ü�¿� ���� ���� ó��
	if (KEYMANAGER->isToggleKey('R') || _hp <= 0)
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

			if (_deathTimer % 150 == 0)
			{
				_isActive = false;
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
			if (_deathTimer % 150 == 0)
			{
				_isActive = false;
			}
		}

		break;
	}

	//���¿� ���� �̹��� ����
	this->crabImage();

}

void Crab::Render()
{
	//�� �̹��� �׸���
	this->crabImageRender();

	//��Ʈ ����
	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	
	//	//ī�޶� ��Ʈ �׸���
	//	Rectangle(getMemDC(), CAMERA->Relative(_cam.rc));

	//	//��Ʈ �׸���
	//	Rectangle(getMemDC(), CAMERA->Relative(_rc));

	//	//�浹��Ʈ �׸���
	//	for (int i = 0; i < 4; i++)
	//	{
	//		//Rectangle(getMemDC(), CAMERA->Relative(_col[i].rc));
	//	}

	//	//��üó����Ʈ �׸���
	//	for (int i = 0; i < 3; i++)
	//	{
	//		Rectangle(getMemDC(), CAMERA->Relative(_part[i].rc));
	//	}
	//	//����ó����Ʈ �׸���
	//	for (int i = 0; i < 2; i++)
	//	{
	//		Rectangle(getMemDC(), CAMERA->Relative(_att[i].rc));
	//	}
	//	//��Ʈ �׸���
	//	Rectangle(getMemDC(), CAMERA->Relative(_rc));
		//�ȼ� ���� ��Ʈ �׸���
	//	Rectangle(getMemDC(), CAMERA->Relative(_pixelrc[0]));
	//	Rectangle(getMemDC(), CAMERA->Relative(_pixelrc[1]));
	//}
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
	if (_state == state::L_DEATH)
	{
		countImg[3]++;
		if (countImg[3] % 7 == 0)
		{
			indexImg[3]++;
			if (indexImg[3] > 21)
			{
				indexImg[3] = 0;
			}
			crabImg[4]->setFrameX(indexImg[3]);
		}
	}
	if (_state == state::R_DEATH)
	{
		countImg[4]++;
		if (countImg[4] % 7 == 0)
		{
			indexImg[4]--;
			if (indexImg[4] < 0)
			{
				indexImg[4] = 21;
			}
			crabImg[5]->setFrameX(indexImg[4]);
		}
	}
}

void Crab::crabImageRender()
{
	if ((_state == state::L_IDLE || _state == state::L_MOVE || _state == state::L_ATTACK_MOVE) && !(_state == state::L_ATTACK_FINISH))
	{
		crabImg[0]->frameRender(getMemDC(), CAMERA->Relative(_rc).left, CAMERA->Relative(_rc).top, indexImg[0], 0);
	}
	if (_state == state::R_IDLE || _state == state::R_MOVE || _state == state::R_ATTACK_MOVE)
	{
		crabImg[1]->frameRender(getMemDC(), CAMERA->Relative(_rc).left, CAMERA->Relative(_rc).top, indexImg[0], 0);
	}
	if (_state == state::L_ATTACK)
	{
		crabImg[2]->frameRender(getMemDC(), _rc.left - 60 - CAMERA->GetCamera().left -300, _rc.top - 22 - CAMERA->GetCamera().top, indexImg[1], 0);

	}
	if (_state == state::R_ATTACK)
	{
		crabImg[3]->frameRender(getMemDC(), _rc.left + 10 - CAMERA->GetCamera().left - 300, _rc.top - 22 - CAMERA->GetCamera().top, indexImg[1], 0);
	}
	if (_state == state::L_ATTACK_FINISH)
	{
		crabImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[2], 0);
	}
	if (_state == state::R_ATTACK_FINISH)
	{
		crabImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[2], 0);
	}
	if (_state == state::L_DEATH)
	{
		crabImg[4]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 44 - CAMERA->GetCamera().top, indexImg[3], 0);
	}
	if (_state == state::R_DEATH)
	{
		crabImg[5]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 44 - CAMERA->GetCamera().top, indexImg[4], 0);
	}
}
