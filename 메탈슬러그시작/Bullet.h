#pragma once
#include "GameObject.h"

//ÃÑ¾Ë±¸Á¶Ã¼ 
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

	int att;                             //°ø¿ëÀ¸·Î µé°íÀÖ´Â ±¸Á¶Ã¼ÀÇ °ø°Ý·Â 
	//int count;
};



class Bullet :public GameObject
{
private:
	//const char* _imageName;
	//float _range;
	//int _bulletMax;
	bool _isFrameImg;

	float _range; //ÃÑ¾Ë°Å¸® 

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet; 

	float _angle;
//	float _angle1; 

///	int _frameX;
//int _frameY;

public:
	//ÃÑ¾Ë¹ß»ç
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
	image*bulletImage;//ÆøÅºÀÌ¹ÌÁö 
	RECT rc; //ÆøÅº ·ºÆ® 
	float x, y;//ÆøÅº ½ÃÀÛÁöÁ¡ 
	float fireX, fireY;//ÆøÅº ¿òÁ÷ÀÓ 
	float speed;//ÆøÅº ½ºÇÇµå
	float angle;//ÆøÅºÀÇ ¾Þ±Û 
	float gravity;//ÆøÅºÀÇ Áß·Â 
	bool isFire;//ÆøÅº ´ø º³Ä? 

};
class Boom : public GameObject
{
private:
	vector<tagBoom> _vBoom;
	vector<tagBoom>::iterator _viBoom;
	int _bulletMax;
	float _range; //ÆøÅº °Å¸® 
				  //((Player*)OBJECTMANAGER->FindObject(ObjectType::PLAYER, "ÇÃ·¹ÀÌ¾î"));


	
	int _frameCount[10]; 
	int _frameIndex[10];
	int _PlayerBoomMax; //ÇÃ·¹ÀÌ¾î ÆøÅº°³¼ö ÃÖ´ë´Â 10°³ÀÌ´Ù 

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
	int GetPlayerBoomMax() { return _PlayerBoomMax; }//ÇÃ·¹ÀÌ¾î ÆøÅºÃÖ´ë°¹¼ö
	void SetPlayerBoomMax(int PlayerBoomMax) { _PlayerBoomMax = PlayerBoomMax; }
	vector<tagBoom> getVBoom() { return _vBoom; }
	vector<tagBoom>::iterator getViBoom() { return _viBoom; }

	
//	void SetisFire(int i, bool fire) { _vBoom[i].isFire = fire; }
};




// ########################±âº»ÃÑ¾Ë»óÅÂ 
class Bullet1 :public GameObject  
{
private:
	//const char* _imageName;
	//float _range;
	//int _bulletMax;
	bool _isFrameImg;

	float _range; //ÃÑ¾Ë°Å¸® 
	
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _angle;
	//	float _angle1; 

	///	int _frameX;
	//int _frameY;

public:
	//ÃÑ¾Ë¹ß»ç
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





