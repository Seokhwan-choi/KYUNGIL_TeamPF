#include "stdafx.h"
#include "BigCrab.h"
#include "Player.h"
#include "Bubble.h"

BigCrab::BigCrab(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot) : GameObject(name, pos, size, pivot)
{
}


BigCrab::~BigCrab()
{
}

HRESULT BigCrab::Init()
{
	//상태 초기화
	_state = state::L_IDLE;
	//게 카메라 렉트 초기화
	for (int i = 0; i < 4; i++)
	{
		_cam[i].pt = { _position.x,_position.y };
		_cam[i].isCrush = false;
	}
	//_cam[0].rc = RectMakeCenter(_cam[0].pt.x, _cam[0].pt.y, _size.x * 8.f, _size.y);
	//_cam[1].rc = RectMakeCenter(_cam[1].pt.x, _cam[1].pt.y, _size.x * 5.f, _size.y);
	//_cam[2].rc = RectMakeCenter(_cam[2].pt.x, _cam[2].pt.y - 200, _size.x * 3.f, _size.y / 2);
	//_cam[3].rc = RectMakeCenter(_cam[3].pt.x, _cam[3].pt.y, _size.x * 2.3f, _size.y);

	//충돌 렉트 초기화
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x,_position.y };
	}
	//위쪽
	_col[0].rc = RectMakeCenter(_col[0].pt.x + 5, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	//아래쪽
	_col[1].rc = RectMakeCenter(_col[1].pt.x + 5, _col[1].pt.y + _size.y / 3 + 19, _size.x - 30, _size.y / 5);
	//오른쪽
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	//왼쪽
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);
	//플레이어 클래스 초기화
	player = (Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어");
	//공격용 렉트 초기화
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x,_position.y };
	}
	//왼쪽공격용 렉트
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 4, _att[0].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//오른쪽공격용 렉트
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 4 + 10, _att[1].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//카운트 초기화
	count = 0;
	//왼쪽입니다
	isLeft = true;
	//플레이어와의 각도 초기화
	_angle = GetAngle(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);

	_bubble = new Bubble("거품");
	_bubble->Init2("Enemy/거품.bmp", 480, 60, 7, 1, 6, 1280);

	_isBubbleShoot = false;
	_bubbleGauge = 1;
	_isStop = false;
	bubbleMax = -1;
	_isBubbleShootFinish = false;
	_isAttack = false;
	_bubblefinishcount = 0;
	//이미지 초기화
	_bigCrabImg[0] = IMAGEMANAGER->findImage("bigcrab");
	_bigCrabImg[1] = IMAGEMANAGER->findImage("bigcrab2");
	_bigCrabImg[2] = IMAGEMANAGER->findImage("bigcrab3");
	_bigCrabImg[3] = IMAGEMANAGER->findImage("bigcrab4");
	_bigCrabImg[4] = IMAGEMANAGER->findImage("bigcrab5");
	_bigCrabImg[5] = IMAGEMANAGER->findImage("bigcrab6");


	for (int i = 0; i < 2; i++)
	{
		_imgCount[i] = 0;
	}

	for (int i = 0; i < 8; i++)
	{
		index[i] = 0;
		countImg[i] = 1;
	}
	_gauge = 1;
	index[8] = 11;
	countImg[8] = 1;
	index[9] = 22;
	countImg[9] = 1;
	_probeY = _position.y + (_size.y / 2);
	_pixelImage = IMAGEMANAGER->findImage("지하배경픽셀");

	_deathTimer = 1;

	//체력 초기화
	_hp = 20;

	return S_OK;
}

void BigCrab::Release()
{
}

