#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(string name) : GameObject(name)
{
	_name = name;				// Ŭ���� �̸� ���� ����
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


void Bullet::Update()
{
	this->move(); 
}
//if (_angle == 0 || _angle == PI)
//{
//	_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, 0, 0);
//}
//else if (_angle == PI / 2 || _angle == PI + PI / 2)
//{
//	_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, 1, 0);
//}
void Bullet::Render()
{
	//RECT playerRC = CAMERA->Relative(_rc);
	if (_isFrameImg)//������ �̹�����?

	{
		
		for (int i = 0; i < _vBullet.size(); i++)
		{

			RECT bulletRc = CAMERA->Relative(_vBullet[i].rc);
			_angle = _vBullet[i].angle;//�⺻�Ѿ�

			

				if (_angle >= 0 && _angle <= (PI / 2) )
				{
					_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, _angle / 5.29f * (180 / PI), 3);
				}
				//Ȳ�ݺ��� 5.29f
				else if (_angle >= (PI / 2)/* * 180/ PI */ && _angle <= PI /** (180 / PI)*/) //���� ���Ŀ��� angle���� 180���ʿ䰡���� 
																							 //else if
				{
					_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)((_angle / 5.29f) *(180 / PI)) - 17, 2);//�������ؾȵ� 
																																			   //100�� �ϋ��� 5.29������ 18 �����ε� 17������ 1���δ콺���;��Ѵ� 
																																			   //180���� 34������ ������ 17������ 17 �̳��;��Ѵ� 
				}
				else if (_angle >= -(PI) && _angle <= -(PI / 2))
				{
					_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)(((_angle * -1) / 5.29f) * (180 / PI)) - 17, 1);
				}
				else if (_angle <= 0 && _angle >= -(PI / 2))
				{
					_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)((_angle * -1) / 5.29f * (180 / PI)  + 3), 0);
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
		if (_vBullet[i].isFire) continue;

		_vBullet[i].isFire = true;
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getWidth(), _vBullet[i].bulletImage->getHeight());
		_vBullet[i].speed = speed;
		_vBullet[i].angle = angle;
		//_vBullet[i].angle1 = angle;
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
	_name = name; //Ŭ���� �̸����� 
}

Boom::~Boom()
{
}

HRESULT Boom::Init(const char * imageName, int width, int height , int bulletMax,float range)
{
	
	_bulletMax = bulletMax; 
	_range = range; 
	for (int i = 0; i < bulletMax; i++)
	{
	
		tagBoom boom;

		boom.angle = 0.0f;
		boom.bulletImage = new image;
		boom.bulletImage->init(imageName,width,height,16,2,true,RGB(255,0,255));
		boom.gravity = 0.0f;
		boom.isFire = false;
		boom.speed = 0.0f; 
		boom.x = 0.0f;
		boom.y = 0.0f;

		_vBoom.push_back(boom);
	}
	for (int i = 0; i < 10; i++)
	{
		_frameCount[i] = 0;
		_frameIndex[i] = 0;
	}
	
	_PlayerBoomMax = 10; 

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
	

	for (int i = 0; i < _bulletMax; i++)
	{ 
		
		// ��ź�� �߻� ������ ���� 
		// frameCount ���� ��Ų��.
		_frameCount[i]++;
		if (_frameCount[i] % 2 == 0)
		{
			// frameCount�� ���� �ʿ� ����
			// frameIndex�� ���� �����ش�.
			_frameIndex[i]++; 
			if (_frameIndex[i] > 15) {
				_frameIndex[i] = 0;
				//_vBoom[i].bulletImage->setFrameY(1);
			}
		}	
		// ������ ������ �ε����� �̹����� ���� �����ش�.
		_vBoom[i].bulletImage->setFrameX(_frameIndex[i]);
	}

}

