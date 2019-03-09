#pragma once
#include "GameObject.h"
class realPlayer : public GameObject
{
private:
	
public:
	realPlayer(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~realPlayer();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

