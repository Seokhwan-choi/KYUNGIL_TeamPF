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

HRESULT Bubble::Init2(const char * imageName, int width, int height, int FrameX, int FrameY, int bubbleMax, float range)
{
	_bubbleMax = bubbleMax;
	_range = range;

	for (int i = 0; i < bubbleMax; i++)
	{
		BUBBLE bubble;

		ZeroMemory(&bubble, sizeof(BUBBLE));
		bubble.bubbleImage = new image;
		//bubble.bubbleImage->init(imageName, width, height, true, RGB(255, 0, 255));
		bubble.bubbleImage->init(imageName, width, height, FrameX, FrameY, true, RGB(255, 0, 255));
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

		_vBubble[i].bubbleImage->frameRender(getMemDC(), _vBubble[i].rc.left + 30 - CAMERA->GetCamera().left, _vBubble[i].rc.top - CAMERA->GetCamera().top,_vBubble[i].index,1);
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

		if (!_vBubble[i].isDown)
		{
			_vBubble[i].gravity -= 0.02f;
			_vBubble[i].upDownCount++;
			if (_vBubble[i].upDownCount >= 40)
			{
				_vBubble[i].gravity = 0.f;
				_vBubble[i].isDown = true;
			}
		}
		if (_vBubble[i].isDown)
		{
			_vBubble[i].gravity += 0.02f;
			_vBubble[i].upDownCount--;
			if (_vBubble[i].upDownCount <= 0)
			{
				_vBubble[i].gravity = 0.f;
				_vBubble[i].isDown = false;
			}
		}

		_vBubble[i].x += cosf(_vBubble[i].angle) * _vBubble[i].speed;
		_vBubble[i].y += -sinf(_vBubble[i].angle) * _vBubble[i].speed + _vBubble[i].gravity;

		_vBubble[i].rc = RectMakeCenter(_vBubble[i].x, _vBubble[i].y
										, _vBubble[i].bubbleImage->getWidth()
										, _vBubble[i].bubbleImage->getHeight());
		float dist = GetDistance(_vBubble[i].fireX, _vBubble[i].fireY
								, _vBubble[i].x, _vBubble[i].y);

		//사거리 멀어지면 거품 사라짐
		if (_range < dist)
		{
			_vBubble[i].isFire = false;
			_vBubble[i].gravity = 0.f;
			_vBubble[i].upDownCount = 0;
			_vBubble[i].isDown = false;
		}
	}
}

void Bubble::move1()
{
	for (int i = 0; i < _vBubble.size(); i++)
	{
		_vBubble[i].upDownCount = 0;
		if (!_vBubble[i].isFire)continue;

		//if (!_vBubble[i].isDown)
		//{
		//	_vBubble[i].gravity -= 0.02f;
		//	_vBubble[i].upDownCount++;
		//	if (_vBubble[i].upDownCount >= 40)
		//	{
		//		_vBubble[i].gravity = 0.f;
		//		_vBubble[i].isDown = true;
		//	}
		//}
		
		_vBubble[i].x += cosf(_vBubble[i].angle) * _vBubble[i].speed;
		_vBubble[i].y += -sinf(_vBubble[i].angle) * _vBubble[i].speed + _vBubble[i].gravity;

		_vBubble[i].rc = RectMakeCenter(_vBubble[i].x, _vBubble[i].y
			, _vBubble[i].bubbleImage->getWidth()
			, _vBubble[i].bubbleImage->getHeight());

		float dist = GetDistance(_vBubble[i].fireX, _vBubble[i].fireY
			, _vBubble[i].x, _vBubble[i].y);

		if (dist >= 400.f)
		{
			_vBubble[i].speed = 0;
			_vBubble[i].isDown = true;
		}
		if (_vBubble[i].isDown == true)
		{
			_vBubble[i].gravity -= 0.02f;
			_vBubble[i].upDownCount++;
			if (_vBubble[i].upDownCount % 10 == 0)
			{
				_vBubble[i].gravity = 0.f;
				_vBubble[i].isDown = false;
			}
		}
		//사거리 멀어지면 거품 사라짐
		if (_range < dist)
		{
			_vBubble[i].isFire = false;
			_vBubble[i].gravity = 0.f;
			_vBubble[i].upDownCount = 0;
			_vBubble[i].isDown = false;
		}
	}
}

void Bubble::render()
{
	for (int i = 0; i < _vBubble.size(); i++)
	{
		if (_vBubble[i].isFire == true)
		{
			_vBubble[i].count++;
			if (_vBubble[i].count % 10 == 0)
			{
				_vBubble[i].index++;
				if (_vBubble[i].index > 7)
				{
					_vBubble[i].index = 0;
				}
			}
		}
	}
}
