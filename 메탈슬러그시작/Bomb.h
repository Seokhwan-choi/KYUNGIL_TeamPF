#pragma once
#include "GameObject.h"

typedef struct tagBomb
{
	image* bombImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool isFire;
	int count;
	int upDownCount;
	bool isDown;
}
BOMB, *LBOMB;

class Bomb : public GameObject
{
private:
	float _range;						//ÆøÅº °Å¸® 
	int _bombMax;						//ÆøÅº °¹¼ö 
	float _x, _y;						//¹ß»ç ´ç½Ã ÇÃ·¹ÀÌ¾î ÁÂÇ¥

	vector<BOMB> _vBomb;
	vector<BOMB>::iterator _viBomb;
public:
	Bomb(string name);
	~Bomb();

	virtual HRESULT Init(const char * imageName, int width, int height, int bombMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//ÆøÅº ¹ß»ç ¸í·É
	void fire(float x, float y, float angle, float speed);
	//ÆøÅº ¿òÁ÷ÀÓ Ã³¸®
	void move();
	//¹ß»ç ´ç½Ã ÇÃ·¹ÀÌ¾î ÁÂÇ¥ ÀÔ·Â
	void setPosition(float x, float y) { _x = x, _y = y; }

	vector<BOMB> getVBomb() { return _vBomb; }
	vector<BOMB>::iterator getViBomb() { return _viBomb; }
};

