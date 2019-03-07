#pragma once
#include "SceneMaker.h"
class StageOne : public SceneMaker
{
private:
	class Player* _player;

	image* _bgImage;			// ����̹��� 
	image* _bgSea;				// ��� �ⷷ�ⷷ

	image* _bgImage2;			// ����� ���
	image* _PixelImage;			// �ȼ� �浹�� �̹���

	image* _wallImage;			// ��_�庮

	bool _PixelCheck;			// �ȼ� �� ����

	int _index;					// ������ �ε���
	int _count;					// ������ ī��Ʈ

public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	StageOne() {}
	~StageOne() {}
};

