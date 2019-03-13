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
	float _range;									//화염포 최대 사거리 
	int _fireCannonMax;								//화염포 갯수 
	float _x, _y;									//발사 당시 플레이어 좌표

	image* _bridgeImg[22];							//다리 이미지

	vector<FIRECANNON> _vFireCannon[2];
	vector<FIRECANNON>::iterator _viFireCannon[2];
public:
	FireCannon(string name);
	~FireCannon();

	virtual HRESULT Init(const char * imageName, int width, int height, int fireCannonMax, float range);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//왼쪽 화염포 발사 명령
	void leftFire(float x, float y, float angle, float speed);
	//왼쪽 화염포 움직임 처리
	void leftFireMove();
	//오른쪽 화염포 발사 명령
	void rightFire(float x, float y, float angle, float speed);
	//오른쪽 화염포 움직임 처리
	void rightFireMove();

	//발사 당시 플레이어 좌표 입력
	void setPosition(float x, float y) { _x = x, _y = y; }

	//화염포 벡터 get
	vector<FIRECANNON> getVFireCannon(int i) { return _vFireCannon[i]; }
	//화염포 반복자 get
	vector<FIRECANNON>::iterator getViFireCannon(int i) { return _viFireCannon[i]; }
};

