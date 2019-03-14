#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:

	class Player* _player;  
	image* _bgImage;			// ��� �̹���
	image* _pixelImage;			// ��� �ȼ� �̹���

	class BigCrab* _bigCrab;


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

