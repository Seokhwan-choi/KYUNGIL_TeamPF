#pragma once
#include "GameObject.h"

typedef struct tagBubble
{
	image* bubbleImage;
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
BUBBLE, *LBUBBLE;

class Bubble : public GameObject
{
private:
	float _range;						//거품 거리 
	int _bubbleMax;						//거품 갯수 
	vector<BUBBLE> _vBubble;			
	vector<BUBBLE>::iterator _viBubble;
public:
	//거품 발사 명령
	void fire(float x, float y, float angle, float speed);
	//거품 움직임 처리
	void move();

	Bubble(string name);
	~Bubble();

	virtual HRESULT Init(const char * imageName, int width, int height, int bubbleMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	vector<BUBBLE> getVBubble() { return _vBubble; }
	vector<BUBBLE>::iterator getViBubble() { return _viBubble; }
};

