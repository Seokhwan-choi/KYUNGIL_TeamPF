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

	//���Ϳ� �ֱ� ���� �ӽ� ����ü ����
	for (int i = 0; i < bombMax; i++)
	{
		//���Ϳ� �ֱ� ���� �ӽ� ����ü ����
		BOMB bomb;

		ZeroMemory(&bomb, sizeof(BOMB));
		bomb.bombImage = new image;
		bomb.bombImage->init(imageName, width, height, true, RGB(255, 0, 255));
		bomb.isFire = false;

		_vBomb.push_back(bomb);
	}

	//�ٸ� �̹��� �ʱ�ȭ
	for (int i = 0; i < 22; i++)
	{
		string idx = to_string(i + 1);
		string key = "�ٸ�" + idx;
	
		_bridgeImg[i] = IMAGEMANAGER->findImage(key);
	}

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

	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		for (int i = 0; i < 22; ++i) 
		{
			Rectangle(getMemDC(), _bridgeImg[i]->boudingBox());
		}
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

		//�߻� ����� �÷��̾� ��ġ�� ����� ������ ��� ����Ѵ�.
		float _angle = GetAngle(_idx->x, _idx->y, _x, _y);

		//270���� �Ǿ��� ��� �߻� ����� �÷��̾� ��ġ�� ���� ����
		if (_angle <= PI / 180 * 270)
		{
			_idx->angle = PI / 180 * 270;
			_idx->gravity = 0.f;
		}

		_idx->x += cosf(_idx->angle) * _idx->speed;
		_idx->y += -sinf(_idx->angle) * _idx->speed + _idx->gravity;

		_idx->rc = RectMakeCenter(_idx->x, _idx->y, _idx->bombImage->getWidth(), _idx->bombImage->getHeight());

		float dist = GetDistance(_idx->fireX, _idx->fireY, _idx->x, _idx->y);
		
		//�ٸ� �浹 üũ �ӽ� ��Ʈ
		RECT rc;
		//�ٸ��� �浹 üũ
		for (int i = 0; i < 22; i++)
		{
			if (IntersectRect(&rc, &_idx->rc, &_bridgeImg[i]->boudingBox()))
			{
				//�ӽ÷� ����
				_bridgeImg[i]->setX(-200);
				//_bridgeImg[i]->setX(1575 + (i * 175));
		
				//�� �ʱ�ȭ
				_idx->isFire = false;
				_idx->gravity = 0.f;
			}
		}

		//��Ÿ� �־����� ��ź �����
		if (_range < dist)
		{
			_idx->isFire = false;
			_idx->gravity = 0.f;
		}
	}
}
