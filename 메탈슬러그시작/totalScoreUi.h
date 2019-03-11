#pragma once
#include "GameObject.h"
class totalScoreUi :
	public GameObject
{
public:
	totalScoreUi(string name, POINTFLOAT pos, POINTFLOAT size, Pivot pivot);
	~totalScoreUi();
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

};

