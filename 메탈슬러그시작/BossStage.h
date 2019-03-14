#pragma once
#include "SceneMaker.h"

typedef struct tagBridge
{
	RECT rc;
	image* bridgeImg;
	bool isCrush;
}
BRIDGE, *LBRIDGE;

class BossStage : public SceneMaker
{
private:
	image* _bgImage;			// ���� �������� ��� �̹���
	image* _waterground;		// ���� �������� �ⷷ �̹���

	BRIDGE _bridge[22];			// �ٸ� ����ü
	bool _start;				// ���� �����߳� ?
	//image* _breakImage;		// ���� �����ϸ鼭 �μ��� �ٴ�

	int _loopX;					// ���� �������� ��� ������
	int _gcount;				// ���� �������� �ⷷ ������ ī��Ʈ
	int _gframe;				// ���� �������� �ⷷ ������ �ε���

	bool _reset[2];				//�ٸ� ���� ����

	class Player* _player;
	class Boss* _boss;
public:

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	BRIDGE getBridge(int i) { return _bridge[i]; }



	void PlayerBulletCollisionBoss(); //�÷��̾� �Ѿ˰� ���� �浹������ 
	BossStage() {}
	~BossStage() {}
};
