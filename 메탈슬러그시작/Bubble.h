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
	int count[3];				//ī��Ʈ 0�� �迭�� ū���� ��ǰ�� ������ ������� �ð�
								//ī��Ʈ 1, 2�� �迭�� ū���� ��ǰ�� ������ �ϴ� �ð�
	int index[2];
	int upDownCount;
	bool isDown;
	bool ImageChange;
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

	//��ǰ ���� get
	vector<BUBBLE> getVBubble() { return _vBubble; }
	//��ǰ �ݺ��� get
	vector<BUBBLE>::iterator getViBubble() { return _viBubble; }
};

