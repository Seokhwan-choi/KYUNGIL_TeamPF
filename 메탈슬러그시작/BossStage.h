#pragma once
#include "SceneMaker.h"
class BossStage : public SceneMaker
{

private:
	image* _bgImage;			// ���� �������� ��� �̹���
	RECT _ground[11];			// ���� �������� �ٴ� RECT ( �ٴ� RECT 11�� )
	image* _groundImage[11];	// ���� �������� �ٴ� �̹���
	image* _waterground;		// ���� �������� �ⷷ �̹���
	image* _breakImage;			// ���� �����ϸ鼭 �μ��� �ٴ�
	bool _check[11];			// ���� �������� �ٴ� �������� ?
	bool _start;				// ���� �����߳� ?

	int _loopX;					// ���� �������� ��� ������
	int _gcount;				// ���� �������� �ⷷ ������ ī��Ʈ
	int _gframe;				// ���� �������� �ⷷ ������ �ε���
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BossStage() {}
	~BossStage() {}
};

