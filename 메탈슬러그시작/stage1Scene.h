#pragma once
#include "SceneMaker.h"
class stage1Scene : public SceneMaker
{

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);
	stage1Scene() {}
	~stage1Scene() {}
};

