#pragma once
#include "GameObject.h"
class oldMan : public GameObject
{
private:
	bool _isRight;
	RECT _colRc;
	POINTFLOAT _distance;	//�÷��̾ ���� ������ ������ �����̵��� �������ش�
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

