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
	float _range;						//��ǰ �Ÿ� 
	int _bubbleMax;						//��ǰ ���� 
	vector<BUBBLE> _vBubble;			
	vector<BUBBLE>::iterator _viBubble;
public:
	//��ǰ �߻� ���
	void fire(float x, float y, float angle, float speed);
	//��ǰ ������ ó��
	void move();

	Bubble(string name);
	~Bubble();

	virtual HRESULT Init(const char * imageName, int width, int height, int bubbleMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//��ǰ ���� get
	vector<BUBBLE> getVBubble() { return _vBubble; }
	//��ǰ �ݺ��� get
	vector<BUBBLE>::iterator getViBubble() { return _viBubble; }
};

