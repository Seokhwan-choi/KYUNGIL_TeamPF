#pragma once
#include "GameObject.h"

//�Ѿ˱���ü 
struct tagBullet
{
	image*bulletImage;
	RECT rc; 
	float x, y;
	float fireX, fireY; 
	float speed; 
	float angle; 
	//float angle1; 
	float gravity; 
	float radius;
	bool isFire;
	//int count;
};



class Bullet :public GameObject
{
private:
	//const char* _imageName;
	//float _range;
	//int _bulletMax;
	bool _isFrameImg;

	float _range; //�Ѿ˰Ÿ� 
	int _bulletMax; //�Ѿ˰��� 
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet; 

	float _angle;
//	float _angle1; 

///	int _frameX;
//int _frameY;

public:
	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed);
	void move();

	Bullet(string name);
	~Bullet();

	virtual HRESULT Init(const char * imageName, int width, int height, int bulletMax, float range,bool frameimage);
	//virtual HRESULT Init(const char * imageName, int width, int height, int bulletMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};

struct tagBoom
{
	image*bulletImage;//��ź�̹��� 
	RECT rc; //��ź ��Ʈ 
	float x, y;//��ź �������� 
	float fireX, fireY;//��ź ������ 
	float speed;//��ź ���ǵ�
	float angle;//��ź�� �ޱ� 
	float gravity;//��ź�� �߷� 
	bool isFire;//��ź ������? 

};
class Boom : public GameObject
{
private:
	vector<tagBoom> _vBoom;
	vector<tagBoom>::iterator _viBoom;
	int _bulletMax;
	float _range; //��ź �Ÿ� 
				  //((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "�÷��̾�"));


	
	int _frameCount[10]; 
	int _frameIndex[10];
	int _PlayerBoomMax; //�÷��̾� ��ź���� �ִ�� 10���̴� 

public:
	void fire(float x, float y, float angle ,float gravity,float speed);
	void move(); 

	Boom(string name);
	~Boom();

	virtual HRESULT Init(const char* imageName, int width, int height , int bulletMax,float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	int GetPlayerBoomMax() { return _PlayerBoomMax; }//�÷��̾� ��ź�ִ밹��
	void SetPlayerBoomMax(int PlayerBoomMax) { _PlayerBoomMax = PlayerBoomMax; }
	vector<tagBoom> getVBoom() { return _vBoom; }
	vector<tagBoom>::iterator getViBoom() { return _viBoom; }

};





class Bullet1 :public GameObject
{
private:
	//const char* _imageName;
	//float _range;
	//int _bulletMax;
	bool _isFrameImg;

	float _range; //�Ѿ˰Ÿ� 
	int _bulletMax; //�Ѿ˰��� 
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _angle;
	//	float _angle1; 

	///	int _frameX;
	//int _frameY;

public:
	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed);
	void move();

	Bullet1(string name);
	~Bullet1();

	virtual HRESULT Init(const char * imageName, int width, int height, int bulletMax, float range, bool frameimage);
	//virtual HRESULT Init(const char * imageName, int width, int height, int bulletMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};




//
//
//
//if (_isFrameImg)//������ �̹�����?
//
//{
//
//	for (int i = 0; i < _vBullet.size(); i++)
//	{
//
//		RECT bulletRc = CAMERA->Relative(_vBullet[i].rc);
//		_angle = _vBullet[i].angle;//�⺻�Ѿ�
//
//
//
//		if (_angle >= 0 && _angle <= (PI / 2))
//		{
//			_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, _angle / 5.29f * (180 / PI), 3);
//		}
//		//Ȳ�ݺ��� 5.29f
//		else if (_angle >= (PI / 2)/* * 180/ PI */ && _angle <= PI /** (180 / PI)*/) //���� ���Ŀ��� angle���� 180���ʿ䰡���� 
//																					 //else if
//		{
//			_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)((_angle / 5.29f) *(180 / PI)) - 17, 2);//�������ؾȵ� 
//																																	   //100�� �ϋ��� 5.29������ 18 �����ε� 17������ 1���δ콺���;��Ѵ� 
//																																	   //180���� 34������ ������ 17������ 17 �̳��;��Ѵ� 
//		}
//		else if (_angle >= -(PI) && _angle <= -(PI / 2))
//		{
//			_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)(((_angle * -1) / 5.29f) * (180 / PI)) - 17, 1);
//		}
//		else if (_angle <= 0 && _angle >= -(PI / 2))
//		{
//			_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)((_angle * -1) / 5.29f * (180 / PI) + 3), 0);
//		}
//
//	}
//}


//void Boom::Update()
//{
//	this->move();
//
//
//	for (int i = 0; i < _bulletMax; i++)
//	{
//		_frameCount[i]++;
//		if (_frameCount[i] % 10 == 0)
//		{
//			_frameIndex[i]++;
//
//			if (_frameIndex[i] > 15)
//			{
//				_frameIndex[i] = 0;
//			}
//			_vBoom[i].bulletImage->setFrameY(_frameIndex[i]);
//		}
//	}
//
//}
