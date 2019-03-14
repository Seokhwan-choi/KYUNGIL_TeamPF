#pragma once
#include "SceneMaker.h"
class BaseMent : public SceneMaker
{

private:

	class Player* _player;  
	image* _bgImage;					// ��� �̹���
	image* _pixelImage;					// ��� �ȼ� �̹���

	class Fish* _fish;					//�����
	class BubbleCrab* _bubbleCrab[10];	//��ǰ��
	class BigCrab* _bigCrab[3];			//ū��


	image* _Out;						// ������ �� �̹���
	int _count;							// ������ �� �̹��� ������ ī��Ʈ
	int _index;							// ������ �� �̹��� ������ �ε���

	int _bubbleCrabCount;				//��ǰ�� ��
	int _bigCrabCount;					//ū�� ��
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BaseMent() {}
	~BaseMent() {}
};

