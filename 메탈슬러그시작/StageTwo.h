#pragma once
#include "SceneMaker.h"
class StageTwo : public SceneMaker
{
private:
	POINTFLOAT _center;
public:
	HRESULT Init();			// �� �ʱ�ȭ
	void Release();			// �� ����
	void Update();			// �� ������Ʈ
	void Render();			// �� ����

	StageTwo() {}
	~StageTwo() {}
};

