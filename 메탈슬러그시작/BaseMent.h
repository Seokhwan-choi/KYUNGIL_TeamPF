#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:


	image* _bgImage;			// ��� �̹���
	image* _pixelImage;			// ��� �ȼ� �̹���

	class Player* _player;
	class BigCrab* _bigCrab;


	image* _Out;				// ������ �� �̹���
	int _count;					// ������ �� �̹��� ������ ī��Ʈ
	int _index;					// ������ �� �̹��� ������ �ε���

	bool _check;				// ����� ��

public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);



	
	BaseMent() {}
	~BaseMent() {}
};