void BigCrab::Update()
{
	this->rectmove();
	_bubble->move1();
	_bubble->render();

	//항시 중력 적용
	_position.y += 5.f;

	//픽셀 충돌 처리
	_probeY = _position.y + (_size.y / 2) - 30;

	for (int i = _probeY - 150; i < _probeY + 150; i++)
	{
		COLORREF color = GetPixel(_pixelImage->getMemDC(), _position.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			_position.y = i - _size.y / 2 + 50;
			break;
		}

	}

	//각도 체크
	_angle = GetAngle(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	//거리 체크
	_dist = GetDistance(_position.x, _position.y, player->GetPosition().x, player->GetPosition().y);
	//이동 테스트
	/*if (KEYMANAGER->isStayKeyDown('I'))
	{
		_position.x -= 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('P'))
	{
		_position.x += 5.f;
	}
	if (KEYMANAGER->isStayKeyDown('O'))
	{
		_position.y -= 5.f;
	}*/

	//체력이 0일 경우 죽음 상태로 변경
	if (_hp <= 0 || KEYMANAGER->isOnceKeyDown('P'))
	{
		_state = state::DEATH;
	}

	this->Attcol();
	this->Crabpattern();

	countImg[0]++;
	if (countImg[0] % 12 == 0)
	{
		index[0]++;
		if (index[0] > 6)
		{
			index[0] = 0;
		}
	}

}

void BigCrab::Render()
{
	//카메라 렉트 그리기
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), CAMERA->Relative(_cam[i].rc));
	}
	//큰게 렉트 그리기
	Rectangle(getMemDC(), CAMERA->Relative(_rc));
	//큰게 이미지 그리기
	if (_state == state::L_IDLE && !(_state == state::L_MOVE) && !(_state == state::L_ATTACK) && !(_state == state::DEATH))
	{
		_bigCrabImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[0], 0);
	}
	if (_state == state::R_IDLE && !(_state == state::R_MOVE) && !(_state == state::R_ATTACK) && !(_state == state::DEATH))
	{
		_bigCrabImg[0]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[0], 1);
	}
	if (_state == state::L_MOVE && !(_state == state::L_ATTACK) && !(_state == state::DEATH))
	{
		_bigCrabImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[1], 0);
	}
	if (_state == state::R_MOVE && !(_state == state::R_ATTACK) && !(_state == state::DEATH))
	{
		_bigCrabImg[1]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[1], 1);
	}
	if (_state == state::L_ATTACK && !(_state == state::L_BUBBLE_SHOOT_MOVE) && !(_state == state::DEATH))
	{
		_bigCrabImg[2]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[2], 0);
	}
	if (_state == state::R_ATTACK && !(_state == state::R_BUBBLE_SHOOT_MOVE) && !(_state == state::DEATH))
	{
		_bigCrabImg[2]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[3], 1);
	}
	if (_state == state::L_BUBBLE_SHOOT_MOVE && !(_state == state::DEATH))
	{
		_bigCrabImg[3]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[4], 0);
	}
	if (_state == state::R_BUBBLE_SHOOT_MOVE && !(_state == state::DEATH))
	{
		_bigCrabImg[3]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[5], 1);
	}
	if (_state == state::DEATH)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			if (index[6] < 11)
			{
				_bigCrabImg[4]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[6], 0);
			}
			if (index[6] == 11)
			{
				_bigCrabImg[5]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[7], 0);
			}
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			if (index[8] > 0)
			{
				_bigCrabImg[4]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[8], 1);
			}
			if (index[8] == 0)
			{
				_bigCrabImg[5]->frameRender(getMemDC(), _rc.left - CAMERA->GetCamera().left - 300, _rc.top - 150 - CAMERA->GetCamera().top, index[9], 1);
			}
		}

	}


	Rectangle(getMemDC(), CAMERA->Relative(_pixelrc));
	//큰게 충돌렉트 그리기
	//for (int i = 0; i < 4; i++)
	//{
	//	Rectangle(getMemDC(), CAMERA->Relative(_col[i].rc));
	//}
	//큰게 공격용렉트 그리기
	//for (int i = 0; i < 2; i++)
	//{
	//	Rectangle(getMemDC(), CAMERA->Relative(_att[i].rc));
	//}
	//거품 그리기
	_bubble->Render();
}

void BigCrab::Attcol()
{
	RECT temp;
	if (IntersectRect(&temp, &_cam[1].rc, &player->GetRect()) && !IntersectRect(&temp, &_cam[3].rc, &player->GetRect()))
	{
		_cam[1].isCrush = true;
		_isAttack = true;
	}
	else
	{
		_cam[1].isCrush = false;

	}
	if (IntersectRect(&temp, &_cam[1].rc, &player->GetRect()) && IntersectRect(&temp, &_cam[3].rc, &player->GetRect()))
	{
		_cam[3].isCrush = true;
	}
	else
	{
		_cam[3].isCrush = false;
	}
	if (IntersectRect(&temp, &_cam[2].rc, &player->GetRect()))
	{
		_cam[2].isCrush = true;
	}
	else
	{
		_cam[2].isCrush = false;
	}
	if (IntersectRect(&temp, &_cam[0].rc, &player->GetRect()))
	{
		_cam[0].isCrush = true;
	}
	else
	{
		_cam[0].isCrush = false;
	}
}

