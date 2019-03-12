#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"

HRESULT StageOne::Init(void)
{
	_player = new Player("플레이어", { 500,WINSIZEY / 2 + 175}, { 50, 50 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	_boss = new BigCrab("boss", { 2060, WINSIZEY / 2 + 110 }, { 200,280 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::ENEMY, _boss);
	_boss->Init();

	GameOverUi* _gameoverui = new GameOverUi("gameoverui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui);

	GameOverUi_2* _gameoverui2 = new GameOverUi_2("gameoverui2", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _gameoverui2);

	stage1StartUi* _stage1startui = new stage1StartUi("stage1startui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _stage1startui);

	timeUi* _timeui = new timeUi("timeui", { 0,0 }, { 0,0 }, GameObject::Pivot::LeftTop);
	OBJECTMANAGER->AddObject(ObjectType::UI, _timeui);

	_bgImage = IMAGEMANAGER->addImage("배경", "Background/배경.bmp", 14070, 1150, true , RGB(255,0,255));
	_bgSea = IMAGEMANAGER->addFrameImage("배경출렁", "Background/배경출렁2.bmp", 19568, 278, 8, 1);
	_wallImage = IMAGEMANAGER->addFrameImage("맵장벽", "Background/맵장벽.bmp", 5400, 960, 6, 1, true, RGB(255, 0, 255));
	_bgImage2 = IMAGEMANAGER->addImage("배경의배경", "Background/배경의배경.bmp", 9562, 1200, true, RGB(255, 0, 255));
	_PixelImage = IMAGEMANAGER->addImage("배경픽셀", "Background/배경픽셀.bmp", 14070, 1150, true, RGB(255, 0, 255));

	_PixelCheck = false;

	_wallRect = RectMakeCenter(6750, WINSIZEY/2, 50, 1500);

	_index = 0;
	_count = 0;

	_index2 = 0;
	_count2 = 0;

	_crush = false;

	return S_OK;
}

void StageOne::Release(void)
{
	OBJECTMANAGER->Release();
}

void StageOne::Update(void)
{
	OBJECTMANAGER->Update();
	_count++;
	if (_count % 10 == 0) {
		_index++;
		if (_index > 7) {
			_index = 0;
		}
		IMAGEMANAGER->findImage("배경출렁")->setFrameX(_index);
	}

	_count2++;
	if (_count2 % 10 == 0) {
		_index2++;
		if (_index2 > 6) {
			_index2 = 0;
		}
		IMAGEMANAGER->findImage("맵장벽")->setFrameX(_index2);
	}

	// F1 눌러서 픽셀좀 보쟝 
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) 
	{
		_PixelCheck = !_PixelCheck;
		_crush = !_crush;
	}

	if (_crush) {
		RECT _temp;
		if (IntersectRect(&_temp, &_player->GetRect(), &_wallRect)) {
			_player->SetPosition({
				_wallRect.left - (_player->GetSize().x / 2.0f),
				_player->GetPosition().y });
		}
		CAMERA->SetCamera(_player->GetPosition());
	}
	
}

void StageOne::Render(void)
{
	_bgImage2->render(getMemDC(), 0 - (CAMERA->GetCamera().left / 2), -310 - CAMERA->GetCamera().top);
	_bgImage->render(getMemDC(), 0 - CAMERA->GetCamera().left, -135 - CAMERA->GetCamera().top);
	_bgSea->frameRender(getMemDC(), 0 - CAMERA->GetCamera().left, WINSIZEY - 278 - CAMERA->GetCamera().top);
	
	if (_PixelCheck) {
		_PixelImage->render(getMemDC(), 0 - CAMERA->GetCamera().left, -135 - CAMERA->GetCamera().top);
		_wallImage->frameRender(getMemDC(), 5850 - CAMERA->GetCamera().left, 0 - CAMERA->GetCamera().top);
	}
	
	OBJECTMANAGER->Render();
	//RECT _WALL = CAMERA->Relative(_wallRect);
	//Rectangle(getMemDC(), _WALL);
}