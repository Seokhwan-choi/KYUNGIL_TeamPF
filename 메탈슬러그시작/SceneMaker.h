#pragma once
#include "gameNode.h"

class SceneMaker	// ��� ��� �޾Ƽ� �� �����ȴ�
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

