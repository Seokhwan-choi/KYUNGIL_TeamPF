#pragma once
#include "SceneMaker.h"
class StageTwo : public SceneMaker
{
private:
	POINTFLOAT _center;
public:
	HRESULT Init();			// æ¿ √ ±‚»≠
	void Release();			// æ¿ «ÿ¡¶
	void Update();			// æ¿ æ˜µ•¿Ã∆Æ
	void Render();			// æ¿ ∑ª¥ı

	StageTwo() {}
	~StageTwo() {}
};

