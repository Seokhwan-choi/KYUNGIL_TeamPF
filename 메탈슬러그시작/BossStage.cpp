#include "stdafx.h"
#include "BossStage.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"

HRESULT BossStage::Init(void)
{
	_bgImage = IMAGEMANAGER->findImage("�������");
	_waterground = IMAGEMANAGER->findImage("�����ⷷ");
	_breakImage = IMAGEMANAGER->findImage("��μ���");


	for (int i = 0; i < 22; ++i) 
	{
		char str[100];
		sprintf(str, "�ٸ�%d", i + 1);
		_bridge[i].rc = RectMake( (175 * i), WINSIZEY - 215, 175, 183);
		_bridge[i].bridgeImg = IMAGEMANAGER->addImage(str, string("Background/"+ string(str) + ".bmp").c_str(), (175 * i), WINSIZEY - 215, 175, 183, true, RGB(255,0,255));
		_bridge[i].isCrush = false;

	}

	_start = false;
	_loopX = 0;
	_gcount = 0;
	_gframe = 0;
	for (int i = 0; i < 2; i++)
	{
		_reset[i] = false;
	}

	_player = new Player("�÷��̾�", { WINSIZEX / 2 + 200, WINSIZEY / 2 + 175 }, { 50, 50 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	_boss = new Boss("boss", { -WINSIZEX / 4, WINSIZEY / 2 + 100 }, { WINSIZEX / 2, WINSIZEY }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _boss);

	OBJECTMANAGER->Init();

	return S_OK;
}

void BossStage::Release(void)
{
	OBJECTMANAGER->Release();
}

void BossStage::Update(void)
{
	// ============== ����� õõ�� ���� ��Ų��. ================
	_loopX++;
	// ============== ���ٴ� �ⷷ�ⷷ ��Ų��. =================
	_gcount++;
	if (_gcount % 5 == 0)
	{
		_gframe++;
		if (_gframe > 7) {
			_gframe = 0;
		}
		IMAGEMANAGER->findImage("�����ⷷ")->setFrameX(_gframe);
	}
	// ======================================================


	// ============== ���ٸ� �̵� �� ���� ��Ų��. ==================

	if (_start) 
	{
		for (int i = 0; i < 22; ++i)
		{
			//x��ǥ -3�� �մ��
			_bridge[i].bridgeImg->setX(_bridge[i].bridgeImg->getX() - 3);

			//ȭ�� -175������ ���� ��� �ڷ� �ǵ�����. 
			if (_bridge[i].bridgeImg->getX() < - 175) 
			{
				_bridge[i].bridgeImg->setX(-200);
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q')) 
	{
		_start = !_start;
	}

	OBJECTMANAGER->Update();

	// =========================================================
	//-200��ġ�� ���� �ı� ���� ����
	for (int i = 0; i < 11; i++)
	{
		if (_bridge[i].bridgeImg->getX() == -200)
		{
			_bridge[i].isCrush = true;
		}
	}

	for (int i = 0; i < 11; i++)
	{
		if (!_bridge[i].isCrush) break;

		if (_bridge[i].isCrush && i == 10)
		{
			_reset[0] = true;
		}
	}

	if (_reset[0])
	{
		for (int i = 0; i < 11; i++)
		{
			_bridge[i].bridgeImg->setX(_bridge[21].bridgeImg->getX() + 150 + (i * 175));
			_bridge[i].isCrush = false;
		}

		_reset[0] = false;
	}

	for (int i = 11; i < 22; i++)
	{
		if (_bridge[i].bridgeImg->getX() == -200)
		{
			_bridge[i].isCrush = true;
		}
	}

	for (int i = 11; i < 22; i++)
	{
		if (!_bridge[i].isCrush) break;

		if (_bridge[i].isCrush && i == 21)
		{
			_reset[1] = true;
		}
	}

	if (_reset[1])
	{
		for (int i = 11; i < 22; i++)
		{
			_bridge[i].bridgeImg->setX(_bridge[10].bridgeImg->getX() + 150 + ((i - 11) * 175));
			_bridge[i].isCrush = false;
		}

		_reset[1] = false;
	}
}

void BossStage::Render(void)
{
	// ============== ����� õõ�� ���� ��Ų��. ================
	RECT _rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_bgImage->loopRender(getMemDC(), &_rc, _loopX, 0);
	// ============== ���ٴ� �ⷷ�ⷷ ��Ų��. =================
	_waterground->frameRender(getMemDC(), 0, WINSIZEY - 100);
	// ======================================================

	//�ٸ� �̹��� �׸���
	for (int i = 0; i < 22; ++i)
	{	
		//Rectangle(getMemDC(), _bridge[i].rc);
		_bridge[i].bridgeImg->render(getMemDC(), _bridge[i].bridgeImg->getX(), _bridge[i].bridgeImg->getY());
	}
	
	if (!_start)
	{
		//_breakImage->render(getMemDC(), -235, WINSIZEY - 215);
	}

	OBJECTMANAGER->Render();
}
