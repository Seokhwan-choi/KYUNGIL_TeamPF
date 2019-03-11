#include "stdafx.h"
#include "FireCannon.h"

FireCannon::FireCannon(string name) : GameObject(name)
{
}

FireCannon::~FireCannon()
{
}

HRESULT FireCannon::Init(const char * imageName, int width, int height, int fireCannonMax, float range)
{
	_fireCannonMax = fireCannonMax;
	_range = range;
	_x, _y = 0.f;
	//벡터에 넣기 위해 임시 구조체 생성
	for (int i = 0; i < fireCannonMax; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			FIRECANNON fireCannon;

			ZeroMemory(&fireCannon, sizeof(FIRECANNON));
			fireCannon.fireCannonImage = new image;
			fireCannon.fireCannonImage->init(imageName, width, height, true, RGB(255, 0, 255));
			fireCannon.isFire = false;

			_vFireCannon[j].push_back(fireCannon);
		}
	}

	return S_OK;
}

void FireCannon::Release()
{
	for (int i = 0; i < 2; i++)
	{
		vector<FIRECANNON>::iterator _idx = _vFireCannon[i].begin();
		vector<FIRECANNON>::iterator _end = _vFireCannon[i].end();

		for (_idx; _idx != _end; ++_idx)
		{
			_idx->fireCannonImage->release();
			SAFE_DELETE(_idx->fireCannonImage);
		}
	}
}

void FireCannon::Update()
{
	this->leftFireMove();
}

void FireCannon::Render()
{
	for (int i = 0; i < 2; i++)
	{
		vector<FIRECANNON>::iterator _idx = _vFireCannon[i].begin();
		vector<FIRECANNON>::iterator _end = _vFireCannon[i].end();

		for (_idx; _idx != _end; ++_idx)
		{
			if (!_idx->isFire) continue;

			_idx->fireCannonImage->render(getMemDC(), _idx->rc.left, _idx->rc.top);
		}
	}
}

void FireCannon::leftFire(float x, float y, float angle, float speed)
{
	vector<FIRECANNON>::iterator _idx = _vFireCannon[0].begin();
	vector<FIRECANNON>::iterator _end = _vFireCannon[0].end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (_idx->isFire) continue;

		_idx->isFire = true;
		_idx->x = _idx->fireX = x;
		_idx->y = _idx->fireY = y;
		_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage->getWidth(), _idx->fireCannonImage->getHeight());
		_idx->speed = speed;
		_idx->angle = angle;

		break;
	}
}

void FireCannon::rightFire(float x, float y, float angle, float speed)
{
	vector<FIRECANNON>::iterator _idx = _vFireCannon[1].begin();
	vector<FIRECANNON>::iterator _end = _vFireCannon[1].end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (_idx->isFire) continue;

		_idx->isFire = true;
		_idx->x = _idx->fireX = x;
		_idx->y = _idx->fireY = y;
		_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage->getWidth(), _idx->fireCannonImage->getHeight());
		_idx->speed = speed;
		_idx->angle = angle;

		break;
	}
}

void FireCannon::leftFireMove()
{
	vector<FIRECANNON>::iterator _idx = _vFireCannon[0].begin();
	vector<FIRECANNON>::iterator _end = _vFireCannon[0].end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (!_idx->isFire) continue;

		_idx->gravity += 0.35f;

		_idx->x += cosf(_idx->angle) * _idx->speed;
		_idx->y += -sinf(_idx->angle) * _idx->speed + _idx->gravity;

		_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage->getWidth(), _idx->fireCannonImage->getHeight());

		float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

		//사거리 멀어지면 화염포 사라짐
		if (_range < dist)
		{
			_idx->isFire = false;
			_idx->gravity = 0.f;
		}
	}
}

void FireCannon::rightFireMove()
{
	vector<FIRECANNON>::iterator _idx = _vFireCannon[1].begin();
	vector<FIRECANNON>::iterator _end = _vFireCannon[1].end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (!_idx->isFire) continue;

		_idx->gravity += 0.45f;

		//발사 당시의 플레이어 위치를 기억해 각도를 계속 계산한다.
		float _angle = GetAngle(_idx->x, _idx->y, _x, _y);
		//280도가 되었을 경우 발사 당시의 플레이어 위치로 각도 보정
		if(_angle <= PI / 180 * 280)
		{
			_idx->angle = PI / 180 * 280;
			_idx->gravity = 0.f;
		}
		_idx->x += cosf(_idx->angle) * _idx->speed;
		_idx->y += -sinf(_idx->angle) * _idx->speed + _idx->gravity;
	
		_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage->getWidth(), _idx->fireCannonImage->getHeight());

		float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

		//사거리 멀어지면 화염포 사라짐
		if (_range < dist)
		{
			_idx->isFire = false;
			_idx->gravity = 0.f;
		}
	}
}
