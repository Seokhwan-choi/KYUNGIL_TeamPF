#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:
	image* bgImage;				// ��� �̹���
	image* pixelImage;			// ��� �ȼ� �̹���

public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BaseMent() {}
	~BaseMent() {}
};

