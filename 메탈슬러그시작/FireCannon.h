#pragma once
#include "GameObject.h"

typedef struct tagFireCannon
{
	image* fireCannonImage;
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
	float dist;
}
FIRECANNON, *LFIRECANNON;

class FireCannon : public GameObject
{
private:
	float _range;									//ȭ���� �ִ� ��Ÿ� 
	int _fireCannonMax;								//ȭ���� ���� 
	float _x, _y;									//�߻� ��� �÷��̾� ��ǥ

	image* _bridgeImg[22];							//�ٸ� �̹���

	vector<FIRECANNON> _vFireCannon[2];
	vector<FIRECANNON>::iterator _viFireCannon[2];
public:
	FireCannon(string name);
	~FireCannon();

	virtual HRESULT Init(const char * imageName, int width, int height, int fireCannonMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//���� ȭ���� �߻� ���
	void leftFire(float x, float y, float angle, float speed);
	//���� ȭ���� ������ ó��
	void leftFireMove();
	//������ ȭ���� �߻� ���
	void rightFire(float x, float y, float angle, float speed);
	//������ ȭ���� ������ ó��
	void rightFireMove();

	//�߻� ��� �÷��̾� ��ǥ �Է�
	void setPosition(float x, float y) { _x = x, _y = y; }

	//ȭ���� ���� get
	vector<FIRECANNON> getVFireCannon(int i) { return _vFireCannon[i]; }
	//ȭ���� �ݺ��� get
	vector<FIRECANNON>::iterator getViFireCannon(int i) { return _viFireCannon[i]; }
};

