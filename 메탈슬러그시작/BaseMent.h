#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:
	image* bgImage;				// 배경 이미지
	image* pixelImage;			// 배경 픽셀 이미지

public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BaseMent() {}
	~BaseMent() {}
};

