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

	image* _wallImage;			// ���庮

	bool _PixelCheck;			// �ȼ� �� ����

	int _index;					// ��� �ⷷ�ⷷ ������ �ε���
	int _count;					// ��� �ⷷ�ⷷ ������ ī��Ʈ

	int _index2;				// ���庮 ������ �ε���
	int _count2;				// ���庮 ������ ī��Ʈ


	bool _crush;				// �ھҳ�?
	RECT _wallRect;				// ��������

public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	StageOne() {}
	~StageOne() {}
};

