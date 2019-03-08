#pragma once
#include "SceneMaker.h"
class startScene : public SceneMaker
{
private:
	
public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);
	startScene() {}
	~startScene() {}
};

