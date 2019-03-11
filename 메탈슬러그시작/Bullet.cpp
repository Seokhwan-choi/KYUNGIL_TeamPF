#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(string name) : GameObject(name)
{
	_name = name;				// 클래스 이름 설정 해준
}


Bullet::~Bullet()
{
}

HRESULT Bullet::Init(const char * imageName, int width, int height, int bulletMax, float range, bool frameimage)
{
	_isFrameImg = frameimage; 
	_bulletMax = bulletMax;
	_range = range;
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;

		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		if (!_isFrameImg) {
			bullet.bulletImage->init(imageName, width, height, true, RGB(255, 0, 255));
		}
		else
		{
			bullet.bulletImage->init(imageName, width, height, 17, 4, true, RGB(255, 0, 255));
		}
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	_angle=0.0f;
	_angle1=0.0f;
	return S_OK;

}


void Bullet::Release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release(); 
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}
//if (DATA->getScore() < 10) {
//	_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore(), 0);
//}
////백자리
//if (DATA->getScore() >= 100 && DATA->getScore() < 1000) {
//	_scoreImg->frameRender(getMemDC(), 218, 34, (DATA->getScore() - DATA->getScore() % 100) / 100, 0);
//	_scoreImg->frameRender(getMemDC(), 243, 34, (DATA->getScore() / 10) % 10, 0);
//	_scoreImg->frameRender(getMemDC(), 268, 34, DATA->getScore() % 10, 0);

void Bullet::Update()
{
	this->move(); 
}

void Bullet::Render()
{
	//RECT playerRC = CAMERA->Relative(_rc);
	if (_isFrameImg)//프레임 이미지냐?
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			RECT bulletRc = CAMERA->Relative(_vBullet[i].rc);
			
			_angle =_vBullet[i].angle;

			//if (!_vBullet[i].isFire)continue;
			//_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top);	
			if (_angle >= 0 && _angle < (3.14f / 2) /**  180/PI*/ )
			{
				_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top,  _angle / 5.29f * (180 / PI),3);
			}
			//황금비율 5.29f
			else if (_angle> (PI / 2)/* * 180/ PI */ &&   _angle < PI /** (180 / PI)*/ ) //구지 계산식에서 angle옆에 180쓸필요가없다 
			//else if
			{
				_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)((_angle / 5.29f ) *(180 / PI) )- 17 , 2);//존나이해안됨 
				//100도 일떄는 5.29나누면 18 정도인데 17을빼면 1번인댁스나와야한다 
				//180도는 34정도가 나오고 17을뺴면 17 이나와야한다 
			}

		}
	}
	else
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			RECT bulletRc = CAMERA->Relative(_vBullet[i].rc);
			if (!_vBullet[i].isFire)continue;
			_vBullet[i].bulletImage->render(getMemDC(), bulletRc.left, bulletRc.top);
		}
	}
	

}
void Bullet::fire(float x, float y, float angle, float speed)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].isFire)continue;

		_vBullet[i].isFire = true;
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getWidth(), _vBullet[i].bulletImage->getHeight());
		_vBullet[i].speed = speed;
		_vBullet[i].angle = angle;
		break;
	}
}

void Bullet::move()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].isFire)continue;
	
		_vBullet[i].x += cosf(_vBullet[i].angle)*_vBullet[i].speed;
		_vBullet[i].y -= sinf(_vBullet[i].angle)*_vBullet[i].speed;

		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getWidth(),
			_vBullet[i].bulletImage->getHeight());

		float distance = GetDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);

		if (_range < distance)
		{
			_vBullet[i].isFire = false; 
		}
	}
}



Boom::Boom(string name)
	:GameObject(name)
{
	_name = name; //클래스 이름설정 
}

Boom::~Boom()
{
}

HRESULT Boom::Init(const char * imageName, int width, int height , int bulletMax)
{

	_bulletMax = bulletMax; 

	for (int i = 0; i < bulletMax; i++)
	{
		tagBoom boom;

		boom.angle = 0.0f;
		boom.bulletImage = new image;
		boom.bulletImage->init(imageName, width, height, true, RGB(255, 0, 255));
		boom.gravity = 0.0f;
		boom.isFire = false;
		boom.speed = 0.0f; 
		boom.x = 0.0f;
		boom.y = 0.0f; 

		_vBoom.push_back(boom);
	}
	return S_OK;
}

void Boom::Release()
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		_vBoom[i].bulletImage->release(); 
		SAFE_DELETE(_vBoom[i].bulletImage);
	}
}

void Boom::Update()
{
	this->move(); 

	//((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, ""));

}

void Boom::Render()
{
	for (int i = 0; i<_vBoom.size(); i++)
	{
		if (!_vBoom[i].isFire)continue;
			_vBoom[i].bulletImage->render(getMemDC(), _vBoom[i].rc.left, _vBoom[i].rc.top);
	}
}
void Boom::fire(float x, float y, float angle, float gravity ,float speed)
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		if (_vBoom[i].isFire)continue;

		_vBoom[i].isFire = true; 
		_vBoom[i].x = x; 
		_vBoom[i].y = y; 
		_vBoom[i].rc = RectMakeCenter(_vBoom[i].x, _vBoom[i].y,
			_vBoom[i].bulletImage->getWidth(), _vBoom[i].bulletImage->getHeight());
		_vBoom[i].speed = speed; 
		_vBoom[i].angle = angle; 
		_vBoom[i].gravity = gravity; 
		break;
	}
}

void Boom::move()
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		if (!_vBoom[i].isFire)continue;
		_vBoom[i].gravity += 0.5f;

		_vBoom[i].x += cosf(_vBoom[i].angle) * _vBoom[i].speed;
		_vBoom[i].y += -sinf(_vBoom[i].angle) * _vBoom[i].speed + _vBoom[i].gravity;

		_vBoom[i].rc = RectMakeCenter(_vBoom[i].x, _vBoom[i].y,
			_vBoom[i].bulletImage->getWidth(), _vBoom[i].bulletImage->getHeight());


	}
}