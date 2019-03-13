#pragma once
#include "SceneMaker.h"
class LoadingScene : public SceneMaker
{
private:
	class loading* _loading;		// �ε� �����Ѵ�.

public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void LoadingImage();
	void LoadingSound();

	LoadingScene() {}
	~LoadingScene() {}
};

