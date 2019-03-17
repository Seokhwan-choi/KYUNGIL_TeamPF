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
	_hp = 5;

	//�̹��� �ʱ�ȭ
	BubblecrabImg[0] = IMAGEMANAGER->findImage("bubblecrab");
	BubblecrabImg[1] = IMAGEMANAGER->findImage("bubblecrab2");
	BubblecrabImg[2] = IMAGEMANAGER->findImage("bubblecrab3");
	BubblecrabImg[3] = IMAGEMANAGER->findImage("bubblecrab4");
	BubblecrabImg[4] = IMAGEMANAGER->findImage("bubblecrab5");
	BubblecrabImg[5] = IMAGEMANAGER->findImage("bubblecrab6");
	BubblecrabImg[6] = IMAGEMANAGER->findImage("bubblecrab7");
	BubblecrabImg[7] = IMAGEMANAGER->findImage("bubblecrab8");
	//�̹��� ���� �ʱ�ȭ
	for (int i = 0; i < 6; i++)
	{
		indexImg[i] = 0;
		countImg[i] = 0;
	}
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
	//��ǰ�߻�� �÷��̾���� ���� �ʱ�ȭ
	_bubbleAngle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	//��ǰ Ŭ���� �ʱ�ȭ
	_bubble = new Bubble("��ǰ");
	_bubble->Init2("Enemy/��ǰ.bmp", 420, 60, 7, 1, 3, 1280);


	_probeY = _position.y + _size.y / 2;

	_pixelImage[0] = IMAGEMANAGER->findImage("����ȼ�");
	_pixelImage[1] = IMAGEMANAGER->findImage("���Ϲ���ȼ�");
	_pixelGravity = 1.f;

	//�ݺ��Ҹ� ������ ���� ����
	_deathSound = false;
	_bubbleShootSound = false;

	return S_OK;
}

void BubbleCrab::Release()
{
	_bubble->Release();
	SAFE_DELETE(_bubble);
}

void BubbleCrab::Update()
{
	RECT renderRect = CAMERA->Relative(_rc);
	if (renderRect.right < 0 || renderRect.left > WINSIZEX || renderRect.top < 0 || renderRect.bottom > WINSIZEY)
		return;


	RECT temp;
	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&temp, &_player->GetRect(), &_att[i].rc))
		{
			//exit(0);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (IntersectRect(&temp, &_player->GetRect(), &_bubble->getVBubble()[i].rc))
		{
			//exit(0);
		}
	}
	//�׽� �߷� ����
	_position.y += _pixelGravity;

	//�Ʒ��� �浹��Ʈ ��ġ ��ǥ ������Ʈ
	_probeY = _position.y + _size.y / 2;
	if (SCENEMANAGER->FindScene("����������") == true)
	{
		//�ȼ� �浹 ó��
		for (int i = _probeY - 20; i < _probeY + 360; i++)
		{
			COLORREF color = GetPixel(_pixelImage[0]->getMemDC(), _position.x, i);
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
	}
	if (SCENEMANAGER->FindScene("���Ͻ�������") == true)
	{
		//�ȼ� �浹 ó��
		for (int i = _probeY - 20; i < _probeY + 1060; i++)
		{
			COLORREF color = GetPixel(_pixelImage[1]->getMemDC(), _position.x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 255 && b == 0))
			{
				_pixelGravity = 0.f;
				_position.y = i - _size.y / 2;

				break;
			}
		}
	}
	

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

	//������� ���� üũ
	if (_hp > 0)
	{
		//�÷��̾�� ���� üũ
		_angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		//�÷��̾�� �Ÿ� üũ
		_dist = GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	}

	//���¿� ���� �̹��� ����
	this->bubblecrabImage();

	//��ǰ ������ ó��
	_bubble->move();
	_bubble->render();

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
	if ((_isBubbleShoot && !_isBubbleShootFinish && !_isAttack && !_isAttackFinish) 
		&& (_state == state::L_BUBBLE_SHOOT_MOVE || _state == state::R_BUBBLE_SHOOT_MOVE))
	{
		_bubbleGauge++;
		//��ǰ�߻�� �÷��̾���� ����
		float angle = GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

		//�÷��̾� ��ġ�� ���� ��ǰ�߻� ���� ����
		if (angle > PI / 2 && angle < PI / 180 * 270)
		{
			_bubbleAngle = PI;
		}
		else if (angle > PI / 180 * 270 && angle < PI / 2)
		{
			_bubbleAngle = 0.f;
		}
	}

	//��ǰ �ѹ߾� �߻� ó��
	if (_bubbleGauge % 83 == 0)
	{
		_bubbleShootSound = false;

		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_bubble->fire(_position.x + 150, _position.y, _bubbleAngle, 5.f);

			//��ǰ�Ҹ�
			if (!_bubbleShootSound)
			{
				SOUNDMANAGER->play("��ǰ����");
				_bubbleShootSound = true;
			}
		}
		else if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_bubble->fire(_position.x + 50, _position.y, _bubbleAngle, 5.f);

			//��ǰ�Ҹ�
			if (!_bubbleShootSound)
			{
				SOUNDMANAGER->play("��ǰ����");
				_bubbleShootSound = true;
			}
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

		if (_moveTimer % 30 == 0)
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

	//ü�¿� ���� ���� ó��
	if (KEYMANAGER->isToggleKey('R'))
	{
		_hp = 0;
	}

	//���� ó��
	if (_hp == 0)
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

	//�״� �Ҹ�
	if (_hp == 0 && !_deathSound)
	{
		SOUNDMANAGER->play("��ǰ������");
		_deathSound = true;
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
			indexImg[6] = 0;
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

		//�̹��� ������� �� Ÿ�̸�
		_deathTimer++;

		if (_deathTimer % 150 == 0)
		{
			_rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);

			//��ǰ�� ������� �׶� ��ü�� �������
			if (_bubble->getVBubble()[0].isFire == false
				&& _bubble->getVBubble()[1].isFire == false
				&& _bubble->getVBubble()[2].isFire == false)
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


		//�̹��� ������� �� Ÿ�̸�
		_deathTimer++;

		if (_deathTimer % 150 == 0)
		{
			_rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);

			//��ǰ�� ������� �׶� ��ü�� �������
			if (_bubble->getVBubble()[0].isFire == false
				&& _bubble->getVBubble()[1].isFire == false
				&& _bubble->getVBubble()[2].isFire == false)
			{
				_isActive = false;
			}
		}
		break;
	}
	
}

