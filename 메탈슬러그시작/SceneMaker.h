#pragma once
#include "gameNode.h"

class SceneMaker	// 요놈 상속 받아서 맵 만들면된당
{
private:

public:

	virtual HRESULT Init(void);
	virtual void Release (void);
	virtual void Update(void);
	virtual void Render(void);

	SceneMaker() {}
	~SceneMaker() {}
};

