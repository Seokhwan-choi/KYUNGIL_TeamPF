#include "stdafx.h"
#include "StageOne.h"
#include "Player.h"


HRESULT StageOne::Init(void)
{
	_player = new Player("ÇÃ·¹ÀÌ¾î", { WINSIZEX / 2,WINSIZEY / 2 }, { 50, 50 }, GameObject::Pivot::Center);
	OBJECTMANAGER->AddObject(ObjectType::Enum::PLAYER, _player);

	_bgImage = IMAGEMANAGER->addImage("¹è°æ", "¹è°æ.bmp", 14070, 1150, true , RGB(255,0,255));
	_bgSea = IMAGEMANAGER->addFrameImage("¹è°æÃâ··", "¹è°æÃâ··2.bmp", 19568, 278, 8, 1);
	_wallImage = IMAGEMANAGER->addFrameImage("¸ÊÀåº®", "¸ÊÀåº®.bmp", 8300, 960, 7, 1, true, RGB(255, 0, 255));
	_bgImage2 = IMAGEMANAGER->addImage("¹è°æÀÇ¹è°æ", "¹è°æÀÇ¹è°æ.bmp", 9562, 1200, true, RGB(255, 0, 255));
	_PixelImage = IMAGEMANAGER->addImage("¹è°æÇÈ¼¿", "¹è°æÇÈ¼¿.bmp", 14070, 1150, true, RGB(255, 0, 255));

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
		IMAGEMANAGER->findImage("¹è°æÃâ··")->setFrameX(_index);
	}

	//_count++;
	//if (_count % 10 == 0) {
	//	_index++;
	//	if (_index > 6) {
	//		_index = 0;
	//	}
	//	IMAGEMANAGER->findImage("¸ÊÀåº®")->setFrameX(_index);
	//}

	// F1 ´­·¯¼­ ÇÈ¼¿Á» º¸Àö 
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
	_wallImage->frameRender(getMemDC(), 6000 - CAMERA->GetCamera().left, 0 - CAMERA->GetCamera().top);

	if (_PixelCheck) {
		_PixelImage->render(getMemDC(), 0 - CAMERA->GetCamera().left, -135 - CAMERA->GetCamera().top);
	}

	OBJECTMANAGER->Render();
}