void BubbleCrab::Render()
{
	//ī�޶� ��Ʈ �׸���
	//Rectangle(getMemDC(), CAMERA->Relative(_cam.rc));

	//��Ʈ �׸���
	//Rectangle(getMemDC(), CAMERA->Relative(_rc));
	//�� �̹��� �׸���
	this->bubblecrabImageRender();
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
		//Rectangle(getMemDC(), CAMERA->Relative(_att[i].rc));
	}
	//�ؽ�Ʈ ���
	sprintf(msg1, "x : %f", _dist);
	TextOut(getMemDC(), 50, 50, msg1, strlen(msg1));

	//��ǰ �׸���
	_bubble->Render2();
}

void BubbleCrab::bubblecrabImage()
{
	if ((_state == state::L_IDLE 
		|| _state == state::L_MOVE 
		|| _state == state::L_ATTACK_MOVE 
		|| _state == state::L_BUBBLE_SHOOT_FINISH) 
		&& !(_state == state::L_ATTACK_FINISH))
	{
		countImg[0]++;
		if (countImg[0] % 10 == 0)
		{
			indexImg[0]++;
			if (indexImg[0] > 11)
			{
				indexImg[0] = 0;
			}
			BubblecrabImg[0]->setFrameX(indexImg[0]);
		}
	}
	if (_state == state::R_IDLE 
		|| _state == state::R_MOVE 
		|| _state == state::R_ATTACK_MOVE 
		&& !(_state == state::R_ATTACK_FINISH))
	{
		countImg[0]++;
		if (countImg[0] % 10 == 0)
		{
			indexImg[0]++;
			if (indexImg[0] > 11)
			{
				indexImg[0] = 0;
			}
			BubblecrabImg[1]->setFrameX(indexImg[0]);
		}
	}
	if (_state == state::L_BUBBLE_SHOOT_MOVE)
	{
		countImg[5]++;
		if (countImg[5] % 8 == 0)
		{
			indexImg[5]++;
			if (indexImg[5] > 12)
			{
				indexImg[5] = 0;
			}
			BubblecrabImg[6]->setFrameX(indexImg[5]);
		}
	}
	if (_state == state::R_BUBBLE_SHOOT_MOVE)
	{
		countImg[5]++;
		if (countImg[5] % 8 == 0)
		{
			indexImg[5]--;
			if (indexImg[5] < 0)
			{
				indexImg[5] = 12;
			}
			BubblecrabImg[7]->setFrameX(indexImg[5]);
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
			BubblecrabImg[2]->setFrameX(indexImg[1]);
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
			BubblecrabImg[3]->setFrameX(indexImg[1]);
		}
	}
	if (_state == state::L_ATTACK_FINISH || _state == state::L_BUBBLE_SHOOT_FINISH)
	{
		countImg[2]++;
		if (countImg[2] % 10 == 0)
		{
			indexImg[2]--;
			if (indexImg[2] < 0)
			{
				indexImg[2] = 11;
			}
			BubblecrabImg[0]->setFrameX(indexImg[2]);
		}
	}
	if (_state == state::R_ATTACK_FINISH || _state == state::R_BUBBLE_SHOOT_FINISH)
	{
		countImg[2]++;
		if (countImg[2] % 10 == 0)
		{
			indexImg[2]--;
			if (indexImg[2] < 0)
			{
				indexImg[2] = 11;
			}
			BubblecrabImg[1]->setFrameX(indexImg[2]);
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
				indexImg[3] = 21;
			}
			BubblecrabImg[4]->setFrameX(indexImg[3]);
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
				indexImg[4] = 0;
			}
			BubblecrabImg[5]->setFrameX(indexImg[4]);
		}
	}
	
}

