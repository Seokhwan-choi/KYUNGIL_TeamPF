#pragma once
#include "SceneMaker.h"
// MainGame이라고 생각하면 된다.
class StageOne : public SceneMaker
{
public:

	HRESULT Init();			// 씬 초기화
	void Release();			// 씬 해제
	void Update();			// 씬 업데이트
	void Render();			// 씬 렌더

	StageOne() {}
	~StageOne() {}
};

