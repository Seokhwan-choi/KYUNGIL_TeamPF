#include "stdafx.h"
#include "BossStage.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"

HRESULT BossStage::Init(void)
{
	SOUNDMANAGER->play("보스전시작");

	_bgImage = IMAGEMANAGER->findImage("보스배경");
	_waterground = IMAGEMANAGER->findImage("보스출렁");

	CAMERA->SetCamera3({ WINSIZEX / 2.f, WINSIZEY / 2.f });

	for (int i = 0; i < 22; ++i) 
	{
		char str[100];
		sprintf(str, "다리%d", i + 1);
		_bridge[i].rc = RectMake( (175 * i), WINSIZEY - 215, 175, 183);
		_bridge[i].bridgeImg = IMAGEMANAGER->addImage(str, string("Background/"+ string(str) + ".bmp").c_str(), (175 * i), WINSIZEY - 215, 175, 183, true, RGB(255,0,255));
		_bridge[i].isCrush = false;
	}

	for (int i = 0; i < 22; ++i)
	{
		char str[100];
		sprintf(str, "픽셀다리%d", i + 1);
		_pixelbridge[i].rc = RectMake((175 * i), WINSIZEY - 215, 175, 183);
		_pixelbridge[i].bridgeImg = IMAGEMANAGER->addImage(str, string("Background/" + string(str) + ".bmp").c_str(), (175 * i), WINSIZEY - 215, 175, 183, true, RGB(255, 0, 255));
		_pixelbridge[i].isCrush = false;
		_pixelbridge[i].isShow = false;
	}


	_start = false;
	_loopX = 0;
	_gcount = 0;
	_gframe = 0;


	for (int i = 0; i < 2; i++)
	{
		_reset[i] = false;
	}


	_player = new Player("플레이어", { WINSIZEX - 200, WINSIZEY / 2 + 250 }, { 320, 403 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	_boss = new Boss("boss", { -WINSIZEX / 4, WINSIZEY / 2 + 100 }, { WINSIZEX / 2, WINSIZEY }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::BOSS, _boss);

	GameCompleteUi* _gamecompleteui = new GameCompleteUi("gamecompleteui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gamecompleteui);

	totalScore* _totalscore = new totalScore("totalscore", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _totalscore);


	GameOverUi* _gameoverui = new GameOverUi("gameoverui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui);
	//
	GameOverUi_2* _gameoverui2 = new GameOverUi_2("gameoverui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui2);
	//
	timeUi* _timeui = new timeUi("timeui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui);

	playerDataUi* _playerdataui = new playerDataUi("playerdataui", { WINSIZEX / 2,WINSIZEY / 2 }, { 50,50 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _playerdataui);

	OBJECTMANAGER->Init();

	return S_OK;
}

void BossStage::Release(void)
{
	OBJECTMANAGER->Release();
}

void BossStage::Update(void)
{
	
	// ============== 배경을 천천히 루프 시킨다. ================
	_loopX++;
	// ============== 배경바닥 출렁출렁 시킨다. =================
	_gcount++;
	if (_gcount % 5 == 0)
	{
		_gframe++;
		if (_gframe > 7) {
			_gframe = 0;
		}
		IMAGEMANAGER->findImage("보스출렁")->setFrameX(_gframe);
	}
	// ======================================================


	// ============== 배경다리 이동 및 보정 시킨다. ==================
	if (_start) 
	{
		CAMERA->SetCamera3(_player->GetPosition());
		for (int i = 0; i < 22; ++i)
		{
			//x좌표 -3씩 앞당김
			_bridge[i].bridgeImg->setX(_bridge[i].bridgeImg->getX() - 3);

			//화면 -175지점에 왔을 경우 보이지 않는 곳으로 이미지를 모은다. 
			if (_bridge[i].bridgeImg->getX() < - 175) 
			{
				_bridge[i].bridgeImg->setX(-200);
			}
		}

		for (int i = 0; i < 22; ++i) {
			//x좌표 -3씩 앞당김
			_pixelbridge[i].bridgeImg->setX(_pixelbridge[i].bridgeImg->getX() - 3);

			//화면 -175지점에 왔을 경우 뒤로 되돌린다. 
			if (_pixelbridge[i].bridgeImg->getX() < -175)
			{
				_pixelbridge[i].bridgeImg->setX(-200);
				_pixelbridge[i].isShow = false;
			}

			if (_pixelbridge[i].bridgeImg->getX() < WINSIZEX)
			 {

				_pixelbridge[i].isShow = true;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q')) 
	{
		_start = !_start;
	}

	

	// =========================================================
	//-200위치로 가면 파괴 여부 변경
	for (int i = 0; i < 11; i++)
	{
		if (_bridge[i].bridgeImg->getX() == -200)
		{
			_bridge[i].isCrush = true;
		}

		if (_pixelbridge[i].bridgeImg->getX() == -200)
		{
			_pixelbridge[i].isCrush = true;
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

		for (int i = 0; i < 11; i++)
		{
			_pixelbridge[i].bridgeImg->setX(_pixelbridge[21].bridgeImg->getX() + 150 + (i * 175));
			_pixelbridge[i].isCrush = false;
		}

		_reset[0] = false;
	}

	for (int i = 11; i < 22; i++)
	{
		if (_bridge[i].bridgeImg->getX() == -200)
		{
			_bridge[i].isCrush = true;
		}
		if (_pixelbridge[i].bridgeImg->getX() == -200)
		{
			_pixelbridge[i].isCrush = true;
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

		for (int i = 11; i < 22; i++)
		{
			_pixelbridge[i].bridgeImg->setX(_pixelbridge[10].bridgeImg->getX() + 150 + ((i - 11) * 175));
			_pixelbridge[i].isCrush = false;
		}

		_reset[1] = false;
	}

	this->PlayerBulletBoss();
	for (int i = 0; i < 22; ++i) 
	{
		//if (!_pixelbridge[i].isShow) continue;
		_player->BossStagePixel(_pixelbridge[i].bridgeImg);
	}

	OBJECTMANAGER->Update();
}

void BossStage::Render(void)
{
	// ============== 배경을 천천히 루프 시킨다. ================
	RECT _rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_bgImage->loopRender(getMemDC(), &_rc, _loopX, 0);
	// ============== 배경바닥 출렁출렁 시킨다. =================
	_waterground->frameRender(getMemDC(), 0 - CAMERA->GetCamera().left, WINSIZEY - 100 - CAMERA->GetCamera().top);
	// ======================================================

	//다리 이미지 그리기
	for (int i = 0; i < 22; ++i)
	{	
		//Rectangle(getMemDC(), _bridge[i].rc);
		_bridge[i].bridgeImg->render(getMemDC(), _bridge[i].bridgeImg->getX() - CAMERA->GetCamera().left - 300, _bridge[i].bridgeImg->getY() - CAMERA->GetCamera().top);
		//_bridge[i].bridgeImg->render(getMemDC(), _bridge[i].bridgeImg->getX(), _bridge[i].bridgeImg->getY());
	}
	
	if (_start)
	{
		//다리 이미지 그리기
		for (int i = 0; i < 22; ++i)
		{
			_pixelbridge[i].bridgeImg->render(getMemDC(), _pixelbridge[i].bridgeImg->getX() -  CAMERA->GetCamera().left - 300, _pixelbridge[i].bridgeImg->getY() - CAMERA->GetCamera().top);
			//_pixelbridge[i].bridgeImg->render(getMemDC(), _pixelbridge[i].bridgeImg->getX(), _pixelbridge[i].bridgeImg->getY());
		}
	}

	OBJECTMANAGER->Render();
}

void BossStage::PlayerBulletBoss()
{
	RECT temp; 

	for (int i = 0; i < _player->playerbullet()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &_player->playerbullet()->getVBullet()[i].rc, &_boss->GetRect()))
		{
			_boss->Damage(1); 
			_player->playerbullet()->SetisFire(i, false);

		}
	}

	for (int i = 0; i < _player->heavybullet()->getVBullet().size(); i++)
	{
		if (IntersectRect(&temp, &_player->heavybullet()->getVBullet()[i].rc, &_boss->GetRect()))
		{
			_boss->Damage(1);
			_player->heavybullet()->SetisFire(i, false);
		}
	}


	for (int i = 0; i < _player->playerboom()->getVBoom().size(); i++)
	{
		if (IntersectRect(&temp, &_player->playerboom()->getVBoom()[i].rc, &_boss->GetRect()))
		{
			_boss->Damage(1);
			_player->playerboom()->SetisFire(i, false);
		}
	}

}
