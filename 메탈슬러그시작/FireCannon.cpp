#include "stdafx.h"
#include "FireCannon.h"

FireCannon::FireCannon(string name) : GameObject(name)
{
}

FireCannon::~FireCannon()
{
}

HRESULT FireCannon::Init(const char * imageName, int width, int height, int FrameX, int FrameY, int fireCannonMax, float range)
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
			fireCannon.fireCannonImage[0] = new image;
			fireCannon.fireCannonImage[0]->init(imageName, width, height, FrameX, FrameY, true, RGB(255, 0, 255));
			fireCannon.fireCannonImage[1] = new image;
			fireCannon.fireCannonImage[1]->init("Enemy/화염포꼬리.bmp",1440,200,18,1, true, RGB(255, 0, 255));
			fireCannon.isFire = false;

			_vFireCannon[j].push_back(fireCannon);
		}
	}

	//다리 이미지 초기화
	for (int i = 0; i < 22; i++)
	{
		string idx = to_string(i + 1);
		string key = "다리" + idx;

		_bridgeImg[i] = IMAGEMANAGER->findImage(key);
	}
	for (int i = 0; i < 5; i++)
	{
		index[i] = 0;
	}
	count = 0;
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
			_idx->fireCannonImage[0]->release();
			SAFE_DELETE(_idx->fireCannonImage[0]);
			_idx->fireCannonImage[1]->release();
			SAFE_DELETE(_idx->fireCannonImage[1]);
		}
	}
}

void FireCannon::Update()
{
	this->leftFireMove();
	this->rightFireMove();
}

void FireCannon::Render()
{
	
		vector<FIRECANNON>::iterator _idx = _vFireCannon[0].begin();
		vector<FIRECANNON>::iterator _end = _vFireCannon[0].end();

		vector<FIRECANNON>::iterator _idx1 = _vFireCannon[1].begin();
		vector<FIRECANNON>::iterator _end1 = _vFireCannon[1].end();

		for (_idx; _idx != _end; ++_idx)
		{
			if (!_idx->isFire) continue;

			if (_idx == _vFireCannon[0].begin())
			{
				_idx->fireCannonImage[0]->frameRender(getMemDC(), _idx->rc.left, _idx->rc.top, index[0], 0);
			}
			if (_idx == _vFireCannon[0].begin() + 1)
			{
				_idx->fireCannonImage[1]->frameRender(getMemDC(), _idx->rc.left, _idx->rc.top, index[1], 0);
			}
			if (_idx == _vFireCannon[0].begin() + 2)
			{
				_idx->fireCannonImage[1]->frameRender(getMemDC(), _idx->rc.left, _idx->rc.top, index[2], 0);
			}
			if (_idx == _vFireCannon[0].begin() + 3)
			{
				_idx->fireCannonImage[1]->frameRender(getMemDC(), _idx->rc.left, _idx->rc.top, index[3], 0);
			}
			if (_idx == _vFireCannon[0].begin() + 4)
			{
				_idx->fireCannonImage[1]->frameRender(getMemDC(), _idx->rc.left, _idx->rc.top, index[4], 0);
			}
		}

		for (_idx1; _idx1 != _end1; ++_idx1)
		{
			if (!_idx1->isFire) continue;

			if (_idx1 == _vFireCannon[1].begin())
			{
				_idx1->fireCannonImage[0]->frameRender(getMemDC(), _idx1->rc.left, _idx1->rc.top, index[0], 0);
			}
			if (_idx1 == _vFireCannon[1].begin() + 1)
			{
				_idx1->fireCannonImage[1]->frameRender(getMemDC(), _idx1->rc.left, _idx1->rc.top, index[1], 0);
			}
			if (_idx1 == _vFireCannon[1].begin() + 2)
			{
				_idx1->fireCannonImage[1]->frameRender(getMemDC(), _idx1->rc.left, _idx1->rc.top, index[2], 0);
			}
			if (_idx1 == _vFireCannon[1].begin() + 3)
			{
				_idx1->fireCannonImage[1]->frameRender(getMemDC(), _idx1->rc.left, _idx1->rc.top, index[3], 0);
			}
			if (_idx1 == _vFireCannon[1].begin() + 4)
			{
				_idx1->fireCannonImage[1]->frameRender(getMemDC(), _idx1->rc.left, _idx1->rc.top, index[4], 0);
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

		if (_idx == _vFireCannon[0].begin())
		{
			_idx->isFire = true;
			_idx->x = _idx->fireX = x + _idx->fireCannonImage[1]->getFrameWidth() * 4 - 100.f;
			_idx->y = _idx->fireY = y - 130.f;
			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[0]->getFrameWidth(), _idx->fireCannonImage[0]->getFrameHeight());
			_idx->speed = speed;
			_idx->angle = angle;
		}
		else if(_idx == _vFireCannon[0].begin() + 1)
		{
			_idx->isFire = true;
			_idx->x = _idx->fireX = x + _idx->fireCannonImage[1]->getFrameWidth() * 3 - 60.f;
			_idx->y = _idx->fireY = y - 40.f;
			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());
			_idx->speed = speed;
			_idx->angle = angle;
		}
		else if (_idx == _vFireCannon[0].begin() + 2)
		{
			_idx->isFire = true;
			_idx->x = _idx->fireX = x + _idx->fireCannonImage[1]->getFrameWidth() * 2 - 40.f;
			_idx->y = _idx->fireY = y - 35.f;
			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());
			_idx->speed = speed;
			_idx->angle = angle;
		}
		else if (_idx == _vFireCannon[0].begin() + 3)
		{
			_idx->isFire = true;
			_idx->x = _idx->fireX = x + _idx->fireCannonImage[1]->getFrameWidth() - 20.f;
			_idx->y = _idx->fireY = y - 25.f;
			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());
			_idx->speed = speed;
			_idx->angle = angle;
		}
		else if (_idx == _vFireCannon[0].begin() + 4)
		{
			_idx->isFire = true;
			_idx->x = _idx->fireX = x;
			_idx->y = _idx->fireY = y - 15.f;
			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());
			_idx->speed = speed;
			_idx->angle = angle;
		}

		break;
	}
}

