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
	float _range;						//��ź �Ÿ� 
	int _bombMax;						//��ź ���� 
	float _x, _y;						//�߻� ��� �÷��̾� ��ǥ

	vector<BOMB> _vBomb;
	vector<BOMB>::iterator _viBomb;
public:
	Bomb(string name);
	~Bomb();

	virtual HRESULT Init(const char * imageName, int width, int height, int bombMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//��ź �߻� ���
	void fire(float x, float y, float angle, float speed);
	//��ź ������ ó��
	void move();
	//�߻� ��� �÷��̾� ��ǥ �Է�
	void setPosition(float x, float y) { _x = x, _y = y; }

	vector<BOMB> getVBomb() { return _vBomb; }
	vector<BOMB>::iterator getViBomb() { return _viBomb; }
};

