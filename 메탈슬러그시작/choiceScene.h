#pragma once
#include "SceneMaker.h"
//ĳ���� ����â
class choiceScene : public SceneMaker
{
public:
	choiceScene() {}
	~choiceScene() {}

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);
};