void FireCannon::leftFireMove()
{
	count++;
	if (count % 10 == 0)
	{
		
		index[0]++;
		index[1]++;
		index[2]++;
		index[3]++;
		index[4]++;
		if (index[0] > 3)
		{
			index[0] = 2;
		}
		if (index[1] > 17)
		{
			index[1] = 0;
		}
		if (index[2] > 17)
		{
			index[2] = 0;
		}
		if (index[3] > 17)
		{
			index[3] = 0;
		}
		if (index[4] > 17)
		{
			index[4] = 0;
		}
	}
	vector<FIRECANNON>::iterator _idx = _vFireCannon[0].begin();
	vector<FIRECANNON>::iterator _end = _vFireCannon[0].end();

	for (_idx; _idx != _end; ++_idx)
	{
		if (!_idx->isFire) continue;

		if (_idx == _vFireCannon[0].begin())
		{
			_idx->gravity += 0.55f;
			_idx->angle -= 0.035f;
			_idx->x += cosf(_idx->angle) * _idx->speed;
			_idx->y += -sinf(_idx->angle) * _idx->speed + _idx->gravity;

			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[0]->getFrameWidth(), _idx->fireCannonImage[0]->getFrameHeight());

			float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx->isFire = false;
					_idx->gravity = 0.f;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx->isFire = false;
				_idx->gravity = 0.f;
			}
		}
		else if (_idx == _vFireCannon[0].begin() + 1)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx - 1;

			float angle = GetAngle(_idx->x, _idx->y, _prevIdx->x, _prevIdx->y);

			_idx->gravity += 0.53f;

			_idx->x += cosf(angle) * _idx->speed;
			_idx->y += -sinf(angle) * _idx->speed + _idx->gravity;

			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx->isFire = false;
					_idx->gravity = 0.f;
					index[1] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx->isFire = false;
				_idx->gravity = 0.f;
				index[1] = 0;
			}
		}
		else if (_idx == _vFireCannon[0].begin() + 2)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx - 1;

			float angle = GetAngle(_idx->x, _idx->y, _prevIdx->x, _prevIdx->y);

			_idx->gravity += 0.51f;

			_idx->x += cosf(angle) * _idx->speed;
			_idx->y += -sinf(angle) * _idx->speed + _idx->gravity;

			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx->isFire = false;
					_idx->gravity = 0.f;
					index[2] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx->isFire = false;
				_idx->gravity = 0.f;
				index[2] = 0;
			}
		}
		else if (_idx == _vFireCannon[0].begin() + 3)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx - 1;

			float angle = GetAngle(_idx->x, _idx->y, _prevIdx->x, _prevIdx->y);

			_idx->gravity += 0.49f;

			_idx->x += cosf(angle) * _idx->speed;
			_idx->y += -sinf(angle) * _idx->speed + _idx->gravity;

			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx->isFire = false;
					_idx->gravity = 0.f;
					index[3] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx->isFire = false;
				_idx->gravity = 0.f;
				index[3] = 0;
			}
		}
		else if (_idx == _vFireCannon[0].begin() + 4)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx - 1;

			float angle = GetAngle(_idx->x, _idx->y, _prevIdx->x, _prevIdx->y);

			_idx->gravity += 0.47f;

			_idx->x += cosf(angle) * _idx->speed;
			_idx->y += -sinf(angle) * _idx->speed + _idx->gravity;

			_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->fireCannonImage[1]->getFrameWidth(), _idx->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx->isFire = false;
					_idx->gravity = 0.f;
					index[4] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx->isFire = false;
				_idx->gravity = 0.f;
				index[4] = 0;
			}
		}
	}
}

