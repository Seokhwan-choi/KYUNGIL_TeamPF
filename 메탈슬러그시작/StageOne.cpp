#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"


HRESULT StageOne::Init(void)
{
	_player = new Player("플레이어", { WINSIZEX / 2,WINSIZEY / 2 }, { 50, 50 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	_bgImage = IMAGEMANAGER->addImage("배경", "배경.bmp", 14070, 1150, true , RGB(255,0,255));
	_bgSea = IMAGEMANAGER->addFrameImage("배경출렁", "배경출렁2.bmp", 19568, 278, 8, 1);
	_bgImage2 = IMAGEMANAGER->addImage("배경의배경", "배경의배경.bmp", 9562, 1200, true, RGB(255, 0, 255));
	_PixelImage = IMAGEMANAGER->addImage("배경픽셀", "배경픽셀.bmp", 14070, 1150, true, RGB(255, 0, 255));

	_PixelCheck = false;

	_index = 0;
	_count = 0;

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

	// F1 눌러서 픽셀좀 보쟝 
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) 
	{
		_PixelCheck = !_PixelCheck;
	}
}

void StageOne::Render(void)
{
	_bgImage2->render(getMemDC(), 0 - (CAMERA->GetCamera().left / 2), -310 - CAMERA->GetCamera().top);
	_bgImage->render(getMemDC(), 0 - CAMERA->GetCamera().left, -135 - CAMERA->GetCamera().top);
	_bgSea->frameRender(getMemDC(), 0 - CAMERA->GetCamera().left, WINSIZEY - 278 - CAMERA->GetCamera().top);

	if (_PixelCheck) {
		_PixelImage->render(getMemDC(), 0 - CAMERA->GetCamera().left, -135 - CAMERA->GetCamera().top);
	}

	OBJECTMANAGER->Render();
}