void BigCrab::rectmove()
{
	//큰게 렉트
	_rc = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
	//픽셀 렉트
	_pixelrc = RectMakeCenter(_position.x, _probeY, 50, 50);
	//카메라 렉트 게 중심으로 따라다니게 하기
	for (int i = 0; i < 3; i++)
	{
		_cam[i].pt = { _position.x,_position.y };
	}
	_cam[0].rc = RectMakeCenter(_cam[0].pt.x, _cam[0].pt.y, _size.x * 8.f, _size.y);
	_cam[1].rc = RectMakeCenter(_cam[1].pt.x, _cam[1].pt.y, _size.x * 5.f, _size.y);
	//_cam[2].rc = RectMakeCenter(_cam[2].pt.x, _cam[2].pt.y - 200, _size.x * 3.f, _size.y / 2);
	_cam[3].rc = RectMakeCenter(_cam[2].pt.x, _cam[2].pt.y, _size.x * 2.3f, _size.y);
	//충돌 렉트 게 중심으로 따라다니게 하기
	for (int i = 0; i < 4; i++)
	{
		_col[i].pt = { _position.x,_position.y };
	}
	//위쪽
	_col[0].rc = RectMakeCenter(_col[0].pt.x + 5, _col[0].pt.y - _size.y / 2, _size.x - 30, _size.y / 5);
	//아래쪽
	_col[1].rc = RectMakeCenter(_col[1].pt.x + 5, _col[1].pt.y + _size.y / 3 + 19, _size.x - 30, _size.y / 5);
	//오른쪽
	_col[2].rc = RectMakeCenter(_col[2].pt.x - _size.x / 2 + 5, _col[2].pt.y, _size.x / 10, _size.y);
	//왼쪽
	_col[3].rc = RectMakeCenter(_col[3].pt.x + _size.x / 2 + 5, _col[3].pt.y, _size.x / 10, _size.y);

	//공격용 렉트 초기화
	for (int i = 0; i < 2; i++)
	{
		_att[i].pt = { _position.x,_position.y };
	}
	//왼쪽공격용 렉트
	_att[0].rc = RectMakeCenter(_att[0].pt.x - _size.x / 4, _att[0].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);
	//오른쪽공격용 렉트
	_att[1].rc = RectMakeCenter(_att[1].pt.x + _size.x / 4 + 10, _att[1].pt.y - _size.y / 15 + 90, _size.x / 3, _size.y - 150);

}

