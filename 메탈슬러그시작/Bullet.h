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
	float gravity; 
	float radius;
	bool isFire;

	int att;                             //�������� ����ִ� ����ü�� ���ݷ� 
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

	virtual HRESULT Init( float range);
	//virtual HRESULT Init(const char * imageName, int width, int height, int bulletMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetisFire(int index, bool isfire) { _vBullet[index].isFire = isfire; }

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

	//void SetisFire(int index, bool isfire) { _vBoom[index].isFire = isfire;  }
	
	void SetisFire(int index, bool isfire) { _vBoom[index].isFire = isfire; }
	int GetPlayerBoomMax() { return _PlayerBoomMax; }//�÷��̾� ��ź�ִ밹��
	void SetPlayerBoomMax(int PlayerBoomMax) { _PlayerBoomMax = PlayerBoomMax; }
	vector<tagBoom> getVBoom() { return _vBoom; }
	vector<tagBoom>::iterator getViBoom() { return _viBoom; }

	
//	void SetisFire(int i, bool fire) { _vBoom[i].isFire = fire; }
};




// ########################�⺻�Ѿ˻��� 
class Bullet1 :public GameObject  
{
private:
	//const char* _imageName;
	//float _range;
	//int _bulletMax;
	bool _isFrameImg;

	float _range; //�Ѿ˰Ÿ� 
	
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _angle;
	//	float _angle1; 

	///	int _frameX;
	//int _frameY;

public:
	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed );
	void move();

	Bullet1(string name);
	~Bullet1();

	virtual HRESULT Init(float range);
	//virtual HRESULT Init(const char * imageName, int width, int height, int bulletMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetisFire(int index, bool isfire) { _vBullet[index].isFire = isfire; }

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};






//###################################################





