#pragma once
#include "SceneMaker.h"
// MainGame�̶�� �����ϸ� �ȴ�.
class StageOne : public SceneMaker
{
public:

	HRESULT Init();			// �� �ʱ�ȭ
	void Release();			// �� ����
	void Update();			// �� ������Ʈ
	void Render();			// �� ����

	StageOne() {}
	~StageOne() {}
};

