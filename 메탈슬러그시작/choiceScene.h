#pragma once
#include "SceneMaker.h"
//캐릭터 선택창
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

