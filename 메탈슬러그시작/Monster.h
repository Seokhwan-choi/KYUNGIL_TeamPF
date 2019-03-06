#pragma once
#include "GameObject.h"
class Monster :public GameObject
{
private:

	
public:
	Monster(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~Monster();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