void Boom::Render()
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		RECT bulletRc = CAMERA->Relative(_vBoom[i].rc);
		_vBoom[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top);
	}
}
void Boom::fire(float x, float y, float angle, float gravity ,float speed)
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		if (_vBoom[i].isFire)continue;
		_vBoom[i].isFire = true; 
		_vBoom[i].x = _vBoom[i].fireX= x; 
		_vBoom[i].y = _vBoom[i].fireY = y;
		_vBoom[i].rc = RectMakeCenter(_vBoom[i].x, _vBoom[i].y,
			_vBoom[i].bulletImage->getWidth(), _vBoom[i].bulletImage->getHeight());
		_vBoom[i].speed = speed; 
		_vBoom[i].angle = angle; 
		_vBoom[i].gravity = gravity; 
		_PlayerBoomMax -= 1;  
		break;
	}
}

void Boom::move()
{
	for (int i = 0; i < _vBoom.size(); i++)
	{
		if (!_vBoom[i].isFire)continue;
		_vBoom[i].gravity += 0.5f;
		_vBoom[i].x += cosf(_vBoom[i].angle) * _vBoom[i].speed  ; 
		_vBoom[i].y += -sinf(_vBoom[i].angle) * _vBoom[i].speed + _vBoom[i].gravity;

		_vBoom[i].rc = RectMakeCenter(_vBoom[i].x, _vBoom[i].y,
			_vBoom[i].bulletImage->getWidth(), _vBoom[i].bulletImage->getHeight());

		float distance = GetDistance(_vBoom[i].fireX, _vBoom[i].fireY,
			_vBoom[i].x, _vBoom[i].y);

		if (_range < distance)
		{
			_vBoom[i].isFire = false;
		}
	}
}



//#####################################

Bullet1::Bullet1(string name) : GameObject(name)
{
	_name = name;				// Ŭ���� �̸� ���� ����
}


Bullet1::~Bullet1()
{
}

HRESULT Bullet1::Init(const char * imageName, int width, int height, int bulletMax, float range, bool frameimage)
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
			bullet.bulletImage->init(imageName, width, height, 2, 1, true, RGB(255, 0, 255));
		}
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}
	_angle = 0.0f;


	return S_OK;
}


void Bullet1::Release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}


void Bullet1::Update()
{
	this->move();
}

void Bullet1::Render()
{
	//RECT playerRC = CAMERA->Relative(_rc);
	if (_isFrameImg)//������ �̹�����?

	{

		for (int i = 0; i < _vBullet.size(); i++)
		{

			RECT bulletRc = CAMERA->Relative(_vBullet[i].rc);
			_angle = _vBullet[i].angle;//�⺻�Ѿ�



			if (_angle == 0 || _angle == PI)
			{
				_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, 0, 0);
			}
			else if (_angle == PI / 2 || _angle == PI + PI / 2)
			{
				_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, 1, 0);
			}



			//((Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�"))->SetWeapon(((Player*)OBJECTMANAGER->FindObject(ObjectType::Enum::PLAYER, "�÷��̾�"))->GetWeapon());



		//_angle =_vBullet[i].angle;//�غ���Ű��Ѿ� 
		//_angle1 = _vBullet[i].angle1;//�⺻�Ѿ�  
	 //   if (_angle1 == 0 || _angle1 == PI)
		//{
		//	_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, 0, 0);
		//}
		//else if (_angle1 == PI / 2 || _angle1 == PI + PI / 2)
		//{
		//	_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, 1, 0);
		//}



		//�غ�=======================================================�غ�=========================================
		//if (!_vBullet[i].isFire)continue;
		//_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top);	


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
void Bullet1::fire(float x, float y, float angle, float speed)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].isFire) continue;

		_vBullet[i].isFire = true;
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getWidth(), _vBullet[i].bulletImage->getHeight());
		_vBullet[i].speed = speed;
		_vBullet[i].angle = angle;
		//_vBullet[i].angle1 = angle;
		break;
	}
}

void Bullet1::move()
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