void BigCrab::Crabpattern()
{
	//if (!_cam[0].isCrush && !_cam[1].isCrush && !_cam[2].isCrush && !_cam[3].isCrush)
	//{
	//	_state = state::L_IDLE;
	//}
	if (_cam[0].isCrush == true && _isStop == false)
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

	if (_cam[1].isCrush && _isStop == false && _isAttack == true && _bubble->getVBubble()[5].isFire == false)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_BUBBLE_SHOOT_MOVE;
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_BUBBLE_SHOOT_MOVE;
		}
		_isStop = true;
	}

	if (_dist <= player->GetSize().x / 2 + _size.x / 2 && (!(_state == state::L_BUBBLE_SHOOT_MOVE)) && !(_state == state::R_BUBBLE_SHOOT_MOVE))
	{
		_isAttack = false;
	}

	if ((_cam[3].isCrush && _isAttack == true) && _bubble->getVBubble()[5].isFire == true)
	{
		_gauge++;
		if (_gauge % 140 == 0)
		{
			_isAttack = false;
			_gauge = 1;
		}
	}
	if (_cam[3].isCrush && _isAttack == false)
	{
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_state = state::L_ATTACK;
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_state = state::R_ATTACK;
		}
	}
	if (_state == state::L_MOVE)
	{
		countImg[1]++;
		if (countImg[1] % 12 == 0)
		{
			index[1]++;
			if (index[1] > 11)
			{
				index[1] = 0;
			}
		}
		if (_dist > 300.f)
		{
			_position.x -= 5.f;
		}
	}
	else
	{
		index[1] = 0;
	}
	if (_state == state::R_MOVE)
	{
		countImg[1]++;
		if (countImg[1] % 12 == 0)
		{
			index[1]++;
			if (index[1] > 11)
			{
				index[1] = 0;
			}
		}
		if (_dist > 300.f)
		{
			_position.x += 5.f;
		}
	}
	else
	{
		index[1] = 0;
	}


	if (_state == state::L_ATTACK)
	{
		countImg[2]++;
		if (countImg[2] % 12 == 0)
		{
			index[2]++;
			if (index[2] > 5)
			{
				index[2] = 0;
			}
		}
		_att[0].rc.left -= _size.x / 2 + 40.f;
		_att[0].rc.right -= _size.x / 2 + 40.f;
	}
	if (_state == state::R_ATTACK)
	{
		countImg[3]++;
		if (countImg[3] % 12 == 0)
		{
			index[3]--;
			if (index[3] < 0)
			{
				index[3] = 5;
			}
		}
		_att[1].rc.left += _size.x / 2 + 40.f;
		_att[1].rc.right += _size.x / 2 + 40.f;
	}



	if (_state == state::L_BUBBLE_SHOOT_MOVE)
	{
		//if (_dist < 400.f && _rc.right <= WINSIZEX)
		//{
		//	_position.x += 5.f;
		//}
		//거품발사명령(끝 지점일 때도 플레이어와 충돌이 아닐 경우 거품 발사 명령)
		//if (_dist >= 400.f || _rc.right <= WINSIZEX)
		//{
		//	_isBubbleShoot = true;
		//}

		countImg[4]++;
		if (countImg[4] % 12 == 0)
		{
			index[4]++;
			if (index[4] > 6)
			{
				index[4] = 6;
			}

		}
		_imgCount[0]++;
		if (_imgCount[0] > 64)
		{
			_isBubbleShoot = true;
		}


	}
	if (_state == state::R_BUBBLE_SHOOT_MOVE)
	{
		//if (_dist < 400.f && _rc.left >= 0.f)
		//{
		//	_position.x -= 5.f;
		//}
		//거품발사명령(끝 지점일 때도 플레이어와 충돌이 아닐 경우 거품 발사 명령)
		//if (_dist >= 400.f || _rc.left <= 0.f)
		//{
		//	_isBubbleShoot = true;
		//}
		countImg[5]++;
		if (countImg[5] % 12 == 0)
		{
			index[5]--;
			if (index[5] < 0)
			{
				index[5] = 8;
			}

		}
		_imgCount[1]++;
		if (_imgCount[1] > 64)
		{
			_isBubbleShoot = true;
		}
	}

	if (_isBubbleShoot == true)
	{
		_bubbleGauge++;
	}
	if (_bubbleGauge % 25 == 0 && bubbleMax < 6)
	{
		index[4] = 7;
		if (_angle <= PI + PI / 2 && _angle > PI / 2)
		{
			_bubble->fire(_position.x + 300, _position.y - 60, _angle, 5.f);
		}
		if (_angle < PI / 2 && _angle >= 0.f || _angle > PI + PI / 2 && _angle <= PI * 2)
		{
			_bubble->fire(_position.x, _position.y - 60, _angle, 5.f);
		}

		//값 초기화
		_bubbleGauge = 1;
		_isBubbleShoot = false;
		++bubbleMax;
	}
	if (bubbleMax > 5)
	{
		_isBubbleShootFinish = true;

	}
	if (_isBubbleShootFinish == true)
	{
		_bubblefinishcount++;
	}
	if (_bubblefinishcount == 50)
	{
		_isStop = false;
		_isBubbleShootFinish = false;
		bubbleMax = -1;
		index[4] = 8;
		_bubblefinishcount = 0;
	}
	if (index[4] == 8)
	{
		index[4] = 0;
	}
	if (_state == state::DEATH)
	{
		//충돌 렉트 없애기
		for (int i = 0; i < 4; i++)
		{
			_col[i].rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);
		}
		//공격 렉트 없애기
		for (int i = 0; i < 2; i++)
		{
			_att[i].rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);
		}

		countImg[6]++;
		if (countImg[6] % 10 == 0)
		{
			index[6]++;
			if (index[6] > 11)
			{
				index[6] = 11;
			}

		}
		if (index[6] == 11)
		{
			countImg[7]++;
			if (countImg[7] % 10 == 0)
			{
				index[7]++;
				if (index[7] > 22)
				{
					index[7] = 22;
				}
			}
		}

		countImg[8]++;
		if (countImg[8] % 10 == 0)
		{
			index[8]--;
			if (index[8] < 0)
			{
				index[8] = 0;
			}

		}
		if (index[8] == 0)
		{
			countImg[9]++;
			if (countImg[9] % 10 == 0)
			{
				index[9]--;
				if (index[9] < 0)
				{
					index[9] = 0;
				}
			}
		}

		_deathTimer++;
		if (_deathTimer % 150 == 0)
		{
			_rc = RectMakeCenter(-1000.f, -1000.f, _size.x, _size.y / 2);

		}
		if (_bubble->getVBubble()[5].isFire == false)
		{
			_isActive = false;
		}

	}
}
