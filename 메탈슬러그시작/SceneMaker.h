#pragma once
#include "gameNode.h"

// ��� ��� �޾Ƽ� �� �����ȴ�
class SceneMaker : public gameNode
{
private:

public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	SceneMaker() {}
	~SceneMaker() {}
};

