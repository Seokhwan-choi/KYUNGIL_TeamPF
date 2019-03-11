#pragma once
#include "SceneMaker.h"
class StageOne : public SceneMaker
{
private:
	class Player* _player;
	class Boss* _crab;

	image* _bgImage;			// ����̹��� 
	image* _bgSea;				// ��� �ⷷ�ⷷ

	image* _bgImage2;			// ����� ���
	image* _PixelImage;			// �ȼ� �浹�� �̹���

	image* _wallImage;			// ���庮

	bool _PixelCheck;			// �ȼ� �� ����

	int _index;					// ��� �ⷷ�ⷷ ������ �ε���
	int _count;					// ��� �ⷷ�ⷷ ������ ī��Ʈ

	int _index2;				// ���庮 ������ �ε���
	int _count2;				// ���庮 ������ ī��Ʈ


	bool _crush;				// �ھҳ�?
	RECT _wallRect;				// ��������

public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	StageOne() {}
	~StageOne() {}
};

