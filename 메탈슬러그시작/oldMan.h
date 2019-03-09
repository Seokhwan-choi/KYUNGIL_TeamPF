#pragma once
#include "GameObject.h"
class oldMan : public GameObject
{
private:
	bool _isRight;
	RECT _colRc;
	POINTFLOAT _distance;	//플레이어가 일정 범위에 들어오면 움직이도록 설정해준다
	float _userDistance;
	float _sense;

	class Item* _item;
public:
	oldMan(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~oldMan();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

