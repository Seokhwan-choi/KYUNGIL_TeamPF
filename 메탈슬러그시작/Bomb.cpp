#include "stdafx.h"
#include "Bomb.h"

Bomb::Bomb(string name) : GameObject(name)
{
}

Bomb::~Bomb()
{
}

HRESULT Bomb::Init(const char * imageName, int width, int height, int bombMax, float range)
{
	_bombMax = bombMax;
	_range = range;
	_x = 0.f;
	_y = 0.f;

	//벡터에 넣기 위해 임시 구조체 생성
	for (int i = 0; i < bombMax; i++)
	{
		//벡터에 넣기 위해 임시 구조체 생성
		BOMB bomb;

		ZeroMemory(&bomb, sizeof(BOMB));
		bomb.bombImage = new image;
		bomb.bombImage->init(imageName, width, height, true, RGB(255, 0, 255));
		bomb.isFire = false;

		_vBomb.push_back(bomb);
	}

	//다리 이미지 초기화
	_bridgeImg = IMAGEMANAGER->findImage("다리");

	return S_OK;
}

void Bomb::Release()
{
	vector<BOMB>::iterator _idx = _vBomb.begin();
	vector<BOMB>::iterator _end = _vBomb.end();

	for (_idx; _idx != _end; ++_idx)
	{
		_idx->bombImage->release();
		SAFE_DELETE(_idx->bombImage);
	}
}

void Bomb::Update()
{
	this->move();
}

void Bomb::Render()
{
	vector<BOMB>::iterator _idx = _vBomb.begin();
	vector<BOMB>::iterator _end = _vBomb.end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (!_idx->isFire) continue;

		_idx->bombImage->render(getMemDC(), _idx->rc.left, _idx->rc.top);
	}
}

void Bomb::fire(float x, float y, float angle, float speed)
{
	vector<BOMB>::iterator _idx = _vBomb.begin();
	vector<BOMB>::iterator _end = _vBomb.end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (_idx->isFire) continue;

		_idx->isFire = true;
		_idx->x = _idx->fireX = x;
		_idx->y = _idx->fireY = y;
		_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->bombImage->getWidth(), _idx->bombImage->getHeight());
		_idx->speed = speed;
		_idx->angle = angle;

		break;
	}
}

void Bomb::move()
{
	vector<BOMB>::iterator _idx = _vBomb.begin();
	vector<BOMB>::iterator _end = _vBomb.end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (!_idx->isFire) continue;

		_idx->gravity += 0.2f;

		//발사 당시의 플레이어 위치를 기억해 각도를 계속 계산한다.
		float _angle = GetAngle(_idx->x, _idx->y, _x, _y);
		//270도가 되었을 경우 발사 당시의 플레이어 위치로 각도 보정
		if (_angle <= PI / 180 * 270)
		{
			_idx->angle = PI / 180 * 270;
			_idx->gravity = 0.f;
		}

		_idx->x += cosf(_idx->angle) * _idx->speed;
		_idx->y += -sinf(_idx->angle) * _idx->speed + _idx->gravity;

		_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->bombImage->getWidth(), _idx->bombImage->getHeight());

		float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

		//다리 충돌 체크 임시 렉트
		RECT rc;
		//다리와 충돌 체크
		if (IntersectRect(&rc, &_idx->rc, &_bridgeImg->boudingBox()))
		{
			//펜 생성하기
			HPEN pen = CreatePen(PS_NULL, 0, RGB(255, 0, 255));
			//펜 사용하기
			HGDIOBJ oldPen = SelectObject(_bridgeImg->getMemDC(), pen);
			//붓 생성하기
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
			//붓 사용하기
			HGDIOBJ oldBrush = SelectObject(_bridgeImg->getMemDC(), brush);

			//렉트 그리기
			if (_idx->isFire)
			{
				Rectangle(_bridgeImg->getMemDC(), _idx->rc);
			}

			//펜 삭제 하기
			DeleteObject(oldPen);
			//붓 삭제 하기
			DeleteObject(oldBrush);

			//값 초기화
			_idx->isFire = false;
			_idx->gravity = 0.f;
		}

		//사거리 멀어지면 폭탄 사라짐
		if (_range < dist)
		{
			_idx->isFire = false;
			_idx->gravity = 0.f;
		}
	}
}
