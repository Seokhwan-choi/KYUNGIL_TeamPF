#pragma once
#include "GameObject.h"

typedef struct tagBubble
{
	image* bubbleImage[2];
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool isFire;
	int count[3];				//카운트 0번 배열은 큰게의 거품이 터져서 사라지는 시간
								//카운트 1, 2번 배열은 큰게의 거품을 랜더링 하는 시간
	int index[2];
	int upDownCount;
	bool isDown;
	bool ImageChange;
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
	void move1();
	void render();

	Bubble(string name);
	~Bubble();

	virtual HRESULT Init(const char * imageName, int width, int height, int bubbleMax, float range);
	virtual HRESULT Init2(const char * imageName, int width, int height, int FrameX, int FrameY, int bubbleMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();
	virtual void Render2();

	//거품 벡터 get
	vector<BUBBLE> getVBubble() { return _vBubble; }
	//거품 반복자 get
	vector<BUBBLE>::iterator getViBubble() { return _viBubble; }
};