void FireCannon::rightFire(float x, float y, float angle, float speed)
{
	vector<FIRECANNON>::iterator _idx1 = _vFireCannon[1].begin();
	vector<FIRECANNON>::iterator _end1 = _vFireCannon[1].end();

	for (_idx1; _idx1 != _end1; ++_idx1)
	{
		if (_idx1->isFire) continue;

		if (_idx1 == _vFireCannon[1].begin())
		{
			_idx1->isFire = true;
			_idx1->x = _idx1->fireX = x + _idx1->fireCannonImage[1]->getFrameWidth() * 4;
			_idx1->y = _idx1->fireY = y - 20.f;
			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[0]->getFrameWidth(), _idx1->fireCannonImage[0]->getFrameHeight());
			_idx1->speed = speed;
			_idx1->angle = angle;
		}
		else if (_idx1 == _vFireCannon[1].begin() + 1)
		{
			_idx1->isFire = true;
			_idx1->x = _idx1->fireX = x + _idx1->fireCannonImage[1]->getFrameWidth() * 3;
			_idx1->y = _idx1->fireY = y - 15.f;
			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());
			_idx1->speed = speed;
			_idx1->angle = angle;
		}
		else if (_idx1 == _vFireCannon[1].begin() + 2)
		{
			_idx1->isFire = true;
			_idx1->x = _idx1->fireX = x + _idx1->fireCannonImage[1]->getFrameWidth() * 2;
			_idx1->y = _idx1->fireY = y - 10.f;
			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());
			_idx1->speed = speed;
			_idx1->angle = angle;
		}
		else if (_idx1 == _vFireCannon[1].begin() + 3)
		{
			_idx1->isFire = true;
			_idx1->x = _idx1->fireX = x + _idx1->fireCannonImage[1]->getFrameWidth();
			_idx1->y = _idx1->fireY = y - 5.f;
			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());
			_idx1->speed = speed;
			_idx1->angle = angle;
		}
		else if (_idx1 == _vFireCannon[1].begin() + 4)
		{
			_idx1->isFire = true;
			_idx1->x = _idx1->fireX = x;
			_idx1->y = _idx1->fireY = y;
			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());
			_idx1->speed = speed;
			_idx1->angle = angle;
		}

		break;
	}
}

