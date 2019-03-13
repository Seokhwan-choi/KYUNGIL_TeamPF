#pragma once
#include "GameObject.h"

//총알구조체 
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

	float _range; //총알거리 
	int _bulletMax; //총알갯수 
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet; 

	float _angle;
//	float _angle1; 

///	int _frameX;
//int _frameY;

public:
	//총알발사
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
	image*bulletImage;//폭탄이미지 
	RECT rc; //폭탄 렉트 
	float x, y;//폭탄 시작지점 
	float fireX, fireY;//폭탄 움직임 
	float speed;//폭탄 스피드
	float angle;//폭탄의 앵글 
	float gravity;//폭탄의 중력 
	bool isFire;//폭탄 던졋냐? 

};
class Boom : public GameObject
{
private:
	vector<tagBoom> _vBoom;
	vector<tagBoom>::iterator _viBoom;
	int _bulletMax;
	float _range; //폭탄 거리 
				  //((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "플레이어"));


	
	int _frameCount[10]; 
	int _frameIndex[10];
	int _PlayerBoomMax; //플레이어 폭탄개수 최대는 10개이다 

public:
	void fire(float x, float y, float angle ,float gravity,float speed);
	void move(); 

	Boom(string name);
	~Boom();

	virtual HRESULT Init(const char* imageName, int width, int height , int bulletMax,float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	int GetPlayerBoomMax() { return _PlayerBoomMax; }//플레이어 폭탄최대갯수
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

	float _range; //총알거리 
	int _bulletMax; //총알갯수 
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _angle;
	//	float _angle1; 

	///	int _frameX;
	//int _frameY;

public:
	//총알발사
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
//if (_isFrameImg)//프레임 이미지냐?
//
//{
//
//	for (int i = 0; i < _vBullet.size(); i++)
//	{
//
//		RECT bulletRc = CAMERA->Relative(_vBullet[i].rc);
//		_angle = _vBullet[i].angle;//기본총알
//
//
//
//		if (_angle >= 0 && _angle <= (PI / 2))
//		{
//			_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, _angle / 5.29f * (180 / PI), 3);
//		}
//		//황금비율 5.29f
//		else if (_angle >= (PI / 2)/* * 180/ PI */ && _angle <= PI /** (180 / PI)*/) //구지 계산식에서 angle옆에 180쓸필요가없다 
//																					 //else if
//		{
//			_vBullet[i].bulletImage->frameRender(getMemDC(), bulletRc.left, bulletRc.top, (int)((_angle / 5.29f) *(180 / PI)) - 17, 2);//존나이해안됨 
//																																	   //100도 일떄는 5.29나누면 18 정도인데 17을빼면 1번인댁스나와야한다 
//																																	   //180도는 34정도가 나오고 17을뺴면 17 이나와야한다 
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
