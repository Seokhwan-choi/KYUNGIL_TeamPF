#pragma once
#include "SceneMaker.h"
class StageOne : public SceneMaker
{
private:

	class Player* _player;
	class Crab* _crab[9];
	class BubbleCrab* _bubbleCrab[3];
	class Fish* _fish;
	class BigCrab* _bigCrab;

	image* _bgImage;			// ����̹��� 
	image* _bgSea;				// ��� �ⷷ�ⷷ
	image* _bgImage2;			// ����� ���
	image* _PixelImage;			// �ȼ� �浹�� �̹���
	image* _tongImage;			// ���� 
	image* _wallImage;			// ���庮
	
	bool _PixelCheck;			// �ȼ� �� ����

	int _index;					// ��� �ⷷ�ⷷ ������ �ε���
	int _count;					// ��� �ⷷ�ⷷ ������ ī��Ʈ

	int _index2;				// ���庮 ������ �ε���
	int _count2;				// ���庮 ������ ī��Ʈ

	int _index3;
	int _count3;

	bool _check;


	bool _crush;				// �ھҳ�?
	RECT _wallRect;				// ��������

	int _crabCount;				//������ ��
	int _bubbleCount;			//��ǰ�� ��

	//RECT _test;					// 


	image* _fade;				// fade in/out
	int _fadecount;				// fade ī��Ʈ��
	int _alpha;					// fade ���İ� ( 255 ���� , 0 ���� )
	bool _fadein;				// ����
	bool _fadeout;				// ��
	
    //##################################��ǥ�׽�Ʈ�� ��Ʈ
	RECT _testRect;
	




public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void PlayerBulletCollisionEnemy();   //�÷��̾� �Ѿ˰� ���浹  
	void PlayerCollisionEnemy();         //���Ϳ� �÷��̾� ���� �浹������ �з����� 
	void PlayerBoomCollisionBoom();      //�÷��̾� ����ź�� ���� �浹������ �Ǳ�� 
	void ChangeMap(); 

	StageOne() {}
	~StageOne() {}
};