void FireCannon::rightFireMove()
{
	count++;
	if (count % 10 == 0)
	{

		index[0]++;
		index[1]++;
		index[2]++;
		index[3]++;
		index[4]++;
		if (index[0] > 3)
		{
			index[0] = 2;
		}
		if (index[1] > 17)
		{
			index[1] = 0;
		}
		if (index[2] > 17)
		{
			index[2] = 0;
		}
		if (index[3] > 17)
		{
			index[3] = 0;
		}
		if (index[4] > 17)
		{
			index[4] = 0;
		}
	}
	vector<FIRECANNON>::iterator _idx1 = _vFireCannon[1].begin();
	vector<FIRECANNON>::iterator _end1 = _vFireCannon[1].end();

	for (_idx1; _idx1 != _end1; ++_idx1)
	{
		if (!_idx1->isFire) continue;

		if (_idx1 == _vFireCannon[1].begin())
		{
			_idx1->gravity += 0.45f;
			_idx1->angle -= 0.045f;
			//발사 당시의 플레이어 위치를 기억해 각도를 계속 계산한다.
			float _angle = GetAngle(_idx1->x, _idx1->y, _x, _y);
			//280도가 되었을 경우 발사 당시의 플레이어 위치로 각도 보정
			if (_angle <= PI / 180 * 280)
			{
				_idx1->angle = PI / 180 * 280;
				_idx1->gravity = 0.25f;
			}
			_idx1->x += cosf(_idx1->angle) * _idx1->speed;
			_idx1->y += -sinf(_idx1->angle) * _idx1->speed + _idx1->gravity;

			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[0]->getFrameWidth(), _idx1->fireCannonImage[0]->getFrameHeight());

			float dist = GetDistance(_idx1->fireX, _idx1->fireY, _idx1->x, _idx1->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx1->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx1->isFire = false;
					_idx1->gravity = 0.f;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx1->isFire = false;
				_idx1->gravity = 0.f;
			}
		}
		else if (_idx1 == _vFireCannon[1].begin() + 1)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx1 - 1;

			float angle = GetAngle(_idx1->x, _idx1->y, _prevIdx->x, _prevIdx->y);

			_idx1->gravity += 0.04f;

			_idx1->x += cosf(angle) * _idx1->speed;
			_idx1->y += -sinf(angle) * _idx1->speed + _idx1->gravity;

			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx1->fireX, _idx1->fireY, _idx1->x, _idx1->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx1->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx1->isFire = false;
					_idx1->gravity = 0.f;
					index[1] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx1->isFire = false;
				_idx1->gravity = 0.f;
				index[1] = 0;
			}
		}
		else if (_idx1 == _vFireCannon[1].begin() + 2)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx1 - 1;

			float angle = GetAngle(_idx1->x, _idx1->y, _prevIdx->x, _prevIdx->y);

			_idx1->gravity += 0.038f;

			_idx1->x += cosf(angle) * _idx1->speed;
			_idx1->y += -sinf(angle) * _idx1->speed + _idx1->gravity;

			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx1->fireX, _idx1->fireY, _idx1->x, _idx1->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx1->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx1->isFire = false;
					_idx1->gravity = 0.f;
					index[2] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx1->isFire = false;
				_idx1->gravity = 0.f;
				index[2] = 0;
			}
		}
		else if (_idx1 == _vFireCannon[1].begin() + 3)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx1 - 1;

			float angle = GetAngle(_idx1->x, _idx1->y, _prevIdx->x, _prevIdx->y);

			_idx1->gravity += 0.036f;

			_idx1->x += cosf(angle) * _idx1->speed;
			_idx1->y += -sinf(angle) * _idx1->speed + _idx1->gravity;

			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx1->fireX, _idx1->fireY, _idx1->x, _idx1->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx1->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx1->isFire = false;
					_idx1->gravity = 0.f;
					index[3] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx1->isFire = false;
				_idx1->gravity = 0.f;
				index[3] = 0;
			}
		}
		else if (_idx1 == _vFireCannon[1].begin() + 4)
		{
			vector<FIRECANNON>::iterator _prevIdx = _idx1 - 1;

			float angle = GetAngle(_idx1->x, _idx1->y, _prevIdx->x, _prevIdx->y);

			_idx1->gravity += 0.034f;

			_idx1->x += cosf(angle) * _idx1->speed;
			_idx1->y += -sinf(angle) * _idx1->speed + _idx1->gravity;

			_idx1->rc = RectMakeCenter(_idx1->x, _idx1->y, _idx1->fireCannonImage[1]->getFrameWidth(), _idx1->fireCannonImage[1]->getFrameHeight());

			float dist = GetDistance(_idx1->fireX, _idx1->fireY, _idx1->x, _idx1->y);

			//다리 충돌 체크 임시 렉트
			RECT rc;
			//다리와 충돌 체크
			for (int i = 0; i < 22; i++)
			{
				if (IntersectRect(&rc, &_idx1->rc, &_bridgeImg[i]->boudingBox()))
				{
					//값 초기화
					_idx1->isFire = false;
					_idx1->gravity = 0.f;
					index[4] = 0;
				}
			}

			//사거리 멀어지면 화염포 사라짐
			if (_range < dist)
			{
				_idx1->isFire = false;
				_idx1->gravity = 0.f;
				index[4] = 0;
			}
		}
	}
}
