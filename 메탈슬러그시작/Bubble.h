#pragma once
#include "GameObject.h"

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

	vector<BUBBLE> getVBubble() { return _vBubble; }
	vector<BUBBLE>::iterator getViBubble() { return _viBubble; }
};

