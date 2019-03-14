#pragma once
#include "SceneMaker.h"
class StageOne : public SceneMaker
{
private:
	class Player* _player;
	class BubbleCrab* _boss;
	class Crab* _crab;

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


	bool _crush;				// �ھҳ�?
	RECT _wallRect;				// ��������

	//RECT _test;					// 







public:

	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	void PlayerBulletCollisionEnemy();   //�÷��̾� �Ѿ˰� ���浹  
	void PlayerCollisionEnemy();         //���Ϳ� �÷��̾� ���� �浹������ �з����� 
	void PlayerBoomCollisionBoom();      //�÷��̾� ����ź�� ���� �浹������ �Ǳ�� 
	
	StageOne() {}
	~StageOne() {}
};

//for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
//{
//	if (_player->playerbullet()->getVBullet()[i].isFire == false) continue;
//	if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_crab->getCol(2)))
//	{
//		_crab->Damage(1);
//		_player->playerbullet()->getVBullet()[i].isFire = false;
//		break;
//	}
//}
////###########################�غ�ӽŰ� �Ѿ� 
//for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
//{
//	if (_player->heavybullet()->getVBullet()[i].isFire == false)continue;
//	if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_crab->getCol(2)))
//	{
//		_crab->Damage(1);
//		_player->heavybullet()->getVBullet()[i].isFire = false;
//		break;
//	}
//}
