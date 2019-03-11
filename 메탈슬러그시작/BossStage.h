#pragma once
#include "SceneMaker.h"
class BossStage : public SceneMaker
{

private:
	image* _bgImage;			// ���� �������� ��� �̹���
	RECT _ground[11];			// ���� �������� �ٴ� RECT ( �ٴ� RECT 11�� )
	image* _groundImage[11];	// ���� �������� �ٴ� Image
	bool _check[11];			// ���� �������� �ٴ� �������� ?
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BossStage() {}
	~BossStage() {}
};

