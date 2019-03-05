#include "stdafx.h"
#include "Bubble.h"

Bubble::Bubble(string name) : GameObject(name)
{
	_name = name;
}

Bubble::~Bubble()
{
}

HRESULT Bubble::Init(const char * imageName, int width, int height, int bubbleMax, float range)
{
	_bubbleMax = bubbleMax;
	_range = range;

	for (int i = 0; i < bubbleMax; i++)
	{
		BUBBLE bubble;

		ZeroMemory(&bubble, sizeof(BUBBLE));
		bubble.bubbleImage = new image;
		bubble.bubbleImage->init(imageName, width, height, true, RGB(255, 0, 255));
		bubble.isFire = false;

		_vBubble.push_back(bubble);
	}

	return S_OK;
}

void Bubble::Release()
{
	for (int i = 0; i < _vBubble.size(); i++)
	{
		_vBubble[i].bubbleImage->release();
		SAFE_DELETE(_vBubble[i].bubbleImage);
	}
}

void Bubble::Update()
{
	this->move();
}

void Bubble::Render()
{
	for (int i = 0; i < _vBubble.size(); i++)
	{
		if (!_vBubble[i].isFire) continue;

		_vBubble[i].bubbleImage->render(getMemDC(), _vBubble[i].rc.left, _vBubble[i].rc.top);
	}
}

void Bubble::fire(float x, float y, float angle, float speed)
{
	for (int i = 0; i < _vBubble.size(); i++)
	{
		if (_vBubble[i].isFire) continue;

		_vBubble[i].isFire = true;
		_vBubble[i].x = _vBubble[i].fireX = x;
		_vBubble[i].y = _vBubble[i].fireY = y;
		_vBubble[i].rc = RectMakeCenter(_vBubble[i].x, _vBubble[i].y
										, _vBubble[i].bubbleImage->getWidth()
										, _vBubble[i].bubbleImage->getHeight());
		_vBubble[i].speed = speed;
		_vBubble[i].angle = angle;
		break;
	}
}

void Bubble::move()
{
	for (int i = 0; i < _vBubble.size(); i++)
	{
		if (!_vBubble[i].isFire)continue;

		_vBubble[i].x += cosf(_vBubble[i].angle) * _vBubble[i].speed;
		_vBubble[i].y += -sinf(_vBubble[i].angle) * _vBubble[i].speed;

		_vBubble[i].rc = RectMakeCenter(_vBubble[i].x, _vBubble[i].y
										, _vBubble[i].bubbleImage->getWidth()
										, _vBubble[i].bubbleImage->getHeight());
		float dist = GetDistance(_vBubble[i].fireX, _vBubble[i].fireY
								, _vBubble[i].x, _vBubble[i].y);

		//사거리 멀어지면 거품 사라짐
		if (_range < dist)
		{
			_vBubble[i].isFire = false;
		}
	}
}