void BubbleCrab::bubblecrabImageRender()
{
	if ((_state == state::L_IDLE 
		|| _state == state::L_MOVE 
		|| _state == state::L_ATTACK_MOVE) 
		&& !(_state == state::L_ATTACK_FINISH))
	{
		cout << "��ǰ�� �׸���" << endl;
		BubblecrabImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[0], 0);
	}

	if (_state == state::R_IDLE 
		|| _state == state::R_MOVE 
		|| _state == state::R_ATTACK_MOVE)
	{
		BubblecrabImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[0], 0);
	}

	if (_state == state::L_BUBBLE_SHOOT_MOVE)
	{
		BubblecrabImg[6]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[5], 0);

	}

	if (_state == state::R_BUBBLE_SHOOT_MOVE)
	{
		BubblecrabImg[7]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[5], 0);
	}

	if (_state == state::L_ATTACK)
	{
		BubblecrabImg[2]->frameRender(getMemDC(), _rc.left - 60 - CAMERA->GetCamera().left - 300, _rc.top - 22 - CAMERA->GetCamera().top, indexImg[1], 0);

	}

	if (_state == state::R_ATTACK)
	{
		BubblecrabImg[3]->frameRender(getMemDC(), _rc.left + 10 - CAMERA->GetCamera().left - 300, _rc.top - 22 - CAMERA->GetCamera().top, indexImg[1], 0);
	}

	if (_state == state::L_ATTACK_FINISH)
	{
		BubblecrabImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[2], 0);
	}

	if (_state == state::R_ATTACK_FINISH)
	{
		BubblecrabImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[2], 0);
	}

	if (_state == state::L_BUBBLE_SHOOT_FINISH)
	{
		BubblecrabImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[0], 0);
	}
	if (_state == state::R_BUBBLE_SHOOT_FINISH)
	{
		BubblecrabImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - CAMERA->GetCamera().top, indexImg[2], 0);
	}

	if (_state == state::L_DEATH && _deathTimer < 150)
	{
		BubblecrabImg[4]->frameRender(getMemDC(), _rc.left - 14 - CAMERA->GetCamera().left - 300, _rc.top - 44 - CAMERA->GetCamera().top, indexImg[3], 0);
	} 

	if (_state == state::R_DEATH && _deathTimer < 150)
	{
		BubblecrabImg[5]->frameRender(getMemDC(), _rc.left -14 - CAMERA->GetCamera().left - 300, _rc.top - 44 - CAMERA->GetCamera().top, indexImg[4], 0);
	}
}
