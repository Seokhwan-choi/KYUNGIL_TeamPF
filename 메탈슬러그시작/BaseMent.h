#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:
	image* _bgImage;			// ��� �̹���
	image* _pixelImage;			// ��� �ȼ� �̹���

	image* _Out;				// ������ �� �̹���
	int _count;					// ������ �� �̹��� ������ ī��Ʈ
	int _index;					// ������ �� �̹��� ������ �ε���

public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BaseMent() {}
	~BaseMent() {}
};

